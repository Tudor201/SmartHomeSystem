#pragma once
#include "ElectricalDevice.h"

class DoorLock : public ElectricalDevice {
private:
    bool locked;
    int failedAttempts;
    int batteryLevel;

public:
    DoorLock();
    DoorLock(const std::string& name, const std::string& roomName, bool powerOn,
             double energyUsage, bool locked, int failedAttempts, int batteryLevel);
    DoorLock(const DoorLock& d);
    DoorLock& operator=(const DoorLock& d);
    ~DoorLock() override;

    bool isLocked() const;
    int getFailedAttempts() const;
    int getBatteryLevel() const;

    void setLocked(bool locked);
    void setFailedAttempts(int failedAttempts);
    void setBatteryLevel(int batteryLevel);

    void lockDoor();
    void unlockDoor();
    void registerFailedAttempt();
    void resetFailedAttempts();

    void displayStatus() const override;
    void interact() override;
    std::string getType() const override;
    Device* clone() const override;
    void save(std::ofstream& out) const override;

    friend std::istream& operator>>(std::istream& in, DoorLock& d);
    friend std::ostream& operator<<(std::ostream& out, const DoorLock& d);
};