#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter AT and BT for P" << i+1 << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    bool inQueue[n] = {false};

    int time = 0, complete = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\nGantt Chart:\n";
    cout << "0 ";

    // Push first process
    q.push(0);
    inQueue[0] = true;

    while(!q.empty()) {
        int i = q.front();
        q.pop();

        if(rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
            cout << "| P" << i+1 << " " << time << " ";
        } else {
            time += rt[i];
            cout << "| P" << i+1 << " " << time << " ";

            ct[i] = time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];

            totalWT += wt[i];
            totalTAT += tat[i];

            rt[i] = 0;
            complete++;
        }

        // Add new processes to queue
        for(int j = 0; j < n; j++) {
            if(at[j] <= time && !inQueue[j] && rt[j] > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // Re-add current process if not finished
        if(rt[i] > 0)
            q.push(i);
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
