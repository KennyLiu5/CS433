#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
ReadyQueue::ReadyQueue(){
    capacity = 500;//initialize the capacity to 500
    size1= 0;//initialize our size1 to 0 because we have 0 elements in our heap
    heap = new PCB*[capacity];//create a new PCB heap with the max capacity array
}
 ReadyQueue::ReadyQueue(const ReadyQueue& object){
    capacity = object.capacity;
    size1 = object.size1;

    heap = new PCB*[capacity];
    for(int i = 0; i < size1; i++){
        heap[i] = new PCB(*(object.heap[i]));
    }
 }

ReadyQueue& ReadyQueue::operator=(const ReadyQueue& object){
    if(this == &object){//checks if the PCB is the same as the other PCB REadyQueue object
        return *this;
    }
   /* for(int i =0; i < size1;i++){//this makes sure that we delete the heap contents/objects inside the elements
        delete heap[i];
    }*/
    delete[] heap;//this deletes the array heap/itself. Its an array of pointers to PCB objects

    capacity = object.capacity;//store the old capacity to the new capacity//
    size1 = object.size1;//store the old size1 to the new PCB
    heap = new PCB*[capacity];//create a new heap array with the new capacity

    for(int i = 0; i < size1; i++){
        heap[i] = new PCB(*(object.heap[i]));//store heap1 from object to the new PCB heap at index i.
    }
    return *this;
}
 void ReadyQueue::swap(PCB* &heap1, PCB* &heap2){
    PCB* temp = heap1;//store heap1 into a temp variable
    heap1 = heap2;//store heap2 into heap1
    heap2 = temp;//store temp or original heap1 into heap2.
}

/**
 *@brief Destructor
*/
ReadyQueue::~ReadyQueue() {
    delete[] heap;//delete the heap array
    size1 = 0;//reset the size1 to 0
    capacity = 100;//the capacity is reset back to 100
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    // When adding a PCB to the queue, you must change its state to READY.
    if(size1 >= capacity){//checks if our queue is full or not
        cout << "Reached maximum capacity\n";
        return; 
    }
        heap[size1] = pcbPtr;//store the new added pcbPTr to our heap pcb at position of size1
        heap[size1]->setState(ProcState::READY);//change the state by accessing the set state to ready
        percolateUp(size1);
        size1++;//update and increment by 1;
}
void ReadyQueue::percolateUp(int index){
    int fatherIndex = (index - 1) / 2;//to find father we subtract 1 and divide 2
    if(index <=0){//if our index is less than or equal to zero, then we know that it is an invalid or its the father.
        return;
    }
    if(heap[index]->getPriority() > heap[fatherIndex]->getPriority()){//if the heap index priority is greater than our fatherindex priority 
        swap(heap[index],heap[fatherIndex]);//swap the PCB heap pointers
        percolateUp(fatherIndex);//recursively call percolateUp
    }
}
/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    // When removing a PCB from the queue, you must change its state to RUNNING.
    PCB* retval;
    if(size1 > 0){//meaning if there are some pcb's in our queue
        heap[0]->setState(ProcState::RUNNING);//set the state to running

        retval = heap[0];//store the heap[0] to the retval to return in the main
        if(size1 == 1){//if we have only one PCB
            heap[0] = nullptr;//have that pcb at index 0 be null/empty
            size1 = 0;//our size then be 0 because there is no more pcb
            return retval;//then return that pcb.
        }else{
            heap[0] = heap[size1 - 1];//store the last pcb at the end of the index to the top or first position at heap[0]
            size1--;//decrement our size of array 
      
            percolateDown(0);//call the percolateDown to make sure our heap is structured correctly
            //where the top should be the highest priority
            return retval;//finally return that pcb.
        }
    }else{//we don't have any elements of pcb at all.
        cout << "No elements to be removed\n";
        return 0;
    }
}

void ReadyQueue::percolateDown(int index){
    int leftChild = 2 * index +1;//find the left child of the index
    int rightChild = 2 * index +2;//find the right child of the index
    int indexbigger = index; //set the indexbigger to the index/parent
    // See if the left child exists and has a higher priority
    if (leftChild < size1 && heap[leftChild]->getPriority() > heap[indexbigger]->getPriority()) {
        indexbigger = leftChild;
    }

    // See if the right child exists and has a higher priority
    if (rightChild < size1 && heap[rightChild]->getPriority() > heap[indexbigger]->getPriority()) {
        indexbigger = rightChild;
    }

    // If the current pcb priority is less than the maximum priority among children, swap and recursive call
    if (index != indexbigger) {
        swap(heap[index], heap[indexbigger]);
        percolateDown(indexbigger);
    }
}





/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return size1;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    
    if(size1 == 0){
        cout <<"Display Processes in ReadyQuue:\n";
    }else{
        cout <<"Display Processes in ReadyQueue: "<< endl;
        for(int i = 0;i < size1;i++){
            heap[i]->display();//use the pcb display function to display that heap at that i index
        }
        cout << endl;
    }
}
