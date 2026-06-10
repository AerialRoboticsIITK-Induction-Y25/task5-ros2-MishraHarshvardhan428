#include "MissionDrone.hpp"
#include "DroneExceptions.hpp"
#include <sstream>
#include <chrono>
#include <ctime>
using namespace std;

MissionDrone::MissionDrone(const string& name,float max_altitude,float speed,const string& mission_name,const vector<tuple<float,float,float>>& waypoints)
    : Drone(name,max_altitude,speed),mission_name(mission_name),waypoints(waypoints),current_waypoint_index(0){}

tuple<float,float,float> MissionDrone::next_waypoint()
{
    if(mission_complete())
    {
        throw DroneException();
    }

    auto waypoint = waypoints[current_waypoint_index];

    drain_battery(1.5f);

    auto now = chrono::system_clock::to_time_t(
        chrono::system_clock::now()
    );

    visited_waypoints.push_back(
        {
            waypoint,
            ctime(&now)
        }
    );
    current_waypoint_index++;
    return waypoint;
}

void MissionDrone::skip_waypoint(const string& reason)
{
    if(mission_complete())
    {
        return;
    }
    current_waypoint_index++;
}

bool MissionDrone::mission_complete() const
{
    return current_waypoint_index >= static_cast<int>(waypoints.size());
}

string MissionDrone::mission_summary() const
{
    stringstream ss;
    ss << "Mission: " << mission_name << "\n";
    ss << "Visited Waypoints: "
       << visited_waypoints.size()
       << "/"
       << waypoints.size()
       << "\n";

    return ss.str();
}

string MissionDrone::get_info() const
{
    stringstream ss;
    ss << "Mission Drone: "
       << name
       << " | Mission: "
       << mission_name
       << " | Waypoint: "
       << current_waypoint_index
       << "/"
       << waypoints.size();

    return ss.str();
}