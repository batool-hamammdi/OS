#include<iostream>
#include <fstream> 

using namespace std;

const int PROC_MAX = 50;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
};

void FCFS(Process processes[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }
        currentTime += processes[i].burstTime;
        processes[i].finishTime = currentTime;
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
    
}}

void SRT(Process processes[], int n) {
    int currentTime = 0; 
    int completed = 0;   
    bool isCompleted[PROC_MAX] = { false };

    while (completed < n) {
        int i = -1;
        int minRemainingTime = 9999;
      
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !isCompleted[i] &&
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                i = i; 
            }
        }

       
        if (i != -1) {
            currentTime++;        
            processes[i].remainingTime--; 

            if (processes[i].remainingTime == 0) {
                completed++;
                isCompleted[i] = true; 
                processes[i].finishTime = currentTime;
                processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
                processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
            }
        }
        else {
            currentTime++; 
        }
    }

}

void RR(Process processes[], int n, int quantum) {
    int currentTime = 0; 
    bool isCompleted[PROC_MAX] = { false };
    int remainingProcesses = n; 

    while (remainingProcesses > 0) {
        bool processesDone = true; 

       
        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0) {
                processesDone = false; 
                if (processes[i].arrivalTime <= currentTime) {
                    if (processes[i].remainingTime > quantum) {
                        currentTime += quantum; 
                        processes[i].remainingTime -= quantum; 
                    } else {
                       
                        currentTime += processes[i].remainingTime;
                        processes[i].finishTime = currentTime;
                        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
                        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                        processes[i].remainingTime = 0; 
                        remainingProcesses--;
                    }
                }
            }
        }
       
        if (processesDone) break;
    }
}

void Result(Process processes[], int n) {
    cout << "Process ID | Arrival Time | Burst Time | Finish Time | Waiting Time | Turnaround Time"<<endl;
    cout << "------------|--------------|------------|-------------|--------------|----------------"<<endl;
    double avgWaitingTime = 0, avgTurnaroundTime = 0;

   
    for (int i = 0; i < n; i++) {
        cout << processes[i].id << "          | "
            << processes[i].arrivalTime << "            | "
            << processes[i].burstTime << "          | "
            << processes[i].finishTime << "          | "
            << processes[i].waitingTime << "          | "
            << processes[i].turnaroundTime <<endl;

        avgWaitingTime += processes[i].waitingTime; 
        avgTurnaroundTime += processes[i].turnaroundTime; 
    }

  
    cout << "Average Waiting Time: " << avgWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime / n << endl;
}

int main() {
    ifstream inputFile(" .txt"); 
    if (!inputFile) {
        cerr << "Error opening file."<<endl; 
        return 1;
    }

    Process processes[PROC_MAX];
    int n = 0; 
    int quantum; 

   
    while (inputFile >> processes[n].id >> processes[n].arrivalTime >> processes[n].burstTime) {
        processes[n].remainingTime = processes[n].burstTime; 
        n++;
    }
    inputFile >> quantum; 

    
    FCFS(processes, n);
    Result(processes, n);

   
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

  
    SRT(processes, n);
    Result(processes, n);

 
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }
    -- -
    RR(processes, n, quantum);
    Result(processes, n);

    return 0;
}