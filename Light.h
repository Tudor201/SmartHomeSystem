#pragma once
#include "ElectricalDevice.h"

class Light : public ElectricalDevice {
private:
    int brightness;
    std::string colorMode;
public:
    Light();
    Light(const std::string& name, const std::string& roomName, bool powerOn, double energyUsage, int brightness, const std::string& colorMode);
    Light(const Light& l);
    Light& operator=(const Light& l);
    ~Light() override;

    int getBrightness() const;
    std::string getColorMode() const;

    void setBrightness(int brightness);
    void setColorMode(const std::string& colorMode);

    void setReadingMode();
    void setNightMode();

    void displayStatus() const override;
    void interact() override;
    std::string getType() const override;
    Device* clone() const override;
    void save(std::ofstream& out) const override;

    friend std::istream& operator>>(std::istream& in, Light& l);
    friend std::ostream& operator<<(std::ostream& out, const Light& l);
};