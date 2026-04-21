#pragma once
#include "ElectricalDevice.h"

class Thermostat : public ElectricalDevice {
private:
    double currentTemperature;
    double targetTemperature;
    bool ecoMode;
public:
    Thermostat();
    Thermostat(const std::string& name, const std::string& roomName, bool powerOn, double energyUsage, double currentTemperature, double targetTemperature, bool ecoMode);
    Thermostat(const Thermostat& t);
    Thermostat& operator=(const Thermostat& t);
    ~Thermostat() override;

    double getCurrentTemperature() const;
    double getTargetTemperature() const;
    bool isEcoModeOn() const;

    void setCurrentTemperature(double currentTemperature);
    void setTargetTemperature(double targetTemperature);
    void setEcoMode(bool ecoMode);

    void toggleEcoMode();
    void adjustTemperature();

    void displayStatus() const override;
    void interact() override;
    std::string getType() const override;
    Device* clone() const override;
    void save(std::ofstream& out) const override;
};