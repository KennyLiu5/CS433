/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author NAME
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

// global buffer object
Buffer buffer;

pthread_mutex_t mutex; //mutex lock
sem_t full; // count for semaphore
sem_t empty; // count for semaphore

// Producer thread function
void *producer(void *param) {
  // Each producer insert its own ID into the buffer
  // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
  buffer_item item = *((int *) param);//used that is passed from the fourth parameter of the pthread_create function

  while (true) {
    /* sleep for a random period of time */
    usleep(rand()%1000000);
    
    sem_wait(&empty); //acquire sempahore/wait till its not full
    pthread_mutex_lock(&mutex); //let mutex access critical section
    
    if (buffer.insert_item(item)) {
        cout << "Producer " << item << ": Inserted item " << item << endl;
        buffer.print_buffer();//get the function to print out the buffer
    } else {
        cout << "Producer error condition"  << endl;    // shouldn't come here
    }

    //end of critical section
    pthread_mutex_unlock(&mutex); // unlock the mutex
    sem_post(&full);  // release the semaphore, and increment full
  }
}

// Consumer thread function
void *consumer(void *param) {
    buffer_item item;

    while (true) {
      /* sleep for a random period of time */
      usleep(rand() % 1000000);
      
      sem_wait(&full); // acquire sempahore/wait till its not empty
      pthread_mutex_lock(&mutex); // let mutex access critical section
      
      if (buffer.remove_item(&item)) {
          cout << "Consumer " << item << ": Removed item " << item << endl;
          buffer.print_buffer();
      } else {
          cout << "Consumer error condition" << endl;    // shouldn't come here
      }

      //end of critical section
      pthread_mutex_unlock(&mutex); //unlock the mutex
      sem_post(&empty);  //release the semaphore, and decrement empty
    }
}

int main(int argc, char *argv[]) 
{ 
    int sleep_time = atoi(argv[1]); //sleep time
    int pthread = atoi(argv[2]); // number of producer threads
    int cthread = atoi(argv[3]); // number consumer threads
    

    sem_init(&empty, 0, 5/*BUFFER_SIZE*/); // initialize sempahore to BUFFER_SIZE
    sem_init(&full, 0, 0); // initialize sempahore to 0
    pthread_mutex_init(&mutex, NULL);// initialize mutex to NULL
    pthread_t tid1; // producer thread id
    pthread_t tid2; // consumer thread id
  
    /*You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
    int i;
    for(i = 0; i < pthread; i++)
      {
        int* arg = new int;
        if(arg == NULL)
        {
          cout << "CANNOT ALLOCATE MEMORY" << endl;
          exit(0);
        } 
        *arg = i+1; // value will be passed onto *producer 
        
      pthread_attr_t attr;
      pthread_attr_init(&attr);
      pthread_create(&tid1, &attr, producer, (void*) arg); // calling producer thread
      }
  
    int j;
    for(j = 0; j < cthread; j++)
      {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid2, &attr, consumer, NULL); // calling consumer thread
      }

    sleep(sleep_time);
    cout << "\nTimes up!! Main thread will enter sleep\n";
  
    
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
  
    exit(0);

  return 0;
}
