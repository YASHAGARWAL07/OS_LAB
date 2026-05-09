#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id, at, bt, ct, tat, wt;
};

struct Compare {
    bool operator()(Process a, Process b) {
        return a.bt > b.bt; // min heap based on BT
    }
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter AT and BT for P" << i+1 << ": ";
        cin >> p[i].at >> p[i].bt;
    }

    // Sort by arrival time
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[i].at > p[j].at) {
                swap(p[i], p[j]);
            }
        }
    }

    priority_queue<Process, vector<Process>, Compare> pq;

    int time = 0, i = 0;
    float totalWT = 0, totalTAT = 0;

    cout << "\nGantt Chart:\n";
    cout << "0 ";

    while(i < n || !pq.empty()) {

        while(i < n && p[i].at <= time) {
            pq.push(p[i]);
            i++;
        }

        if(pq.empty()) {
            time = p[i].at;
            continue;
        }

        Process curr = pq.top();
        pq.pop();

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
    i = 0;

    while(i < n || !pq.empty()) {

        while(i < n && p[i].at <= time) {
            pq.push(p[i]);
            i++;
        }

        if(pq.empty()) {
            time = p[i].at;
            continue;
        }

        Process curr = pq.top();
        pq.pop();

        time += curr.bt;

        curr.ct = time;
        curr.tat = curr.ct - curr.at;
        curr.wt = curr.tat - curr.bt;

        cout << "P" << curr.id << "\t"
             << curr.at << "\t"
             << curr.bt << "\t"
             << curr.ct << "\t"
             << curr.tat << "\t"
             << curr.wt << endl;
    }

    cout << "\nAverage WT = " << totalWT / n;
    cout << "\nAverage TAT = " << totalTAT / n;

    return 0;
}
