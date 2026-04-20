#include "Device.h"

Device::Device() : name("N/A"), roomName("N/A") {}

Device::Device(const std::string &name, const std::string &roomName) : name(name), roomName(roomName) {}

Device::Device(const Device &d) : name(d.name), roomName(d.roomName) {}

Device& Device::operator=(const Device &d) {
    if (this != &d) {
        name = d.name;
        roomName = d.roomName;
    }
    return *this;
}

Device::~Device() {}

std::string Device::getName() const { return name; }
std::string Device::getRoomName() const { return roomName; }
void Device::setName(const std::string &name) { this->name = name; }
void Device::setRoomName(const std::string &roomName) { this->roomName = roomName; }