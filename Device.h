#pragma once
#include <string>
#include <fstream>
class Device {
private:
    std::string name;
    std::string roomName;

public:
    Device();
    Device(const std::string& name, const std::string& roomName);
    Device(const Device& d);
    Device& operator=(const Device& d);
    virtual ~Device();

    std::string getName() const;
    std::string getRoomName() const;
    void setName(const std::string& name);
    void setRoomName(const std::string& roomName);

    virtual void displayStatus() const = 0;
    virtual void interact() = 0;
    virtual std::string getType() const = 0;
    virtual Device* clone() const = 0;
    virtual void save(std::ofstream& out) const = 0;
};