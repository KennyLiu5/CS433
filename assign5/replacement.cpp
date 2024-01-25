/**
* Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author NAME
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "replacement.h"


// Constructor
Replacement::Replacement(int num_pages, int num_frames)
: page_table(num_pages)
{
  total_pages = num_pages;
  total_frames = num_frames;

  // additional member variables initialized
  references = 0; 
  page_faults = 0; 
  page_replacement = 0; 

  frame_count = 0;  
}

// Destructor
Replacement::~Replacement()
{
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write)
{
  
  // If the page is valid, it calls the touch_page function. 1
  // If the page is not valid but free frames are available, it calls the load_page function. 2
  // If the page is not valid and there is no free frame, it calls the replace_page function. 3
  //PageEntry page;
  references++;
  
  if(!page_table[page_num].valid && frame_count < total_frames) // 2 - not valid, free frames
  {
    load_page(page_num);
    return true;
  }
  else if(!page_table[page_num].valid && frame_count >= total_frames) // 3 - not valid, free frames
  {
    replace_page(page_num);
    return true;
  }
  else 
  {// 1 - valid
    touch_page(page_num);
  }
  return false;
}
  
// Print out statistics of simulation
void Replacement::print_statistics() const {
	std::cout << "Number of references: \t\t"  << references << std::endl;
	std::cout << "Number of page faults: \t\t" << page_faults << std::endl;
	std::cout << "Number of page replacements: \t"  << page_replacement << std::endl;
}
