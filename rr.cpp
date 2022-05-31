#include<bits/stdc++.h>

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

void updateQueue(int queue[], int n, int lastProccessIndex){
	int first_index;
	for(int i = 0; i < n; i++){
		if(queue[i] == 0){
			first_index = i;
			break;
		}
	}
	queue[first_index] = lastProccessIndex + 1;
}

void swapQueues(int queue[], int n){
	for (int i = 0; (i < n - 1) && (queue[i + 1] != 0) ; i++){
		swap(queue[i], queue[i + 1]);
	}
}

void newProcessArrived(int current_time, Process processes[], int n, int lastProccessIndex,int queue[]){
	if (current_time <= processes[n-1].arrival_time){
		bool newArrival = false;
		for(int j = (lastProccessIndex+1); j < n; j++){
				if(processes[j].arrival_time <= current_time){
				if(lastProccessIndex < j){
					lastProccessIndex = j;
					newArrival = true;
				}
			}
		}
		if(newArrival)
			updateQueue(queue, n, lastProccessIndex);
	}
}

int main(){
	int n, quantom;

	cin >> n >> quantom; 

	struct Process processes[n];

	int current_time = 0, maxProccessIndex = 0;

	int queue[n], temp_burst[n];

	for (int i = 0; i < n; i++) {
		processes[i].id = i + 1;
		cin >> processes[i].arrival_time >> processes[i].burst_time;
		
		processes[i].is_completed = false; 
		queue[i] = 0;

		temp_burst[i] = processes[i].burst_time;
	}

	while (current_time < processes[0].arrival_time)
		current_time++;
	
	queue[0] = 1;
	
	while (true){
		bool done = true;
		for (int i = 0; i < n; i++){
			if(temp_burst[i] != 0){
				done = false;
				break;
			}
		}
		if(done)
			break;

		for (int i = 0; (i < n) && (queue[i] != 0); i++){
			int remaining_time = 0;
			while((remaining_time < quantom) && (temp_burst[queue[0] - 1] > 0)){
				temp_burst[queue[0] - 1] -= 1;
				current_time += 1;
				remaining_time++;

				newProcessArrived(current_time, processes, n, maxProccessIndex, queue);
			}
			if((temp_burst[queue[0] - 1] == 0) && (!processes[queue[0]-1].is_completed)) {
				processes[queue[0] - 1].turnaround_time = current_time;		
				processes[queue[0]-1].is_completed = true;
			}
			
			bool flag = true;
			if(queue[n - 1] == 0){
				for(int i = 0; i < n && queue[i] != 0; i++){
					if(!processes[queue[i] - 1].is_completed){
						flag = false;
					}
				}
				if(flag) {
					current_time++;
					newProcessArrived(current_time, processes, n, maxProccessIndex, queue);
				}
			}
		
			swapQueues(queue, n);
		}
	}

	for (int i = 0; i < n; i++) {
		processes[i].turnaround_time -= processes[i].arrival_time;
		processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
	}

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
