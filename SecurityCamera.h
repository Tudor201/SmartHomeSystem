#pragma once
#include "ElectricalDevice.h"

class SecurityCamera : public ElectricalDevice {
private:
    bool recording;
    bool motionDetected;
    int storageUsed;
 public:
    SecurityCamera();
    SecurityCamera(const std::string& name, const std::string& roomName, bool powerOn, double energyUsage, bool recording, bool motionDetected, int storageUsed);
    SecurityCamera(const SecurityCamera& s);
    SecurityCamera& operator=(const SecurityCamera& s);
    ~SecurityCamera();

    bool isRecording() const;
    bool hasMotionDetected() const;
    int getStorageUsed() const;

    void setRecording(bool recording);
    void setMotionDetected(bool motionDetected);
    void setStorageUsed(int storageUsed);

    void toggleRecording();
    void detectMotion();
    void clearStorage();

    void displayStatus() const override;
    void interact() override;
    std::string getType() const override;
    Device* clone() const override;
    void save(std::ofstream& out) const override;

    friend std::istream& operator>>(std::istream& in, SecurityCamera& s);
    friend std::ostream& operator<<(std::ostream& out, const SecurityCamera& s);
};