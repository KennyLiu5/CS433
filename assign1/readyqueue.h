/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author NAME
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once

#include "pcb.h"

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class ReadyQueue {
private:

    // choose a data structure for the ReadyQueue. No STL class is allowed.
    PCB** heap;// array of pcb in the binary heap 
    /*Note: the compiler says that I need to do PCB** and not PCB* alone and it works.*/
    int capacity; //maximum capacity of the priority queue
    int size1;//current size of the element in the the queue
    //PCB** is a pointer that points to another pointer. And this one point to the beginning of the array.
    //was getting error code in readyqueue.cpp in line 17 stating that i need **.


//cout <<here
public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();

    ReadyQueue(const ReadyQueue& object);//copy constructor
    ReadyQueue& operator =(const ReadyQueue& object);//copy constructor but be able to use = operator
    void swap(PCB* &heap1, PCB* &heap2);//swap the two PCB heap units and swap them
    /**
     * @brief Destructor
     */
    ~ReadyQueue();

	// You may add additional member functions, but don't change the definitions of the following four member functions.

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    void percolateUp(int index);//used to help sort our heap making high values priority go to the top
    void percolateDown(int index);//used to help sort our heap making low values priority go to the bottom
    
    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

};
