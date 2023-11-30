#ifndef TRACKERDATA_HPP
#define TRACKERDATA_HPP

#include "../utils/Logger.hpp"
#include <string>
#include <unordered_map>
#include <unordered_set>

class TrackerData {
public:
    TrackerData(BasicLogger& logger);
    bool AddUser(const std::string& userId, const std::string& password);
    bool CreateGroup(const std::string& groupId, const std::string& ownerId);
    ~TrackerData();

private:
    struct User { /* ... */ };

    struct Group {
        std::string groupId;
        std::string ownerId;
        std::unordered_set<std::string> members;

        Group(const std::string& id, const std::string& owner)
            : groupId(id), ownerId(owner) {}
    };

    std::unordered_map<std::string, User> users;
    std::unordered_map<std::string, Group> groups;
    BasicLogger& log;
};

#endif // TRACKERDATA_HPP
