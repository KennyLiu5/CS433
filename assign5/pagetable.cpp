**
* Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author NAME
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "pagetable.h"

// Constrcutor
PageTable::PageTable(int num_pages) {
  for(int i=0; i<num_pages; i++)
    {
      PageEntry p;
      pages.push_back(p);
    }
}

// Destructor
PageTable::~PageTable() {
  while(!pages.empty()) // pop all page entries in page table
    {
      pages.pop_back();
    }
}
