#include "SecurityCamera.h"
#include <iostream>
#include <stdexcept>

SecurityCamera::SecurityCamera()
    : ElectricalDevice("N/A", "N/A", false, 0.0),
      recording(false), motionDetected(false), storageUsed(0) {}

SecurityCamera::SecurityCamera(const std::string& name, const std::string& roomName, bool powerOn,
                               double energyUsage, bool recording, bool motionDetected, int storageUsed)
    : ElectricalDevice(name, roomName, powerOn, energyUsage),
      recording(recording), motionDetected(motionDetected), storageUsed(storageUsed) {
    if (storageUsed < 0 || storageUsed > 1000) {
        throw std::runtime_error("Storage used is invalid.");
    }
}

SecurityCamera::SecurityCamera(const SecurityCamera& s)
    : ElectricalDevice(s),
      recording(s.recording), motionDetected(s.motionDetected), storageUsed(s.storageUsed) {}

SecurityCamera& SecurityCamera::operator=(const SecurityCamera& s) {
    if (this != &s) {
        ElectricalDevice::operator=(s);
        recording = s.recording;
        motionDetected = s.motionDetected;
        storageUsed = s.storageUsed;
    }
    return *this;
}

SecurityCamera::~SecurityCamera() {}

bool SecurityCamera::isRecording() const {
    return recording;
}

bool SecurityCamera::hasMotionDetected() const {
    return motionDetected;
}

int SecurityCamera::getStorageUsed() const {
    return storageUsed;
}

void SecurityCamera::setRecording(bool recording) {
    this->recording = recording;
}

void SecurityCamera::setMotionDetected(bool motionDetected) {
    this->motionDetected = motionDetected;
}

void SecurityCamera::setStorageUsed(int storageUsed) {
    if (storageUsed < 0 || storageUsed > 1000) {
        throw std::runtime_error("Storage used is invalid.");
    }
    this->storageUsed = storageUsed;
}

void SecurityCamera::toggleRecording() {
    recording = !recording;
}

void SecurityCamera::detectMotion() {
    motionDetected = true;
    if (isOn()) {
        recording = true;
        storageUsed += 10;
        if (storageUsed > 1000) {
            storageUsed = 1000;
        }
    }
}

void SecurityCamera::clearStorage() {
    storageUsed = 0;
    motionDetected = false;
}

void SecurityCamera::displayStatus() const {
    std::cout<<*this;
}

void SecurityCamera::interact() {
    detectMotion();
}

std::string SecurityCamera::getType() const {
    return "SecurityCamera";
}

Device* SecurityCamera::clone() const {
    return new SecurityCamera(*this);
}

void SecurityCamera::save(std::ofstream& out) const {
    out << "SecurityCamera\n";
    out << getName() << '\n';
    out << getRoomName() << '\n';
    out << isOn() << '\n';
    out << getEnergyUsage() << '\n';
    out << recording << '\n';
    out << motionDetected << '\n';
    out << storageUsed << '\n';
}

std::istream& operator>>(std::istream& in, SecurityCamera& s) {
    std::string name, roomName;
    bool powerOn, recording, motionDetected;
    double energyUsage;
    int storageUsed;

    std::cout << "Name: ";
    in >> std::ws;
    std::getline(in, name);

    std::cout << "Room name: ";
    std::getline(in, roomName);

    std::cout << "Power on (1/0): ";
    in >> powerOn;

    std::cout << "Energy usage: ";
    in >> energyUsage;

    std::cout << "Recording (1/0): ";
    in >> recording;

    std::cout << "Motion detected (1/0): ";
    in >> motionDetected;

    std::cout << "Storage used: ";
    in >> storageUsed;

    s.setName(name);
    s.setRoomName(roomName);
    if (powerOn) s.turnOn();
    else s.turnOff();
    s.setEnergyUsage(energyUsage);
    s.setRecording(recording);
    s.setMotionDetected(motionDetected);
    s.setStorageUsed(storageUsed);

    return in;
}

std::ostream& operator<<(std::ostream& out, const SecurityCamera& s) {
    out << "Device type: SecurityCamera\n";
    out << "Name: " << s.getName() << '\n';
    out << "Room: " << s.getRoomName() << '\n';
    out << "Power: " << (s.isOn() ? "On" : "Off") << '\n';
    out << "Energy usage: " << s.getEnergyUsage() << '\n';
    out << "Recording: " << (s.isRecording() ? "Yes" : "No") << '\n';
    out << "Motion detected: " << (s.hasMotionDetected() ? "Yes" : "No") << '\n';
    out << "Storage used: " << s.getStorageUsed() << '\n';
    return out;
}