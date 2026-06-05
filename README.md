# OS Lab

My Operating Systems lab work in C, C++, and Bash — programs, assignments, and practice code from my B.Tech CS coursework. I keep it here to stay organized and track progress as the semester goes. Mostly for my own reference, but feel free to look around.

Everything runs on Ubuntu Linux. Most files have comments explaining what the program does and the idea behind it.

## Structure

```text
OS_LAB/
│
├── CPU_Scheduling/        # FCFS, SJF, Priority, Round Robin
├── Synchronization/       # producer-consumer, readers-writers, semaphores
├── Deadlock/              # detection & avoidance (Banker's algorithm)
├── Memory_Management/     # allocation strategies, paging
├── Page_Replacement/      # FIFO, LRU, Optimal
├── Disk_Scheduling/       # FCFS, SCAN, C-SCAN, SSTF
│
├── Threads/               # multithreading with pthreads
├── IPC/                   # pipes, message passing
├── Shared_Memory/         # shared memory segments
├── Sockets/               # client-server, socket programming
│
├── System_Calls/          # Linux system calls
├── Shell_Scripts/         # bash scripting
└── README.md
```

## What's in here — a quick tour

**CPU scheduling.** The classic algorithms — FCFS, SJF, priority, and round robin — with the usual waiting-time and turnaround-time calculations.

**Synchronization.** Process synchronization problems like producer-consumer and readers-writers, solved using semaphores and mutexes.

**Deadlock.** Handling deadlocks through detection and avoidance, including the Banker's algorithm.

**Memory.** Memory management strategies and paging, plus the page replacement algorithms — FIFO, LRU, and Optimal.

**Disk scheduling.** Head-movement algorithms — FCFS, SSTF, SCAN, and C-SCAN.

**Concurrency & IPC** — the systems-programming side:
- Multithreading using pthreads
- Inter-process communication through pipes and message passing
- Shared memory between processes
- Socket programming for client-server communication, including connecting two systems over IP

**Linux programming.** Working with Linux system calls and shell scripting in Bash.

## Running the code

C and C++ programs:

```bash
gcc filename.c -o out          # add -lpthread for threaded programs
./out
```

Shell scripts:

```bash
bash script.sh
```

## Tech

C · C++ · Bash · Ubuntu Linux

## Links

- GitHub — [YASHAGARWAL07](https://github.com/YASHAGARWAL07)
- LinkedIn — [Yash Agarwal](https://www.linkedin.com/in/yash-agarwal0007/)
- LeetCode — [YASH_AGARWAL_07](https://leetcode.com/u/YASH_AGARWAL_07/)
- GeeksforGeeks — [yashagarwal07](https://www.geeksforgeeks.org/profile/yashagarwal07)
