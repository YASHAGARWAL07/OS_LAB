#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], pr[n], ct[n], tat[n], wt[n];
    bool done[n] = {false};

    for(int i = 0; i < n; i++) {
        cout << "Enter AT, BT and Priority for P" << i+1 << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
    }

    int complete = 0, time = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\nGantt Chart:\n";
    cout << "0 ";

    while(complete < n) {
        int idx = -1;
        int highest = 1e9;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && !done[i] && pr[i] < highest) {
                highest = pr[i];
                idx = i;
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        time += bt[idx];

        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        cout << "| P" << idx+1 << " " << time << " ";

        totalWT += wt[idx];
        totalTAT += tat[idx];

        done[idx] = true;
        complete++;
    }

    cout << "|\n";

    cout << "\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    cout << "\nAverage WT = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n;

    return 0;
}
