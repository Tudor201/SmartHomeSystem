cmake_minimum_required(VERSION 4.1)
project(SmartHomeSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmartHomeSystem main.cpp
        Device.cpp
        Device.h
        ElectricalDevice.cpp
        ElectricalDevice.h
        Light.cpp
        Light.h
        Thermostat.cpp
        Thermostat.h
        SecurityCamera.cpp
        SecurityCamera.h
        DoorLock.cpp
        DoorLock.h
        Room.cpp
        Room.h
        SmartHomeSystem.cpp
        SmartHomeSystem.h)
