#include "Room.h"
#include "Light.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "DoorLock.h"
#include <iostream>
#include <stdexcept>

Room::Room() : name("N/A"), type("N/A") {}

Room::Room(const std::string &name, const std::string &type) : name(name), type(type) {}

Room::Room(const Room& r) : name(r.name), type(r.type) {
    for (size_t i = 0; i < r.devices.size(); i++) {
        devices.push_back(r.devices[i]->clone());
    }
}

Room& Room::operator=(const Room& r) {
    if (this != &r) {
        for (size_t i = 0; i < devices.size() ; i++) {
            delete devices[i];
        }
        devices.clear();

        name = r.name;
        type = r.type;

        for (size_t i = 0; i < r.devices.size(); i++) {
            devices.push_back(r.devices[i]->clone());
        }
    }
    return *this;
}

Room::~Room() {
    for (size_t i = 0; i < devices.size(); i++) {
        delete devices[i];
    }
    devices.clear();
}

std::string Room::getName() const {
    return name;
}

std::string Room::getType() const {
    return type;
}

int Room::getDeviceCount() const {
    return static_cast<int>(devices.size());
}

void Room::setName(const std::string& name) {
    this->name = name;
}

void Room::setType(const std::string& type) {
    this->type = type;
}

void Room::addDevice(Device* device) {
    if (device == nullptr) {
        throw std::invalid_argument("Cannot add a null device");
    }
    devices.push_back(device);
}

void Room::removeDeviceByIndex(int index) {
    if (index < 0 || index >= static_cast<int>(devices.size())) {
        throw std::runtime_error("Invalid device index.");
    }

    delete devices[index];
    devices.erase(devices.begin() + index);
}

Device* Room::findDeviceByName(const std::string& name) const {
    for (size_t i = 0; i < devices.size(); i++) {
        if (devices[i]->getName() == name) {
            return devices[i];
        }
    }
    return nullptr;
}

Device* Room::getDeviceByIndex(int index) const {
    if (index < 0 || index >= static_cast<int>(devices.size())) {
        throw std::runtime_error("Invalid device index.");
    }
    return devices[index];
}

void Room::displayDevices() const {
    std::cout << "Room: " << name << " (" << type << ")\n";
    if (devices.empty()) {
        std::cout << "No devices in this room.\n";
        return;
    }

    for (size_t i = 0; i < devices.size(); i++) {
        std::cout << "\nDevice #" << i + 1 << ":\n";
        devices[i]->displayStatus();
    }
}

void Room::applyNightMode() {
    for (size_t i = 0; i < devices.size(); i++) {
        if (Light* light = dynamic_cast<Light*>(devices[i])) {
            light->setNightMode();
        } else if (SecurityCamera* camera = dynamic_cast<SecurityCamera*>(devices[i])) {
            camera->turnOn();
            camera->setRecording(true);
        } else if (DoorLock* doorLock = dynamic_cast<DoorLock*>(devices[i])) {
            doorLock->turnOn();
            doorLock->lockDoor();
        }
    }
}

void Room::applyAwayMode() {
    for (size_t i = 0; i < devices.size(); i++) {
        if (Light* light = dynamic_cast<Light*>(devices[i])) {
            light->turnOff();
        } else if (SecurityCamera* camera = dynamic_cast<SecurityCamera*>(devices[i])) {
            camera->turnOn();
            camera->setRecording(true);
        } else if (DoorLock* doorLock = dynamic_cast<DoorLock*>(devices[i])) {
            doorLock->turnOn();
            doorLock->lockDoor();
        } else if (Thermostat* thermostat = dynamic_cast<Thermostat*>(devices[i])) {
            thermostat->turnOn();
            thermostat->setEcoMode(true);
        }
    }
}

void Room::save(std::ofstream& out) const {
    out << name << '\n';
    out << type << '\n';
    out << devices.size() << '\n';

    for (size_t i = 0; i < devices.size(); i++) {
        devices[i]->save(out);
    }
}

std::istream& operator>>(std::istream& in, Room& r) {
    std::string name, type;

    std::cout << "Room name: ";
    in >> std::ws;
    std::getline(in, name);

    std::cout << "Room type: ";
    std::getline(in, type);

    r.setName(name);
    r.setType(type);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Room& r) {
    out << "Room name: " << r.getName() << '\n';
    out << "Room type: " << r.getType() << '\n';
    out << "Number of devices: " << r.getDeviceCount() << '\n';
    return out;
}