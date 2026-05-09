#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int id, bt, rt, wt, ct;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i+1;
        cout << "Enter BT for P" << i+1 << ": ";
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].wt = 0;
    }

    int tq1, tq2;
    cout << "Enter Time Quantum for Q1: ";
    cin >> tq1;
    cout << "Enter Time Quantum for Q2: ";
    cin >> tq2;

    queue<int> q1, q2, q3;

    for(int i = 0; i < n; i++)
        q1.push(i);

    int time = 0;
    float totalWT = 0;

    cout << "\nGantt Chart:\n";
    cout << "0 ";

    // Q1 → RR small quantum
    while(!q1.empty()) {
        int i = q1.front();
        q1.pop();

        if(p[i].rt > tq1) {
            time += tq1;
            p[i].rt -= tq1;
            cout << "| P" << p[i].id << " " << time << " ";
            q2.push(i); // downshift
        } else {
            time += p[i].rt;
            cout << "| P" << p[i].id << " " << time << " ";
            p[i].rt = 0;
            p[i].ct = time;
        }
    }

    // Q2 → RR large quantum
    while(!q2.empty()) {
        int i = q2.front();
        q2.pop();

        if(p[i].rt > tq2) {
            time += tq2;
            p[i].rt -= tq2;
            cout << "| P" << p[i].id << " " << time << " ";
            q3.push(i); // downshift
        } else {
            time += p[i].rt;
            cout << "| P" << p[i].id << " " << time << " ";
            p[i].rt = 0;
            p[i].ct = time;
        }
    }

    // Q3 → FCFS
    while(!q3.empty()) {
        int i = q3.front();
        q3.pop();

        time += p[i].rt;
        cout << "| P" << p[i].id << " " << time << " ";

        p[i].ct = time;
        p[i].rt = 0;
    }

    cout << "|\n";

    // Calculate WT
    for(int i = 0; i < n; i++) {
        p[i].wt = p[i].ct - p[i].bt;
        totalWT += p[i].wt;
    }

    cout << "\nProcess\tBT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].bt << "\t"
             << p[i].wt << endl;
    }

    cout << "\nAverage WT = " << totalWT / n;

    return 0;
}
