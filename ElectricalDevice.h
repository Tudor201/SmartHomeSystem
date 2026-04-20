#pragma once
#include "Device.h"

class ElectricalDevice : public Device {
protected:
    bool powerOn;
    double energyUsage;
public:
    ElectricalDevice();
    ElectricalDevice(const std::string& name, const std::string& roomName, bool powerOn, double energyUsage);
    ElectricalDevice(const ElectricalDevice& e);
    ElectricalDevice& operator=(const ElectricalDevice& e);
    virtual ~ElectricalDevice();

    bool isOn() const;
    double getEnergyUsage() const;

    void setEnergyUsage(double energyUsage);

    void turnOn();
    void turnOff();
    void togglePower();
};