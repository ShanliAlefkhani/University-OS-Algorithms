#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool is_completed;
};

void srt(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    while(completed != n) {
        int idx = -1;
        int mn = 10000000;
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && processes[i].is_completed == 0) {
                if(processes[i].remaining_burst_time < mn) {
                    mn = processes[i].remaining_burst_time;
                    idx = i;
                }
                if(processes[i].remaining_burst_time == mn) {
                    if(processes[i].arrival_time < processes[idx].arrival_time) {
                        mn = processes[i].remaining_burst_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            if(processes[idx].remaining_burst_time == processes[idx].burst_time) {
                processes[idx].start_time = current_time;
            }
            processes[idx].remaining_burst_time -= 1;
            current_time++;
            
            if(processes[idx].remaining_burst_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].response_time = processes[idx].start_time - processes[idx].arrival_time;
                processes[idx].is_completed = 1;
                completed++;
            }
        }
        else {
             current_time++;
        }  
    }

	cout << "Processes  Arrival Time  Burst Time  Waiting Time  Turn Around Time  Completion Time" << endl;
	int total_waiting_time = 0, total_turn_around_time = 0;
	for (int i = 0 ; i < n ; i++)
	{
		total_waiting_time = total_waiting_time + processes[i].waiting_time;
		total_turn_around_time = total_turn_around_time + processes[i].turnaround_time;
		int complete_time = processes[i].turnaround_time + processes[i].arrival_time;
		cout << " " << processes[i].id << "\t\t" 
			<< processes[i].arrival_time << "\t\t" 
			<< processes[i].burst_time << "\t\t" 
			<< processes[i].waiting_time << "\t\t "
			<< processes[i].turnaround_time << "\t\t "
			<< complete_time << endl;
	}

	cout << "Average waiting time = " << (float)total_waiting_time / (float)n << endl;
	cout << "Average turn around time = " << (float)total_turn_around_time / (float)n << endl;
}

int main() {
	int n;
	cin >> n;
	struct Process processes[n];

	for (int i = 0; i < n; i++) {
		processes[i].id = i + 1;
		cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_burst_time = processes[i].burst_time;
        processes[i].is_completed = 0;
	}

	srt(processes, n);

	return 0;
}
