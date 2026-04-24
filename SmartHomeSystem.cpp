#include "SmartHomeSystem.h"
#include "Light.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "DoorLock.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>

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
    if (findRoomByName(room.getName()) != nullptr) {
        throw std::runtime_error("Room already exists.");
    }

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

void SmartHomeSystem::loadFromFile(const std::string& fileName) {
    std::ifstream in(fileName);

    if (!in) {
        throw std::runtime_error("File could not be opened.");
    }

    std::string newHomeName;
    int roomCount;

    std::getline(in, newHomeName);

    in >> roomCount;
    if (in.fail() || roomCount < 0) {
        throw std::runtime_error("Invalid room count in file.");
    }

    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<Room> newRooms;

    for (int i = 0; i < roomCount; i++) {
        std::string roomName;
        std::string roomType;
        int deviceCount;

        std::getline(in, roomName);
        std::getline(in, roomType);

        in >> deviceCount;
        if (in.fail() || deviceCount < 0) {
            throw std::runtime_error("Invalid device count in file.");
        }

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        Room room(roomName, roomType);

        for (int j = 0; j < deviceCount; j++) {
            std::string deviceType;
            std::string deviceName;
            std::string deviceRoomName;
            bool powerOn;
            double energyUsage;

            std::getline(in, deviceType);
            std::getline(in, deviceName);
            std::getline(in, deviceRoomName);

            in >> powerOn;
            in >> energyUsage;

            if (in.fail()) {
                throw std::runtime_error("Invalid basic device data in file.");
            }

            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            Device* device = nullptr;

            if (deviceType == "Light") {
                int brightness;
                std::string colorMode;

                in >> brightness;
                if (in.fail()) {
                    throw std::runtime_error("Invalid light data in file.");
                }

                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(in, colorMode);

                device = new Light(
                    deviceName,
                    deviceRoomName,
                    powerOn,
                    energyUsage,
                    brightness,
                    colorMode
                );
            }
            else if (deviceType == "Thermostat") {
                double currentTemperature;
                double targetTemperature;
                bool ecoMode;

                in >> currentTemperature;
                in >> targetTemperature;
                in >> ecoMode;

                if (in.fail()) {
                    throw std::runtime_error("Invalid thermostat data in file.");
                }

                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                device = new Thermostat(
                    deviceName,
                    deviceRoomName,
                    powerOn,
                    energyUsage,
                    currentTemperature,
                    targetTemperature,
                    ecoMode
                );
            }
            else if (deviceType == "SecurityCamera") {
                bool recording;
                bool motionDetected;
                int storageUsed;

                in >> recording;
                in >> motionDetected;
                in >> storageUsed;

                if (in.fail()) {
                    throw std::runtime_error("Invalid security camera data in file.");
                }

                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                device = new SecurityCamera(
                    deviceName,
                    deviceRoomName,
                    powerOn,
                    energyUsage,
                    recording,
                    motionDetected,
                    storageUsed
                );
            }
            else if (deviceType == "DoorLock") {
                bool locked;
                int failedAttempts;
                int batteryLevel;

                in >> locked;
                in >> failedAttempts;
                in >> batteryLevel;

                if (in.fail()) {
                    throw std::runtime_error("Invalid door lock data in file.");
                }

                in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                device = new DoorLock(
                    deviceName,
                    deviceRoomName,
                    powerOn,
                    energyUsage,
                    locked,
                    failedAttempts,
                    batteryLevel
                );
            }
            else {
                throw std::runtime_error("Unknown device type in file.");
            }

            try {
                room.addDevice(device);
            } catch (...) {
                delete device;
                throw;
            }
        }

        newRooms.push_back(room);
    }

    homeName = newHomeName;
    rooms = newRooms;

    in.close();
}

std::istream& operator>>(std::istream& in, SmartHomeSystem& s) {
    std::string homeName;

    std::cout << "Home name: ";
    in >> std::ws;
    std::getline(in, homeName);

    s.setHomeName(homeName);

    return in;
}

std::ostream& operator<<(std::ostream& out, const SmartHomeSystem& s) {
    out << "Smart home name: " << s.getHomeName() << '\n';
    out << "Number of rooms: " << s.getRoomCount() << '\n';
    return out;
}
