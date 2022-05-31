#include <bits/stdc++.h>

using namespace std;

struct Process {
	int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
	bool is_completed;
};


int main()
{
	int n;
	cin >> n;
	struct Process processes[n];

	int sum_of_burst_time = 0;

	for (int i = 0; i < n; i++) {
		processes[i].id = i + 1; 
		cin >> processes[i].arrival_time >> processes[i].burst_time;

		processes[i].is_completed = false;

		sum_of_burst_time += processes[i].burst_time; 
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (processes[i].arrival_time > processes[j].arrival_time) {
				swap(processes[i], processes[j]);
			}
		}
	}
	cout << "Processes  Arrival Time  Burst Time  Waiting Time  Turn Around Time  Completion Time" << endl;

	int total_waiting_time = 0;
	int total_turnaround_time = 0; 

	for (int current_time = processes[0].arrival_time; current_time < sum_of_burst_time;) {

		float hrr = -1000 * 1000 * 1000;

		float tmp;

		int loc;
		for (int i = 0; i < n; i++) {

			if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {

				tmp = (processes[i].burst_time + (current_time - processes[i].arrival_time)) / processes[i].burst_time;

				if (hrr < tmp) {

					hrr = tmp;

					loc = i;
				}
			}
		}

		current_time += processes[loc].burst_time;

		processes[loc].waiting_time = current_time - processes[loc].arrival_time - processes[loc].burst_time;

		processes[loc].turnaround_time = current_time - processes[loc].arrival_time;

		total_turnaround_time += processes[loc].turnaround_time;

		total_waiting_time += processes[loc].waiting_time;

		processes[loc].is_completed = true; 

		int complete_time = processes[loc].turnaround_time + processes[loc].arrival_time;


		cout << " " << processes[loc].id << "\t\t" 
			<< processes[loc].arrival_time << "\t\t" 
			<< processes[loc].burst_time << "\t\t" 
			<< processes[loc].waiting_time << "\t\t "
			<< processes[loc].turnaround_time << "\t\t "
			<< complete_time << endl;
	}
	cout << "Average waiting time = " << (float)total_waiting_time / (float)n << endl;
	cout << "Average turn around time = " << (float)total_turnaround_time / (float)n << endl;
}
