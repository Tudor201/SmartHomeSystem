#include "Thermostat.h"
#include <iostream>
#include <stdexcept>

Thermostat::Thermostat()
    : ElectricalDevice("N/A", "N/A", false, 0.0),
      currentTemperature(20.0), targetTemperature(22.0), ecoMode(false) {}

Thermostat::Thermostat(const std::string& name, const std::string& roomName, bool powerOn,
                       double energyUsage, double currentTemperature, double targetTemperature, bool ecoMode)
    : ElectricalDevice(name, roomName, powerOn, energyUsage),
      currentTemperature(currentTemperature), targetTemperature(targetTemperature), ecoMode(ecoMode) {
    if (currentTemperature < -30 || currentTemperature > 50) {
        throw std::runtime_error("Current temperature is invalid.");
    }
    if (targetTemperature < 5 || targetTemperature > 35) {
        throw std::runtime_error("Target temperature is invalid.");
    }
}

Thermostat::Thermostat(const Thermostat &t) : ElectricalDevice(t), currentTemperature(t.currentTemperature), targetTemperature(t.targetTemperature), ecoMode(t.ecoMode) {}

Thermostat& Thermostat::operator=(const Thermostat& t) {
    if (this != &t) {
        ElectricalDevice::operator=(t);
        currentTemperature = t.currentTemperature;
        targetTemperature = t.targetTemperature;
        ecoMode = t.ecoMode;
    }
    return *this;
}

Thermostat::~Thermostat() {}

double Thermostat::getCurrentTemperature() const {
    return currentTemperature;
}

double Thermostat::getTargetTemperature() const {
    return targetTemperature;
}

bool Thermostat::isEcoModeOn() const {
    return ecoMode;
}

void Thermostat::setCurrentTemperature(double currentTemperature) {
    if (currentTemperature < -30 || currentTemperature > 50) {
        throw std::runtime_error("Current temperature is invalid.");
    }
    this->currentTemperature = currentTemperature;
}

void Thermostat::setTargetTemperature(double targetTemperature) {
    if (targetTemperature < 5 || targetTemperature > 35) {
        throw std::runtime_error("Target temperature is invalid.");
    }
    this->targetTemperature = targetTemperature;
}

void Thermostat::setEcoMode(bool ecoMode) {
    this->ecoMode = ecoMode;
}

void Thermostat::toggleEcoMode() {
    ecoMode = !ecoMode;
}

void Thermostat::adjustTemperature() {
    if (!isOn()) {
        return;
    }

    if (currentTemperature < targetTemperature) {
        currentTemperature += 0.5;
        if (currentTemperature > targetTemperature) {
            currentTemperature = targetTemperature;
        }
    } else if (currentTemperature > targetTemperature) {
        currentTemperature -= 0.5;
        if (currentTemperature < targetTemperature) {
            currentTemperature = targetTemperature;
        }
    }
}

void Thermostat::displayStatus() const {
    std::cout << "Device type: Thermostat\n";
    std::cout << "Name: " << getName() << '\n';
    std::cout << "Room: " << getRoomName() << '\n';
    std::cout << "Power: " << (isOn() ? "On" : "Off") << '\n';
    std::cout << "Energy usage: " << getEnergyUsage() << '\n';
    std::cout << "Current temperature: " << currentTemperature << '\n';
    std::cout << "Target temperature: " << targetTemperature << '\n';
    std::cout << "Eco mode: " << (ecoMode ? "On" : "Off") << '\n';
}

void Thermostat::interact() {
    adjustTemperature();
}

std::string Thermostat::getType() const {
    return "Thermostat";
}

Device* Thermostat::clone() const {
    return new Thermostat(*this);
}

void Thermostat::save(std::ofstream& out) const {
    out << "Thermostat\n";
    out << getName() << '\n';
    out << getRoomName() << '\n';
    out << isOn() << '\n';
    out << getEnergyUsage() << '\n';
    out << currentTemperature << '\n';
    out << targetTemperature << '\n';
    out << ecoMode << '\n';
}

std::istream& operator>>(std::istream& in, Thermostat& t) {
    std::string name, roomName;
    bool powerOn, ecoMode;
    double energyUsage, currentTemperature, targetTemperature;

    std::cout << "Name: ";
    in >> std::ws;
    std::getline(in, name);

    std::cout << "Room name: ";
    std::getline(in, roomName);

    std::cout << "Power on (1/0): ";
    in >> powerOn;

    std::cout << "Energy usage: ";
    in >> energyUsage;

    std::cout << "Current temperature: ";
    in >> currentTemperature;

    std::cout << "Target temperature: ";
    in >> targetTemperature;

    std::cout << "Eco mode (1/0): ";
    in >> ecoMode;

    t.setName(name);
    t.setRoomName(roomName);
    if (powerOn) t.turnOn();
    else t.turnOff();
    t.setEnergyUsage(energyUsage);
    t.setCurrentTemperature(currentTemperature);
    t.setTargetTemperature(targetTemperature);
    t.setEcoMode(ecoMode);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Thermostat& t) {
    out << "Device type: Thermostat\n";
    out << "Name: " << t.getName() << '\n';
    out << "Room: " << t.getRoomName() << '\n';
    out << "Power: " << (t.isOn() ? "On" : "Off") << '\n';
    out << "Energy usage: " << t.getEnergyUsage() << '\n';
    out << "Current temperature: " << t.getCurrentTemperature() << '\n';
    out << "Target temperature: " << t.getTargetTemperature() << '\n';
    out << "Eco mode: " << (t.isEcoModeOn() ? "On" : "Off") << '\n';
    return out;
}