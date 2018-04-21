#include<bits/stdc++.h>
using namespace std;

 int dony[20];
 int top = 0;
void findavgTime(int [], int, int [], int);

struct Process
{
    int pid;  // Process ID
    int at;   // Arrival time
    int bt;   // CPU Burst time required
    int priority; // Priority of this process
};
 
// Function to sort the Process acc. to priority
bool comparison(Process a, Process b)
{
    return !(a.priority > b.priority);
}

void priorityScheduling(Process proc[], int n)
{
	
	int temp = 0;
	for(int i = 0 ; i < n; i++)
	{
		temp = temp + proc[i].bt;
		
	}
	//cout<<"\n MAXTIME: "<<temp<<endl;
	
	// Sort processes by priority8
    sort(proc, proc + n, comparison);
	
	
	//needed for level 2
	// process id's
    int processes[20];
 
    // Burst time of all processes
    int burst_time[20];
	
	//level 1
	//  main Logic to communicate between the levels

	int i,j=0,f=0,newi=0;
	int time = 0;
	bool flag2 = true;
	bool flag1 = true;
	
	while(flag1)
	{	
		for(i = 0; i < n; ++i)
		{
			
			if(time >= proc[i].at and proc[i].pid != -1)
			{
				
				if(proc[i].bt != 0)
					{
					
					
					if(flag2)
					{
						j = i;
						flag2 = false;
					}
					
					proc[i].bt = proc[i].bt -1;
					
					if(proc[i].bt == 0)
					{
						dony[top] = proc[i].pid;
						top++;
						
					}
					
					if(i != j )
					{
						if(proc[j].bt != 0)
						{
					
						processes[newi] = proc[j].pid;
						burst_time[newi] = proc[j].bt;
						proc[j].pid = -1;
						newi++;
						j = i;
						}
						else
						{
						flag2 = true;
						}
					
					}
				
				
					i = -1;				
					time++;
				}	
			}
			
		}
		if(time >= temp)
			{
				flag1 = false;
			}
		time++;
		
	}
	
	cout<<"\nProcesses those are completed in level 1:"<<endl;
		
	for(int i=0;i<top-1;i++)
	{
		cout<<"  "<<dony[i]<<"  --> ";
		
	}cout<<dony[top-1]<<endl;
    //level 2 calling

    cout<<"\n-------------------------Level 2-------------------------";
    cout<<"\n                 Round Robin Scheduling    \n"<<endl;
    // Time quantum
    int quantum = 2;
    findavgTime(processes, newi, burst_time, quantum);
}



//      level 2 
// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n,
             int bt[], int wt[], int quantum)
{
    // Make a copy of burst times bt[] to store remaining
    // burst times.
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];
 
    int t = 0; // Current time
 
    // Keep traversing processes in round robin manner
    // until all of them are not done.
    while (1)
    {
        bool done = true;
 
        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            // If burst time of a process is greater than 0
            // then only need to process further
            if (rem_bt[i] > 0)
            {
                done = false; // There is a pending process
 
                if (rem_bt[i] > quantum)
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t += quantum;
 
                    // Decrease the burst_time of current process
                    // by quantum
                    rem_bt[i] -= quantum;
                }
 
                // If burst time is smaller than or equal to
                // quantum. Last cycle for this process
                else
                {
                    // Increase the value of t i.e. shows
                    // how much time a process has been processed
                    t = t + rem_bt[i];
 
                    // Waiting time is current time minus time
                    // used by this process
                    wt[i] = t - bt[i];
 
                    // As the process gets fully executed
                    // make its remaining burst time = 0
                    rem_bt[i] = 0;
                }
            }
        }
 
        // If all processes are done
        if (done == true)
          break;
    }
}
 
// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n,
                        int bt[], int wt[], int tat[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}
 
// Function to calculate average time
void findavgTime(int processes[], int n, int bt[],
                                     int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
 
    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt, quantum);
 
    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);
 
    // Display processes along with all details
    cout << "Processes "<< " Burst time "
         << " Waiting time " << " Turn around time\n";
 
    // Calculate total waiting time and total turn
    // around time
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << processes[i] << "\t\t" << bt[i] <<"\t "
             << wt[i] <<"\t\t " << tat[i] <<endl;
    }
 
    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}




// Driver code
int main()
{
    Process proc[] = {{1, 4, 12, 4}, {2, 6, 5, 0}, {3, 5, 8, 1},
                      {4, 0, 6, 7}, {5, 1, 5, 2}, {6, 2, 8, 6}};
                      
    int n = sizeof proc / sizeof proc[0];

	cout<<"\n------------------*** Process Table ***------------------"<<endl;
	// Display process table
    cout << "ProcessID "<< " Arrival time "
         << " Burst time " << " Priority\n";
	for(int i = 0;i < n; i++)
	{
		cout << " " << proc[i].pid << "\t\t" << proc[i].at <<"\t "
             << proc[i].bt <<"\t\t " << proc[i].priority <<endl;
	}

    cout<<"\n-------------------------Level 1-------------------------"<<endl;
    cout<<"               Fixed pre-emptive scheduling"<<endl;
    priorityScheduling(proc, n);
    return 0;
} 
