/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Katie Trinh and Cherishma Jalaparti
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

  /**
  * @brief Construct a new SchedulerSJF object
  */
  SchedulerSJF::SchedulerSJF()
  {
    count = 0;
    total_turnaround = 0.0;
    total_wait = 0.0;
  }

  /**
   * @brief Destroy the SchedulerSJF object
   */
  SchedulerSJF::~SchedulerSJF() 
  {
    while(!Q.empty()) // pops everything in queue until empty
      {
        Q.pop();
      }
    Q = {}; // to ensure Q will be empty
  }


  /**
   * @brief This function is called once before the simulation starts.
   *        It is used to initialize the scheduler.
   * @param process_list The list of processes in the simulation.
   */
  void SchedulerSJF::init(std::vector<PCB>& process_list)
  {
    sort(process_list.begin(), process_list.end(), [](const PCB& lhs, const PCB& rhs) {
    return lhs.burst_time < rhs.burst_time;
     });
    int v_size = process_list.size();
    int index = 0; // to track which index we are in the vector
    while(index != v_size) // runs until index reaches end of the process_list vector
      {
        Q.push(process_list[index]); // PCB in vector gets pushed into queue
        count++;
        index++;
    }
  }


  /**
   * @brief This function is called once after the simulation ends.
   *        It is used to print out the results of the simulation.
   */
  void SchedulerSJF::print_results()
  {
    sort(done.begin(), done.end(), [](const PCB& lhs, const PCB& rhs) {
    return lhs.id < rhs.id;
     }); // sorts by process T1, T2, etc
    int done_size = done.size();
    for(int i=0; i<done_size; i++)
     {
        cout << done[i].name << " turn-around time = " << done[i].turnaround;
        cout << ", waiting time = " << done[i].wait << endl;
     }
    cout << "Average turn-around time = " <<  total_turnaround/count;
    cout << ", Average waiting time = " << total_wait/count << endl;
  }


  /**
   * @brief This function simulates the scheduling of processes in the ready queue.
   *        It stops when all processes are finished.
   */
  void SchedulerSJF::simulate()
  {
    unsigned int curr_turnaround = 0; // will start at 0
    while(!Q.empty()) // run until queue is empty
    {
      unsigned int curr_burst; // tracks current burst
      unsigned int curr_wait; // tracks current waiting time
  
      curr_burst = Q.front().burst_time; // contains burst time of PCB in front of queue
      curr_turnaround += curr_burst; // calculates turnaround
      curr_wait = curr_turnaround - curr_burst; // calculates wait
  
      // running sum that adds up all the process turnaround/wait
      total_turnaround += curr_turnaround;
      total_wait += curr_wait;

      // saving turnaround and waiting times into PCB
      Q.front().turnaround = curr_turnaround;
      Q.front().wait = curr_wait;

      // putting PCB into done vector
      done.push_back(Q.front());
  
      // display "Running Process [name] for x time units"
      cout << "Running Process " << Q.front().name << " for "  << curr_burst << " time units" << endl;
      
      Q.pop(); // remove PCB in front
    }
  }
