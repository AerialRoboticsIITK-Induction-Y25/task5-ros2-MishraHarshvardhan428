#include "AutonomousDrone.hpp"
#include "DroneExceptions.hpp"

#include <sstream>
#include <chrono>
#include <ctime>
#include <cmath>

using namespace std;

AutonomousDrone::AutonomousDrone(
    const string& name,
    float max_altitude,
    float speed,
    const string& mission_name,
    const vector<tuple<float,float,float>>& waypoints,
    const tuple<float,float,float>& home_position
)
    : MissionDrone(
        name,
        max_altitude,
        speed,
        mission_name,
        waypoints
    ),
      ai_mode("manual"),
      home_position(home_position)
{
}

void AutonomousDrone::set_ai_mode(const string& mode)
{
    if(mode != "manual" &&
       mode != "auto" &&
       mode != "return_home")
    {
        throw InvalidStateError();
    }

    ai_mode = mode;

    if(mode == "return_home")
    {
        waypoints.insert(
            waypoints.begin() + current_waypoint_index,
            home_position
        );
    }
}

void AutonomousDrone::detect_obstacle(
    tuple<float,float,float> position,
    const string& severity
)
{
    auto now =
        chrono::system_clock::to_time_t(
            chrono::system_clock::now()
        );

    stringstream ss;

    ss << "Obstacle at ("
       << get<0>(position) << ", "
       << get<1>(position) << ", "
       << get<2>(position) << ") "
       << "Severity: "
       << severity
       << " Time: "
       << ctime(&now);

    obstacle_log.push_back(
        ss.str()
    );

    if(severity == "high")
    {
        emergency_stop();
    }
}

vector<tuple<float,float,float>>
AutonomousDrone::auto_replan(
    const vector<tuple<float,float,float>>& obstacles
)
{
    vector<tuple<float,float,float>> new_waypoints =
        waypoints;

    for(auto& wp : new_waypoints)
    {
        for(const auto& obs : obstacles)
        {
            float dx =
                get<0>(wp) - get<0>(obs);

            float dy =
                get<1>(wp) - get<1>(obs);

            float dz =
                get<2>(wp) - get<2>(obs);

            float distance =
                sqrt(
                    dx*dx +
                    dy*dy +
                    dz*dz
                );

            if(distance < 5.0f)
            {
                get<0>(wp) += 10;
                get<1>(wp) += 10;
            }
        }
    }

    return new_waypoints;
}

string AutonomousDrone::get_info() const
{
    stringstream ss;

    ss << "Autonomous Drone: "
       << name
       << " | Battery: "
       << get_battery_level()
       << " | Mission: "
       << mission_name
       << " | AI Mode: "
       << ai_mode
       << " | Waypoint: "
       << current_waypoint_index
       << "/"
       << waypoints.size();

    return ss.str();
}