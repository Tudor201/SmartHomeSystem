#include "DoorLock.h"
#include <iostream>
#include <stdexcept>

DoorLock::DoorLock()
    : ElectricalDevice("N/A", "N/A", false, 0.0),
      locked(true), failedAttempts(0), batteryLevel(100) {}

DoorLock::DoorLock(const std::string& name, const std::string& roomName, bool powerOn,
                   double energyUsage, bool locked, int failedAttempts, int batteryLevel)
    : ElectricalDevice(name, roomName, powerOn, energyUsage),
      locked(locked), failedAttempts(failedAttempts), batteryLevel(batteryLevel) {
    if (failedAttempts < 0) {
        throw std::runtime_error("Failed attempts cannot be negative.");
    }
    if (batteryLevel < 0 || batteryLevel > 100) {
        throw std::runtime_error("Battery level must be between 0 and 100.");
    }
}

DoorLock::DoorLock(const DoorLock& d)
    : ElectricalDevice(d),
      locked(d.locked), failedAttempts(d.failedAttempts), batteryLevel(d.batteryLevel) {}

DoorLock& DoorLock::operator=(const DoorLock& d) {
    if (this != &d) {
        ElectricalDevice::operator=(d);
        locked = d.locked;
        failedAttempts = d.failedAttempts;
        batteryLevel = d.batteryLevel;
    }
    return *this;
}

DoorLock::~DoorLock() {}

bool DoorLock::isLocked() const {
    return locked;
}

int DoorLock::getFailedAttempts() const {
    return failedAttempts;
}

int DoorLock::getBatteryLevel() const {
    return batteryLevel;
}

void DoorLock::setLocked(bool locked) {
    this->locked = locked;
}

void DoorLock::setFailedAttempts(int failedAttempts) {
    if (failedAttempts < 0) {
        throw std::runtime_error("Failed attempts cannot be negative.");
    }
    this->failedAttempts = failedAttempts;
}

void DoorLock::setBatteryLevel(int batteryLevel) {
    if (batteryLevel < 0 || batteryLevel > 100) {
        throw std::runtime_error("Battery level must be between 0 and 100.");
    }
    this->batteryLevel = batteryLevel;
}

void DoorLock::lockDoor() {
    if (isOn()) {
        locked = true;
    }
}

void DoorLock::unlockDoor() {
    if (isOn() && batteryLevel > 0 && failedAttempts < 3) {
        locked = false;
    }
}

void DoorLock::registerFailedAttempt() {
    failedAttempts++;
    if (failedAttempts >= 3) {
        locked = true;
    }
}

void DoorLock::resetFailedAttempts() {
    failedAttempts = 0;
}

void DoorLock::displayStatus() const {
    std::cout << "Device type: DoorLock\n";
    std::cout << "Name: " << getName() << '\n';
    std::cout << "Room: " << getRoomName() << '\n';
    std::cout << "Power: " << (isOn() ? "On" : "Off") << '\n';
    std::cout << "Energy usage: " << getEnergyUsage() << '\n';
    std::cout << "Locked: " << (locked ? "Yes" : "No") << '\n';
    std::cout << "Failed attempts: " << failedAttempts << '\n';
    std::cout << "Battery level: " << batteryLevel << '\n';
}

void DoorLock::interact() {
    if (locked) {
        unlockDoor();
    } else {
        lockDoor();
    }
}

std::string DoorLock::getType() const {
    return "DoorLock";
}

Device* DoorLock::clone() const {
    return new DoorLock(*this);
}

void DoorLock::save(std::ofstream& out) const {
    out << "DoorLock\n";
    out << getName() << '\n';
    out << getRoomName() << '\n';
    out << isOn() << '\n';
    out << getEnergyUsage() << '\n';
    out << locked << '\n';
    out << failedAttempts << '\n';
    out << batteryLevel << '\n';
}

std::istream& operator>>(std::istream& in, DoorLock& d) {
    std::string name, roomName;
    bool powerOn, locked;
    double energyUsage;
    int failedAttempts, batteryLevel;

    std::cout << "Name: ";
    in >> std::ws;
    std::getline(in, name);

    std::cout << "Room name: ";
    std::getline(in, roomName);

    std::cout << "Power on (1/0): ";
    in >> powerOn;

    std::cout << "Energy usage: ";
    in >> energyUsage;

    std::cout << "Locked (1/0): ";
    in >> locked;

    std::cout << "Failed attempts: ";
    in >> failedAttempts;

    std::cout << "Battery level: ";
    in >> batteryLevel;

    d.setName(name);
    d.setRoomName(roomName);
    if (powerOn) d.turnOn();
    else d.turnOff();
    d.setEnergyUsage(energyUsage);
    d.setLocked(locked);
    d.setFailedAttempts(failedAttempts);
    d.setBatteryLevel(batteryLevel);

    return in;
}

std::ostream& operator<<(std::ostream& out, const DoorLock& d) {
    out << "Device type: DoorLock\n";
    out << "Name: " << d.getName() << '\n';
    out << "Room: " << d.getRoomName() << '\n';
    out << "Power: " << (d.isOn() ? "On" : "Off") << '\n';
    out << "Energy usage: " << d.getEnergyUsage() << '\n';
    out << "Locked: " << (d.isLocked() ? "Yes" : "No") << '\n';
    out << "Failed attempts: " << d.getFailedAttempts() << '\n';
    out << "Battery level: " << d.getBatteryLevel() << '\n';
    return out;
}