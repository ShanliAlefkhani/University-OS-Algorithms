#include<bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void fifo(struct Process processes[], int n)
{
	int service_time[n];
	service_time[0] = processes[0].arrival_time;
	processes[0].waiting_time = 0;

	for (int i = 1; i < n ; i++)
	{
		service_time[i] = service_time[i-1] + processes[i-1].burst_time;
		processes[i].waiting_time = service_time[i] - processes[i].arrival_time;

		if (processes[i].waiting_time < 0)
			processes[i].waiting_time = 0;
	}

	for (int i = 0; i < n ; i++)
		processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;

	cout << "Processes  Arrival Time  Burst Time  Waiting Time  Turn Around Time  Completion Time" << endl;
	int total_waiting_time = 0, total_turnaround_time = 0;
	for (int i = 0 ; i < n ; i++)
	{
		total_waiting_time = total_waiting_time + processes[i].waiting_time;
		total_turnaround_time = total_turnaround_time + processes[i].turnaround_time;
		int complete_time = processes[i].turnaround_time + processes[i].arrival_time;
		cout << " " << processes[i].id << "\t\t" 
			<< processes[i].arrival_time << "\t\t" 
			<< processes[i].burst_time << "\t\t" 
			<< processes[i].waiting_time << "\t\t "
			<< processes[i].turnaround_time << "\t\t "
			<< complete_time << endl;
	}

	cout << "Average waiting time = " << (float)total_waiting_time / (float)n << endl;
	cout << "Average turn around time = " << (float)total_turnaround_time / (float)n << endl;
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

	fifo(processes, n);

	return 0;
}
