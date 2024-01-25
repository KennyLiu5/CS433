
/**
* Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author NAME
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

#include "buffer.h"
#include <iostream>
using namespace std;
   /**
     * @brief Construct a new Buffer object
     * @param size the size of the buffer
     */
Buffer::Buffer(int size)
{
  length = size;
  count = 0;
  front = 0;//yo you mind if you can share me what you got for Q's 1-18 lol
  rear = -1;
  buffer[0] = 0; // initializing buffer to have 0 elements/0 at index 0
}
    /**
     * @brief Destroy the Buffer object
     */
Buffer::~Buffer()
{
  while(!is_empty())
    {
      buffer_item temp = buffer[front];
      remove_item(&temp); // removes item in the front of buffer
    }
}
   /**
     * @brief Insert an item into the buffer
     * @param item the item to insert
     * @return true if successful
     * @return false if not successful
     */
bool Buffer::insert_item(buffer_item item)
{
  if(!is_full()) // not full, add element to buffer
  {
    rear = (rear + 1) % length/*BUFFER_SIZE*/;
    buffer[rear] = item;
    count++;
    return true;
  }
  else
  {
    return false; 
  }
}
   /**
     * @brief Remove an item from the buffer
     * @param item the item to remove
     * @return true if successful
     * @return false if not successful
     */
bool Buffer::remove_item(buffer_item *item)
{
  if(!is_empty()) // not empty, remove element from buffer
  {
    *item = buffer[front]; //fails cpp test if item = &buffer[front];
    front = (front + 1) % length/*BUFFER_SIZE*/;
    count--;
    return true;
  }
  return false;
}
    /**
     * @brief Get the size of the buffer
     * @return the size of the buffer
     */
int Buffer::get_size()
{
  return length/*BUFFER_SIZE*/;
}
    /**
     * @brief Get the number of items in the buffer
     * @return the number of items in the buffer
     */
int Buffer::get_count()
{
  return count;
}
   /**
     * @brief Chceck if the buffer is empty
     * @return true if the buffer is empty, else false
     */
bool Buffer::is_empty()
{
  if(count == 0)
    return true;
  else
    return false;
}
 /**
   * @brief Check if the buffer is full
   * @return true if the buffer is full, else false
   */
bool Buffer::is_full()
{
  if(count == length/*BUFFER_SIZE*/)
    return true;
  else
    return false;
}
/**
  * @brief Print the buffer
  */
void Buffer::print_buffer()
{
  int j = front;
  if(is_empty()) 
  {
    cout << "\n-- Buffer is empty --\n\n";
  }
  else
  {
    cout << "[";
    for(int i = 1; i <= count; i++)
    {
      if(j == rear) // only element left or last - do not show comma
        cout << buffer[j];
      else
        cout << buffer[j] << ", ";
      j = (j + 1) % length/*BUFFER_SIZE*/;
    }
    cout << "]\n";
  }
}
