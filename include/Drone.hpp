#pragma once
#include "Vehicle.hpp"
using namespace std;

class Drone : public Vehicle
{
    protected:
        float altitude;
        float max_altitude;

    private:
        float speed;

    public:
        Drone(const string& name,float max_altitude,float speed);
        void take_off(float target_altitude);
        void land();
        void emergency_stop();
        string get_info() const override;
        float get_altitude() const;
        float get_speed() const;
};