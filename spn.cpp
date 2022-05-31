#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void spn(struct Process processes[], int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (processes[j].arrival_time > processes[j+1].arrival_time) {
				swap(processes[j], processes[j+1]);
			}
		}
	}
	
	int service_time[n];
	service_time[0] = processes[0].arrival_time;
	processes[0].waiting_time = 0;
	processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
	processes[0].turnaround_time = processes[0].burst_time + processes[0].waiting_time;

	int val = 0;
	for (int i = 1; i < n; i++) {
		int temp = processes[i - 1].completion_time;
		int low = processes[i].burst_time;
		for (int j = i; j < n; j++) {
			if (temp >= processes[j].arrival_time && low >= processes[j].burst_time) {
				low = processes[j].burst_time;
				val = j;
			}
		}
		processes[val].completion_time = temp + processes[val].burst_time;
		processes[val].turnaround_time = processes[val].completion_time - processes[val].arrival_time;
		processes[val].waiting_time = processes[val].turnaround_time - processes[val].burst_time;
		swap(processes[val], processes[i]);
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

int main()
{
	int n;
	cin >> n;
	struct Process processes[n];

	for (int i = 0; i < n; i++) {
		processes[i].id = i + 1;
		cin >> processes[i].arrival_time >> processes[i].burst_time;
	}

	spn(processes, n);

	return 0;
}
