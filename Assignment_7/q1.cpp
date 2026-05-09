#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    // Input
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter AT and BT for P" << i+1 << ": ";
        cin >> p[i].at >> p[i].bt;
    }

    // Sort by Arrival Time
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[i].at > p[j].at) {
                swap(p[i], p[j]);
            }
        }
    }

    queue<Process> q;

    // Insert into queue
    for(int i = 0; i < n; i++) {
        q.push(p[i]);
    }

    int time = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\nGantt Chart:\n";
    cout << "0 ";

    while(!q.empty()) {
        Process curr = q.front();
        q.pop();

        if(time < curr.at)
            time = curr.at;

        time += curr.bt;

        curr.ct = time;
        curr.tat = curr.ct - curr.at;
        curr.wt = curr.tat - curr.bt;

        cout << "| P" << curr.id << " " << time << " ";

        totalWT += curr.wt;
        totalTAT += curr.tat;
    }

    cout << "|\n";

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";

    time = 0;
    for(int i = 0; i < n; i++) {
        if(time < p[i].at)
            time = p[i].at;

        time += p[i].bt;

        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << endl;
    }

    cout << "\nAverage WT = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n;

    return 0;
}
