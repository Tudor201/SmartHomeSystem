#include "ElectricalDevice.h"

ElectricalDevice::ElectricalDevice() : Device(), powerOn(false), energyUsage(0.0) {}

ElectricalDevice::ElectricalDevice(const std::string& name, const std::string& roomName, bool powerOn, double energyUsage) : Device(name, roomName), powerOn(powerOn), energyUsage(energyUsage) {}

ElectricalDevice::ElectricalDevice(const ElectricalDevice &e) : Device(e), powerOn(e.powerOn), energyUsage(e.energyUsage) {}

ElectricalDevice& ElectricalDevice::operator=(const ElectricalDevice &e) {
    if (this != &e) {
        Device::operator=(e);
        powerOn = e.powerOn;
        energyUsage = e.energyUsage;
    }
    return *this;
}

ElectricalDevice::~ElectricalDevice() {}

bool ElectricalDevice::isOn() const { return powerOn; }
double ElectricalDevice::getEnergyUsage() const { return energyUsage; }
void ElectricalDevice::setEnergyUsage(double energyUsage) { this->energyUsage = energyUsage; }
void ElectricalDevice::turnOn() { powerOn = true; }
void ElectricalDevice::turnOff() { powerOn = false; }
void ElectricalDevice::togglePower() { powerOn = !powerOn; }

