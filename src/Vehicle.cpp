#include "Vehicle.hpp"
#include "DroneExceptions.hpp"

#include <sstream>
using namespace std;

Vehicle::Vehicle(const string& name)
    : name(name),battery_level(100.0f), status("idle"){}

void Vehicle::drain_battery(float amount)
{
    if (battery_level <= 0)
        throw BatteryDepletedError();
 
    battery_level -= amount;
    if (battery_level < 0)
        battery_level = 0;

}

void Vehicle::charge_battery(float amount,int duration_seconds)
{
    if (status != "charging")
        throw InvalidStateError();

    battery_level += amount;

    if (battery_level > 100)
        battery_level = 100;
}
bool Vehicle::is_critical() const
{
    return battery_level < 20.0f;
}

string Vehicle::get_flight_log() const
{
    string result;

    for(const auto& entry : flight_log)
    {
        result += entry + "\n";
    }

    return result;
}

void Vehicle::set_status(const string& new_status)
{
    if(new_status != "idle" && new_status != "flying" && new_status != "charging")
        throw InvalidStateError();
    status = new_status;
}

string Vehicle::get_name() const
{
    return name;
}

float Vehicle::get_battery_level() const
{
    return battery_level;
}
string Vehicle::get_status() const
{
    return status;
}