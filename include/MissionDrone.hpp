#pragma once
#include "Drone.hpp"
#include <tuple>
#include <vector>
using namespace std;

class MissionDrone : public Drone
{
    protected:
        string mission_name;
        vector<tuple<float,float,float>> waypoints;
        int current_waypoint_index;

    private:
        vector<pair<tuple<float,float,float>,string>> visited_waypoints;

    public:
        MissionDrone(const string& name,float max_altitude,float speed,const string& mission_name,const vector<tuple<float,float,float>>& waypoints);
        tuple<float,float,float> next_waypoint();
        void skip_waypoint(const string& reason);
        bool mission_complete() const;
        string mission_summary() const;
        string get_info() const override;
};