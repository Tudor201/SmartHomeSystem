#pragma once
#include <string>
#include <vector>
#include "Room.h"

class SmartHomeSystem {
private:
    std::string homeName;
    std::vector<Room> rooms;

public:
    SmartHomeSystem();
    SmartHomeSystem(const std::string& homeName);
    SmartHomeSystem(const SmartHomeSystem& s);
    SmartHomeSystem& operator=(const SmartHomeSystem& s);
    ~SmartHomeSystem();

    std::string getHomeName() const;
    int getRoomCount() const;

    void setHomeName(const std::string& homeName);

    void addRoom(const Room& room);
    void removeRoomByName(const std::string& roomName);
    Room* findRoomByName(const std::string& roomName);

    void addDeviceToRoom(const std::string& roomName, Device* device);

    void displayAllRooms() const;
    void displayFullStatus() const;

    void applyNightMode();
    void applyAwayMode();

    void saveToFile(const std::string& fileName) const;
};