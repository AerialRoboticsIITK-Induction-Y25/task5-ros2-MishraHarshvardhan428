#pragma once
#include "MissionDrone.hpp"
#include <tuple>
#include <vector>
#include <string>
using namespace std;

class AutonomousDrone : public MissionDrone
{
    private:
        string ai_mode;
        tuple<float,float,float> home_position;
        vector<string> obstacle_log;

    public:
        AutonomousDrone(
            const string& name,
            float max_altitude,
            float speed,
            const string& mission_name,
            const vector<tuple<float,float,float>>& waypoints,
            const tuple<float,float,float>& home_position
        );

        void set_ai_mode(const string& mode);

        void detect_obstacle(
            tuple<float,float,float> position,
            const string& severity
        );

        vector<tuple<float,float,float>> auto_replan(
            const vector<tuple<float,float,float>>& obstacles
        );

        string get_info() const override;
};