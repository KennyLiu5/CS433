
/**
* Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author NAME
 * @brief A class implementing the LIFO page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames), q()
{
  // initialized q line 15
}

LIFOReplacement::~LIFOReplacement() {
  while(!q.empty())
    {
      q.pop_back();
    }
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
  page_faults++; // invalid page, so it is a page fault
  page_table[page_num].valid = true; 
  q.push_back(page_num); // pushes page_num into vector
  page_table[page_num].frame_num = frame_count;
  frame_count++; // adding new page, so increment frame count
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
  page_faults++; // invalid page, so it is a page fault
  int last = q.back(); // gets number at rear of vector (last in)
  page_table[last].valid = false; // change that page entry to false, will be replaced
  q.pop_back(); // erases element in rear

  page_table[page_num].valid = true; // new page entry
  q.push_back(page_num);
  page_replacement++; // page replaced, so increment page replacement
  
  return 0;
}
