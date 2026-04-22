#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Device.h"

class Room {
private:
    std::string name;
    std::string type;
    std::vector<Device*> devices;

public:
    Room();
    Room(const std::string& name, const std::string& type);
    Room(const Room& r);
    Room& operator=(const Room& r);
    ~Room();

    std::string getName() const;
    std::string getType() const;
    int getDeviceCount() const;

    void setName(const std::string& name);
    void setType(const std::string& type);

    void addDevice(Device* device);
    void removeDeviceByIndex(int index);
    Device* findDeviceByName(const std::string& name) const;
    Device* getDeviceByIndex(int index) const;

    void displayDevices() const;
    void applyNightMode();
    void applyAwayMode();

    void save(std::ofstream& out) const;

    friend std::istream& operator>>(std::istream& in, Room& r);
    friend std::ostream& operator<<(std::ostream& out, const Room& r);
};