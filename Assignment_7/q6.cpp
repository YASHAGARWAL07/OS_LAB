#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int id, at, bt, rt, wt;
};

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];
    int type[n]; // 0 = foreground, 1 = background

    for(int i = 0; i < n; i++) {
        p[i].id = i+1;
        cout << "Enter AT, BT and Type (0=FG,1=BG) for P" << i+1 << ": ";
        cin >> p[i].at >> p[i].bt >> type[i];
        p[i].rt = p[i].bt;
        p[i].wt = 0;
    }

    cout << "Enter Time Quantum (for RR): ";
    cin >> tq;

    queue<int> fg, bg;

    // Assign processes to queues
    for(int i = 0; i < n; i++) {
        if(type[i] == 0)
            fg.push(i);
        else
            bg.push(i);
    }

    int time = 0;

    cout << "\nGantt Chart:\n";
    cout << "0 ";

    // Foreground Queue → Round Robin
    while(!fg.empty()) {
        int i = fg.front();
        fg.pop();

        if(p[i].rt > tq) {
            time += tq;
            p[i].rt -= tq;
            cout << "| P" << p[i].id << " " << time << " ";
            fg.push(i);
        } else {
            time += p[i].rt;
            cout << "| P" << p[i].id << " " << time << " ";
            p[i].rt = 0;
            p[i].wt = time - p[i].at - p[i].bt;
        }
    }

    // Background Queue → FCFS
    while(!bg.empty()) {
        int i = bg.front();
        bg.pop();

        if(time < p[i].at)
            time = p[i].at;

        time += p[i].bt;

        cout << "| P" << p[i].id << " " << time << " ";

        p[i].wt = time - p[i].at - p[i].bt;
    }

    cout << "|\n";

    cout << "\nProcess\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].wt << endl;
    }

    return 0;
}
