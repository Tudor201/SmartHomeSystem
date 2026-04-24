cmake_minimum_required(VERSION 3.20)
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

configure_file(${CMAKE_SOURCE_DIR}/defaults.txt ${CMAKE_BINARY_DIR}/defaults.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/save.txt ${CMAKE_BINARY_DIR}/save.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/tastatura.txt ${CMAKE_BINARY_DIR}/tastatura.txt COPYONLY)
