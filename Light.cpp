#include "Light.h"
#include <iostream>
#include <stdexcept>

Light::Light() : ElectricalDevice("N/A", "N/A", false, 0.0), brightness(50), colorMode("neutral") {}

Light::Light(const std::string& name, const std::string& roomName, bool powerOn, double energyUsage, int brightness, const std::string& colorMode)
    : ElectricalDevice(name, roomName, powerOn, energyUsage), brightness(brightness), colorMode(colorMode) {
    if (brightness < 0 || brightness > 100) {
        throw std::runtime_error("Brightness must be between 0 and 100.");
    }
}

Light::Light(const Light& l)
    : ElectricalDevice(l), brightness(l.brightness), colorMode(l.colorMode) {}

Light& Light::operator=(const Light& l) {
    if (this != &l) {
        ElectricalDevice::operator=(l);
        brightness = l.brightness;
        colorMode = l.colorMode;
    }
    return *this;
}

Light::~Light() {}

int Light::getBrightness() const {
    return brightness;
}

std::string Light::getColorMode() const {
    return colorMode;
}

void Light::setBrightness(int brightness) {
    if (brightness < 0 || brightness > 100) {
        throw std::runtime_error("Brightness must be between 0 and 100.");
    }
    this->brightness = brightness;
}

void Light::setColorMode(const std::string& colorMode) {
    this->colorMode = colorMode;
}

void Light::setReadingMode() {
    turnOn();
    brightness = 80;
    colorMode = "warm";
}

void Light::setNightMode() {
    turnOn();
    brightness = 20;
    colorMode = "night";
}

void Light::displayStatus() const {
    std::cout << "Device type: Light\n";
    std::cout << "Name: " << getName() << '\n';
    std::cout << "Room: " << getRoomName() << '\n';
    std::cout << "Power: " << (isOn() ? "On" : "Off") << '\n';
    std::cout << "Energy usage: " << getEnergyUsage() << '\n';
    std::cout << "Brightness: " << brightness << '\n';
    std::cout << "Color mode: " << colorMode << '\n';
}

void Light::interact() {
    togglePower();
}

std::string Light::getType() const {
    return "Light";
}

Device* Light::clone() const {
    return new Light(*this);
}

void Light::save(std::ofstream& out) const {
    out << "Light\n";
    out << getName() << '\n';
    out << getRoomName() << '\n';
    out << isOn() << '\n';
    out << getEnergyUsage() << '\n';
    out << brightness << '\n';
    out << colorMode << '\n';
}