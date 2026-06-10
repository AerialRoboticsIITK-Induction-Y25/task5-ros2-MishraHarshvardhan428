#pragma once

#include <string>
#include <vector>

using namespace std;

class Vehicle
{
    protected:
        string name;

    private:
        float battery_level;
        string status;
        vector<string> flight_log;

    public:
        Vehicle(const string& name);
        virtual ~Vehicle() = default;
        virtual string get_info() const = 0;
        void drain_battery(float amount);
        void charge_battery(float amount, int duration_seconds);

        bool is_critical() const;
        string get_flight_log() const;
        void set_status(const string& new_status);

        string get_name() const;
        float get_battery_level() const;
        string get_status() const;
    };