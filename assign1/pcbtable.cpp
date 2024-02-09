/**
 * Assignment 1: priority queue of processes
 * @file pcbtable.h
 * @author Katie Trinh, Cherishma Jalaparti
 * @brief This is the implementation file for the PCBTable class.
 * //You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
 * // Remember to add sufficient comments to your code
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
    //create a new pctable array till the size.
    for(int i = 0; i < size; i++){
        pcb.push_back(nullptr);//create a new vector array at pcb with nullptr by
        // using push_back built in function when dealing with vectors
        //And do it till the size was given.
    }
}
/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {

   // Delete all the PCBs in the table
   //for(element_type element_name : sequence) is for me to understand this type of for loop
    for(PCB* pcb_pointer : pcb){//check each pcb vector if there is an object.
        if(pcb_pointer != nullptr){//if our pcb is not nullptr or points to an existing PCB object
            //then we delete that pcb to release that vector memory. 
            delete pcb_pointer;
        }
    }
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {

    if(idx < pcb.size()){//we check if the idx is valid or within bound of our pcb
        return pcb[idx];//if so, we can return the pcb at that specific index
    }
    //else then the index is ivalid and we return null.
    return NULL;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {

    // Want to make sure that if we reached the end of our index, we resize by increasing it by 1 our new array/vector
    if(idx >= this->pcb.size()){//check if idx is greater than size of our vector pcb to
        //increase the size by 1 and have it nothing inside that pcb.
        this->pcb.resize(idx + 1, nullptr);//working with vectors, we can use resize to increase our array/vectors
    }
    //then we have that new pcb stored at that new pcb[idx]. But use this-> because its two different objects. or it will copy itself and not the new one.
    this->pcb[idx] = pcb;
}
