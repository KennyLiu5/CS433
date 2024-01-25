/**
* Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author NAME
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "fifo_replacement.h"
#include <iostream>

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames) , q()
{
}

FIFOReplacement::~FIFOReplacement() {
  while(!q.empty())
    {
      q.pop_back();
    }
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
  page_faults++; // invalid page, so it is a page fault
  page_table[page_num].valid = true; 
  q.push_back(page_num); // pushes page_num into vector
  page_table[page_num].frame_num = frame_count;
  frame_count++; // adding new page, so increment frame count
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
  page_faults++; // invalid page, so it is a page fault
  int front = q.front(); // gets number in front of vector (first in)
  page_table[front].valid = false; // change that page entry to false, will be replaced
  q.erase(q.begin()); // erases element in front - begin is index 0

  page_table[page_num].valid = true; // new page entry
  q.push_back(page_num);
  page_replacement++; // page replaced, so increment page replacement
  
  return 0;
}
