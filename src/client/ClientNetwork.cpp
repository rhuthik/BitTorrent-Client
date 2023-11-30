#include "ClientNetwork.hpp"
#include "../utils/Logger.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close

ClientNetwork::ClientNetwork(const std::string& peerInfo, const std::string& trackerInfoFile, BasicLogger& logger)
    : peerInfo(peerInfo), trackerInfoFile(trackerInfoFile), log(logger) {}

bool ClientNetwork::Initialize() {
    log.Log(Info, "Initializing network for client");

    // Extracting IP and port from peerInfo
    std::string ip;
    int port;
    size_t colonPos = peerInfo.find(':');
    if (colonPos != std::string::npos) {
        ip = peerInfo.substr(0, colonPos);
        port = std::stoi(peerInfo.substr(colonPos + 1));
    } else {
        log.Log(Error, "Invalid peer info format.");
        return false;
    }

    // Creating socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        log.Log(Error, "Failed to create socket.");
        return false;
    }

    // Setup address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

    // Connecting to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        log.Log(Error, "Connection to server failed.");
        return false;
    }

    log.Log(Info, "Connected to server successfully.");
    return true;
}

void ClientNetwork::SendMessage(const std::string& message) {
    log.Log(Debug, "Sending message: " + message);
    send(clientSocket, message.c_str(), message.size(), 0);
}

std::string ClientNetwork::ReceiveMessage() {
    log.Log(Debug, "Receiving message");
    char buffer[1024] = {0};
    ssize_t bytesRead = recv(clientSocket, buffer, 1024, 0);
    if (bytesRead < 0) {
        log.Log(Error, "Error in receiving message.");
        return "";
    }
    return std::string(buffer, bytesRead);
}

ClientNetwork::~ClientNetwork() {
    if (clientSocket != -1) {
        close(clientSocket);
    }
}
