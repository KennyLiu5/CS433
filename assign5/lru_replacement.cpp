/**
* Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author NAME
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "lru_replacement.h"

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
: Replacement(num_pages, num_frames), l(), u()
{
  // list l initialized on line 27
  // unordered_map u initalized on line 28
}

LRUReplacement::~LRUReplacement()
{
  /*while(!q.empty())
    {
      q.pop_back();
    }*/
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num)
{
  l.erase(u[page_num]); // remove the map 
  l.push_front(page_num);
  u[page_num] = l.begin(); // assign the position of the page into the map
  page_table[page_num].dirty = true; //change the page to true since it has been updated
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
  page_faults++; // invalid page, so it is a page fault
  l.push_front(page_num); // push it to the front of the list
  u[page_num] = l.begin(); // save the index of the page in the list to the map
  page_table[page_num].frame_num = frame_count++; // assign the page a new frame
  page_table[page_num].valid = true; // set to valid
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
  page_faults++; // invalid page, so it is a page fault
  page_replacement++; // page replaced, so increment page replacement

  int back = l.back();//assign to the back part of the list array to be stored
  l.pop_back();//pop the back

  page_table[back].valid = false;//since it is available, the table must be set to false
  page_table[page_num].valid = true;//the page is then taken
  page_table[page_num].frame_num = page_table[back].frame_num;

  u.erase(back);
  l.push_front(page_num);
  u[page_num] = l.begin();
  
  return 0;
}
/*    
OTHER / BUSTED IMPLEMENTATION

    page_faults++;
    int front = q.front(); // gets number in front of queue
    page_table[front].valid = false; // lru is in front, make valid to false
    q.pop(); // removes number from front
    page_table[page_num].valid = true; // new page 
    q.push(page_num);
    page_replacement++;

    int front = l.front();
    if(u.find(page_num) == u.end())//not present in cache
    {
      if(page_table[page_num].valid == false)//cache is full
      {
        //page_table[page_num].valid = false;
        int last = l.back();//delete lru element

        l.pop_back();//pop last element
        u.erase(last);//erase lru element
        page_replacement++;
      }
    }
    else//present in cache
    {
      page_table[page_num].valid = true;
      l.erase(u[page_num]);
    }
    //update reference
    l.push_front(page_num);
    u[page_num] = l.begin();
    page_faults++;
    int front = q.front(); // gets number in front of queue
    if(page_table[front].valid)
    {
      //page_table[front].valid = false; // lru is in front, make valid to false
      q.pop(); // removes number from front
      //page_faults++;
      page_replacement++;
    }
    else
    {
      page_table[page_num].valid = true; // new page 
      q.push(page_num);
      page_faults++;
      //page_replacement++;
    }
    for(int i = 0; i < q.size(); i++)
      {
        if(page_table[i] < last_found)
        {
          
        }
      }
    
//auto it = l.begin();

  //search function
  //doubly linked list <-> vector
  u[page_num] = l.begin();
  //auto i = u[page_num];
  bool found = false;
  while(u[page_num] != l.end() || !found) {
    if(*u[page_num] == page_num) {
      //it = q.erase(it);
      u[page_num] = l.erase(u[page_num]);
      //page_table[page_num].dirty = true;
      found = true;
    }
    else  
      //i++;
      u[page_num]++;
  }
if(u.find(page_num) != u.end())//if page is in the list
  {
    l.erase(u[page_num]); //erase if page is found in the list
  }
  l.push_front(page_num);//push the page to the front of the list
  u[page_num] = l.begin(); //assign position of page into the map array
  //page_table[page_num].dirty = true; // change the page to true since it has been updated
  //return;
page_table[page_num].valid = true; 
  l.push_back(page_num); // pushes page_num into vector
  page_table[page_num].frame_num = frame_count;
  frame_count++; // adding new page, so increment frame count
  //total_frames--;
  l.push_front(page_num);
  u[page_num] = l.begin();
  page_table[page_num].frame_num = frame_count++;
  page_table[page_num].valid = true;
  //total_frames--;
  page_faults++; // invalid page, so it is a page fault
 int last = l.back();
    l.pop_back();

    page_table[last].valid = false;
    page_table[page_num].valid = true;

    page_table[page_num].frame_num = page_table[last].frame_num;

    u.erase(last);
    l.push_back(page_num);
    u[page_num] = l.begin();
    int back = q.back();//int front = q.front(); // gets number in front of vector (first in)
    q.pop_back();
    page_table[back].valid = false; // change that page entry to false, will be replaced
  
    page_table[page_num].valid = true; // new page entry
    page_table[page_num].frame_num = page_table[back].frame_num;
    
    u.erase(back); // erases element in back - begin is index 0
    q.push_back(page_num);
    u[page_num] = q.begin();*/
