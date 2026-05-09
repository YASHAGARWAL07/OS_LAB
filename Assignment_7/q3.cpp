#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter AT and BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i]; // remaining time
    }

    int complete = 0, time = 0, minm = 1e9;
    int shortest = 0;
    bool found = false;

    float totalWT = 0, totalTAT = 0;

    cout << "\nGantt Chart:\n";

    while(complete != n) {

        minm = 1e9;
        found = false;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && rt[i] < minm) {
                minm = rt[i];
                shortest = i;
                found = true;
            }
        }

        if(!found) {
            time++;
            continue;
        }

        cout << "| P" << shortest+1 << " ";

        rt[shortest]--;

        if(rt[shortest] == 0) {
            complete++;
            int finish_time = time + 1;

            ct[shortest] = finish_time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            totalWT += wt[shortest];
            totalTAT += tat[shortest];
        }

        time++;
    }

    cout << "|\n";

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    cout << "\nAverage WT = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n;

    return 0;
}
