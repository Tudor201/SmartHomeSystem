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
    std::cout<<*this;
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

std::istream& operator>>(std::istream& in, Light& l) {
    std::string name, roomName, colorMode;
    bool powerOn;
    double energyUsage;
    int brightness;

    std::cout << "Name: ";
    in >> std::ws;
    std::getline(in, name);

    std::cout << "Room name: ";
    std::getline(in, roomName);

    std::cout << "Power on (1/0): ";
    in >> powerOn;

    std::cout << "Energy usage: ";
    in >> energyUsage;

    std::cout << "Brightness: ";
    in >> brightness;
    in >> std::ws;

    std::cout << "Color mode: ";
    std::getline(in, colorMode);

    l.setName(name);
    l.setRoomName(roomName);
    if (powerOn) l.turnOn();
    else l.turnOff();
    l.setEnergyUsage(energyUsage);
    l.setBrightness(brightness);
    l.setColorMode(colorMode);

    return in;
}

std::ostream& operator<<(std::ostream& out, const Light& l) {
    out << "Device type: Light\n";
    out << "Name: " << l.getName() << '\n';
    out << "Room: " << l.getRoomName() << '\n';
    out << "Power: " << (l.isOn() ? "On" : "Off") << '\n';
    out << "Energy usage: " << l.getEnergyUsage() << '\n';
    out << "Brightness: " << l.getBrightness() << '\n';
    out << "Color mode: " << l.getColorMode() << '\n';
    return out;
}