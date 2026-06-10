#include <iostream>
#include <vector>
#include <tuple>

#include "Drone.hpp"
#include "MissionDrone.hpp"
#include "AutonomousDrone.hpp"
#include "DroneExceptions.hpp"

using namespace std;

int main()
{
    vector<tuple<float,float,float>> waypoints =
    {
        {10,20,30},
        {20,30,40},
        {30,40,50}
    };

    try
    {
        Drone alpha(
            "Alpha",
            100.0f,
            10.0f
        );

        MissionDrone beta(
            "Beta",
            120.0f,
            12.0f,
            "Survey Mission",
            waypoints
        );

        AutonomousDrone gamma(
            "Gamma",
            150.0f,
            15.0f,
            "Inspection Mission",
            waypoints,
            {0,0,0}
        );

        vector<Vehicle*> fleet =
        {
            &alpha,
            &beta,
            &gamma
        };

        cout << "=== POLYMORPHISM TEST ===\n";

        for(auto vehicle : fleet)
        {
            cout << vehicle->get_info() << endl;
        }

        cout << "\n=== DRONE OPERATIONS ===\n";

        alpha.drain_battery(20);

        cout << alpha.get_info() << endl;

        alpha.take_off(50);

        cout << alpha.get_info() << endl;

        alpha.land();

        cout << alpha.get_info() << endl;

        cout << "\n=== AUTONOMOUS DRONE TEST ===\n";

        gamma.take_off(60);

        gamma.detect_obstacle(
            {25,25,25},
            "high"
        );

        cout << gamma.get_info() << endl;

        cout << "\n=== MISSION EXECUTION ===\n";

        gamma.take_off(40);

        while(!gamma.mission_complete())
        {
            auto waypoint =
                gamma.next_waypoint();

            cout << "Visited waypoint: ("
                 << get<0>(waypoint) << ", "
                 << get<1>(waypoint) << ", "
                 << get<2>(waypoint) << ")\n";
        }

        cout << "\n=== MISSION SUMMARY ===\n";

        cout << gamma.mission_summary()
             << endl;

        // Uncommenting this should fail because
        // battery_level is private:
        //
        // alpha.battery_level = 50;

    }
    catch(const BatteryDepletedError& e)
    {
        cout << "Battery Error: "
             << e.what()
             << endl;
    }
    catch(const InvalidStateError& e)
    {
        cout << "State Error: "
             << e.what()
             << endl;
    }
    catch(const AltitudeError& e)
    {
        cout << "Altitude Error: "
             << e.what()
             << endl;
    }
    catch(const DroneException& e)
    {
        cout << "Drone Error: "
             << e.what()
             << endl;
    }
    catch(const exception& e)
    {
        cout << "Standard Exception: "
             << e.what()
             << endl;
    }

    return 0;
}   