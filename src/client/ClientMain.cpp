#include "ClientNetwork.hpp"
#include "ClientCommands.hpp"
#include "FileTransfer.hpp"
#include "../utils/Logger.hpp"
#include "../utils/Common.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    BasicLogger c_log("client_log.txt");
    c_log.Log(Info, "Starting the client application");

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP:PORT> <tracker_info.txt>" << std::endl;
        return 1;
    }

    std::string peerInfo(argv[1]);
    std::string trackerInfoFile(argv[2]);

    // Initialize the Client Network
    ClientNetwork clientNetwork(peerInfo, trackerInfoFile, c_log);
    if (!clientNetwork.Initialize()) {
        c_log.Log(Error, "Failed to initialize network");
        return 1;
    }

    ClientCommands clientCommands(clientNetwork, c_log);

    // Main command loop
    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command.empty()) continue;
        if (command == "quit") break;

        clientCommands.ExecuteCommand(command);
    }

    c_log.Log(Info, "Client application terminated");
    return 0;
}
