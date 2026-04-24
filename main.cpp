#include <iostream>
#include <string>
#include <limits>
#include "SmartHomeSystem.h"
#include "Light.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "DoorLock.h"

void showMenu() {
    std::cout << "\n===== SMART HOME SYSTEM =====\n";
    std::cout << "1. Add room\n";
    std::cout << "2. Show all rooms\n";
    std::cout << "3. Add device to room\n";
    std::cout << "4. Show full home status\n";
    std::cout << "5. Apply night mode\n";
    std::cout << "6. Apply away mode\n";
    std::cout << "7. Save to file\n";
    std::cout << "8. Control a device from a room\n";
    std::cout << "9. Remove room\n";
    std::cout << "10. Remove device from room\n";
    std::cout << "Load from file\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

void showDeviceControlMenu() {
    std::cout << "\nChoose action:\n";
    std::cout << "1. Interact\n";
    std::cout << "2. Display device status\n";
    std::cout << "3. Special action (depending on type)\n";
    std::cout << "0. Back\n";
    std::cout << "Option: ";
}

int main() {
    SmartHomeSystem home;
    int option;

    try {
        home.loadFromFile("defaults.txt");
        std::cout << "Default configuration loaded from defaults.txt.\n";
    }
    catch (const std::exception& e) {
        std::cout << "Could not load defaults.txt: " << e.what() << '\n';
        std::cout << "Starting with an empty smart home.\n";
    }

    do {
        showMenu();
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            if (option == 1) {
                std::string roomName, roomType;

                std::cout << "Enter room name: ";
                std::getline(std::cin, roomName);

                std::cout << "Enter room type: ";
                std::getline(std::cin, roomType);

                Room room(roomName, roomType);
                home.addRoom(room);

                std::cout << "Room added successfully.\n";
            }
            else if (option == 2) {
                home.displayAllRooms();
            }
            else if (option == 3) {
                std::string roomName;
                int deviceType;

                std::cout << "Enter room name: ";
                std::getline(std::cin, roomName);

                std::cout << "Choose device type:\n";
                std::cout << "1. Light\n";
                std::cout << "2. Thermostat\n";
                std::cout << "3. Security Camera\n";
                std::cout << "4. Door Lock\n";
                std::cout << "Option: ";
                std::cin >> deviceType;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Invalid device type.");
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string deviceName;
                bool powerOn;
                double energyUsage;

                std::cout << "Enter device name: ";
                std::getline(std::cin, deviceName);

                std::cout << "Power on? (1 = yes, 0 = no): ";
                std::cin >> powerOn;

                std::cout << "Enter energy usage: ";
                std::cin >> energyUsage;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Invalid device data.");
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Device* device = nullptr;

                if (deviceType == 1) {
                    int brightness;
                    std::string colorMode;

                    std::cout << "Enter brightness (0-100): ";
                    std::cin >> brightness;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Enter color mode: ";
                    std::getline(std::cin, colorMode);

                    device = new Light(deviceName, roomName, powerOn, energyUsage, brightness, colorMode);
                }
                else if (deviceType == 2) {
                    double currentTemperature, targetTemperature;
                    bool ecoMode;

                    std::cout << "Enter current temperature: ";
                    std::cin >> currentTemperature;

                    std::cout << "Enter target temperature: ";
                    std::cin >> targetTemperature;

                    std::cout << "Eco mode? (1 = yes, 0 = no): ";
                    std::cin >> ecoMode;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::runtime_error("Invalid thermostat data.");
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    device = new Thermostat(deviceName, roomName, powerOn, energyUsage,
                                            currentTemperature, targetTemperature, ecoMode);
                }
                else if (deviceType == 3) {
                    bool recording, motionDetected;
                    int storageUsed;

                    std::cout << "Recording? (1 = yes, 0 = no): ";
                    std::cin >> recording;

                    std::cout << "Motion detected? (1 = yes, 0 = no): ";
                    std::cin >> motionDetected;

                    std::cout << "Storage used: ";
                    std::cin >> storageUsed;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::runtime_error("Invalid security camera data.");
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    device = new SecurityCamera(deviceName, roomName, powerOn, energyUsage,
                                                recording, motionDetected, storageUsed);
                }
                else if (deviceType == 4) {
                    bool locked;
                    int failedAttempts, batteryLevel;

                    std::cout << "Locked? (1 = yes, 0 = no): ";
                    std::cin >> locked;

                    std::cout << "Failed attempts: ";
                    std::cin >> failedAttempts;

                    std::cout << "Battery level (0-100): ";
                    std::cin >> batteryLevel;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw std::runtime_error("Invalid door lock data.");
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    device = new DoorLock(deviceName, roomName, powerOn, energyUsage,
                                          locked, failedAttempts, batteryLevel);
                }
                else {
                    throw std::runtime_error("Invalid device type.");
                }

                try {
                    home.addDeviceToRoom(roomName, device);
                }
                catch (...) {
                    delete device;
                    throw;
                }

                std::cout << "Device added successfully.\n";
            }
            else if (option == 4) {
                home.displayFullStatus();
            }
            else if (option == 5) {
                home.applyNightMode();
                std::cout << "Night mode applied.\n";
            }
            else if (option == 6) {
                home.applyAwayMode();
                std::cout << "Away mode applied.\n";
            }
            else if (option == 7) {
                std::string fileName;
                std::cout << "Enter file name: ";
                std::getline(std::cin, fileName);

                home.saveToFile(fileName);
                std::cout << "Data saved successfully.\n";
            }
            else if (option == 8) {
                std::string roomName;
                int index;
                int controlOption;

                std::cout << "Enter room name: ";
                std::getline(std::cin, roomName);

                Room* room = home.findRoomByName(roomName);
                if (room == nullptr) {
                    throw std::runtime_error("Room not found.");
                }

                room->displayDevices();

                std::cout << "\nChoose device index: ";
                std::cin >> index;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Invalid device index.");
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                Device* d = room->getDeviceByIndex(index - 1);

                showDeviceControlMenu();
                std::cin >> controlOption;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Invalid control option.");
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (controlOption == 1) {
                    d->interact();
                    std::cout << "Generic interact executed.\n";
                }
                else if (controlOption == 2) {
                    d->displayStatus();
                }
                else if (controlOption == 3) {
                    if (Light* light = dynamic_cast<Light*>(d)) {
                        int lightOption;
                        std::cout << "\n1. Reading mode\n2. Night mode\n3. Toggle power\nOption: ";
                        std::cin >> lightOption;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (lightOption == 1) light->setReadingMode();
                        else if (lightOption == 2) light->setNightMode();
                        else if (lightOption == 3) light->togglePower();
                        else std::cout << "Invalid option.\n";
                    }
                    else if (Thermostat* thermostat = dynamic_cast<Thermostat*>(d)) {
                        int thOption;
                        std::cout << "\n1. Toggle eco mode\n2. Adjust temperature\n3. Toggle power\nOption: ";
                        std::cin >> thOption;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (thOption == 1) thermostat->toggleEcoMode();
                        else if (thOption == 2) thermostat->adjustTemperature();
                        else if (thOption == 3) thermostat->togglePower();
                        else std::cout << "Invalid option.\n";
                    }
                    else if (SecurityCamera* camera = dynamic_cast<SecurityCamera*>(d)) {
                        int camOption;
                        std::cout << "\n1. Toggle recording\n2. Detect motion\n3. Clear storage\n4. Toggle power\nOption: ";
                        std::cin >> camOption;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (camOption == 1) camera->toggleRecording();
                        else if (camOption == 2) camera->detectMotion();
                        else if (camOption == 3) camera->clearStorage();
                        else if (camOption == 4) camera->togglePower();
                        else std::cout << "Invalid option.\n";
                    }
                    else if (DoorLock* lock = dynamic_cast<DoorLock*>(d)) {
                        int lockOption;
                        std::cout << "\n1. Lock door\n2. Unlock door\n3. Register failed attempt\n4. Reset failed attempts\n5. Toggle power\nOption: ";
                        std::cin >> lockOption;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (lockOption == 1) lock->lockDoor();
                        else if (lockOption == 2) lock->unlockDoor();
                        else if (lockOption == 3) lock->registerFailedAttempt();
                        else if (lockOption == 4) lock->resetFailedAttempts();
                        else if (lockOption == 5) lock->togglePower();
                        else std::cout << "Invalid option.\n";
                    }
                }
                else if (controlOption != 0) {
                    std::cout << "Invalid option.\n";
                }

                std::cout << "Operation completed.\n";
            }
            else if (option == 9) {
                std::string roomName;
                std::cout << "Enter room name to remove: ";
                std::getline(std::cin, roomName);

                home.removeRoomByName(roomName);
                std::cout << "Room removed successfully.\n";
            }
            else if (option == 10) {
                std::string roomName;
                int index;

                std::cout << "Enter room name: ";
                std::getline(std::cin, roomName);

                Room* room = home.findRoomByName(roomName);
                if (room == nullptr) {
                    throw std::runtime_error("Room not found.");
                }

                room->displayDevices();

                std::cout << "\nChoose device index to remove: ";
                std::cin >> index;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Invalid device index.");
                }

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                room->removeDeviceByIndex(index - 1);
                std::cout << "Device removed successfully.\n";
            }
            else if (option == 11) {
                std::string fileName;

                std::cout << "Enter file name: ";
                std::getline(std::cin, fileName);

                home.loadFromFile(fileName);
                std::cout << "\nRoom loaded successfully.\n";
            }
            else if (option == 0) {
                std::cout << "Exiting...\n";
            }
            else {
                std::cout << "Invalid option.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }

    } while (option != 0);

    return 0;
}