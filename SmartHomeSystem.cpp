#include "SmartHomeSystem.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

SmartHomeSystem::SmartHomeSystem() : homeName("Home1") {}

SmartHomeSystem::SmartHomeSystem(const std::string &homeName) : homeName(homeName) {}

SmartHomeSystem::SmartHomeSystem(const SmartHomeSystem &s) : homeName(s.homeName), rooms(s.rooms) {}

SmartHomeSystem& SmartHomeSystem::operator=(const SmartHomeSystem &s) {
    if (this != &s) {
        homeName = s.homeName;
        rooms = s.rooms;
    }
    return *this;
}

SmartHomeSystem::~SmartHomeSystem() {}

std::string SmartHomeSystem::getHomeName() const { return homeName; }

int SmartHomeSystem::getRoomCount() const {
    return static_cast<int>(rooms.size());
}

void SmartHomeSystem::setHomeName(const std::string& homeName) {
    this->homeName = homeName;
}

void SmartHomeSystem::addRoom(const Room& room) {
    rooms.push_back(room);
}

void SmartHomeSystem::removeRoomByName(const std::string &roomName) {
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i].getName() == roomName) {
            rooms.erase(rooms.begin() + i);
            return;
        }
    }
    throw std::runtime_error("Room not found");
}

Room *SmartHomeSystem::findRoomByName(const std::string &roomName) {
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i].getName() == roomName) {
            return &rooms[i];
        }
    }
    return nullptr;
}

void SmartHomeSystem::addDeviceToRoom(const std::string& roomName, Device* device) {
    Room* room = findRoomByName(roomName);
    if (room == nullptr) {
        throw std::runtime_error("Room not found.");
    }
    room->addDevice(device);
}

void SmartHomeSystem::displayAllRooms() const {
    std::cout << "Home: " << homeName << '\n';

    if (rooms.empty()) {
        std::cout << "No rooms available.\n";
        return;
    }

    for (size_t i = 0; i < rooms.size(); i++) {
        std::cout << i + 1 << ". " << rooms[i].getName()
                  << " (" << rooms[i].getType() << ")\n";
    }
}

void SmartHomeSystem::displayFullStatus() const {
    std::cout << "Smart Home: " << homeName << '\n';

    if (rooms.empty()) {
        std::cout << "No rooms available.\n";
        return;
    }

    for (size_t i = 0; i < rooms.size(); i++) {
        std::cout << "\n====================\n";
        rooms[i].displayDevices();
    }
}

void SmartHomeSystem::applyNightMode() {
    for (size_t i = 0; i < rooms.size(); i++) {
        rooms[i].applyNightMode();
    }
}

void SmartHomeSystem::applyAwayMode() {
    for (size_t i = 0; i < rooms.size(); i++) {
        rooms[i].applyAwayMode();
    }
}

void SmartHomeSystem::saveToFile(const std::string& fileName) const {
    std::ofstream out(fileName);

    if (!out) {
        throw std::runtime_error("File could not be opened.");
    }

    out << homeName << '\n';
    out << rooms.size() << '\n';

    for (size_t i = 0; i < rooms.size(); i++) {
        rooms[i].save(out);
    }

    out.close();
}
