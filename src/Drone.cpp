#include "Drone.hpp"
#include "DroneExceptions.hpp"

#include <sstream>

using namespace std;

Drone::Drone(const string& name,float max_altitude,float speed)
    : Vehicle(name),altitude(0.0f),max_altitude(max_altitude),speed(speed){}

void Drone::take_off(float target_altitude)
{
    if(target_altitude > max_altitude)
    {
        throw AltitudeError();
    }

    altitude = target_altitude;
    set_status("flying");
}

void Drone::land()
{
    altitude = 0;

    set_status("idle");
}

void Drone::emergency_stop()
{
    altitude = 0;
    drain_battery(30);
    set_status("idle");
}

string Drone::get_info() const
{
    stringstream ss;

    ss << "Drone: " << name
       << " | Battery: " << get_battery_level()
       << " | Altitude: " << altitude
       << " | Status: " << get_status();

    return ss.str();
}

float Drone::get_altitude() const
{
    return altitude;
}

float Drone::get_speed() const
{
    return speed;
}
