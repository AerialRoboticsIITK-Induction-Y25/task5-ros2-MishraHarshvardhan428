#pragma once
#include <stdexcept>
using namespace std;

class DroneException : public exception
{
    public:
        const char* what() const noexcept override
        {
            return "DroneException occurred";
        }
};

class BatteryDepletedError : public DroneException
{
    public:
        const char* what() const noexcept override
        {
            return "Battery depleted. Please recharge the drone.";
        }
};

class InvalidStateError : public DroneException
{
    public:
        const char* what() const noexcept override
        {
            return "Invalid state transition attempted.";
        }
};

class AltitudeError : public DroneException
{
    public:
        const char* what() const noexcept override
        {
            return "Altitude out of bounds. Please check the drone's altitude settings.";
        }
};