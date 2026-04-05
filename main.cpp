#include <iostream>
#include <deque>
#include <iomanip>

using namespace std;

struct MedicalSystem {
    // Battery Stats (
    double Joules_Remaining = 2430.0;
    const double cost_per_beat = 0.000005;

    // Thermal Stats
    double current_temp_celsius = 37.0; // Baseline body temp
    const double thermal_limit = 42.0;   // Fever/Burn threshold

     double getBatteryYears(int bpm) const
    {
        double joules_per_year = (bpm * 60 * 24 * 365.25) * cost_per_beat;
        return Joules_Remaining / joules_per_year;
    }

    void processEnergy(int anomaly_count) {
        // Drain energy for every beat
        Joules_Remaining -= cost_per_beat;

        // If anomalies are high, the device might "work harder"
        // to send Bluetooth alerts, raising the temp slightly.
        if (anomaly_count > 4) {
            current_temp_celsius += 0.01;
        } else if (current_temp_celsius > 37.0) {
            current_temp_celsius -= 0.005; // Natural cooling
        }
    }
};

int main() {
    MedicalSystem bioSystem;
    int n;
    int anomaly = 0;
    const int limit = 10;
    deque<int> wind;

    cout << "--- BIOS-V1 SYSTEM ONLINE ---" << endl;
    cout << "Initial Lifespan: " << fixed << setprecision(2) << bioSystem.getBatteryYears(70) << " years." << endl;

    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        int heartbeats;
        cin >> heartbeats;

        // 1. this is draining
        bioSystem.processEnergy(anomaly);


        if (wind.size() == limit) {
            int leaving = wind.front();
            wind.pop_front();
            if (leaving < 600 || leaving > 1000) anomaly--;
        }

        wind.push_back(heartbeats);
        if (heartbeats < 600 || heartbeats > 1000) {
            anomaly++;
        }

        // 3. safety check
        if (bioSystem.current_temp_celsius >= bioSystem.thermal_limit) {
            cout << "CRITICAL ERROR: THERMAL SHUTDOWN TO PROTECT TISSUE!" << endl;
            break;
        }

        // 4. logging
        if (i % 5 == 0) {
            cout << "[Beat " << i + 1 << "] Anomalies: " << anomaly
                 << " | Temp: " << bioSystem.current_temp_celsius << "C"
                 << " | Life: " << bioSystem.getBatteryYears(80) << " yrs" << endl;
        }
    }

    return 0;
}