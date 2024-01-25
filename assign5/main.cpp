

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "fifo_replacement.h"
#include "lru_replacement.h"
#include "lifo_replacement.h"

//#include <chrono> //added to get elapsed time

// Check if an integer is power of 2
bool isPowerOfTwo(unsigned int x) {
    /* First x in the below expression is for the case when x is 0 */
    return x && (!(x & (x - 1)));
}

int main(int argc, char *argv[]) {
    //Print basic information about the program
    std::cout << "=================================================================" << std::endl;
    std::cout << "CS 433 Programming assignment 5" << std::endl;
    std::cout << "Author: NAME" << std::endl;
    std::cout << "Date: " << std::endl;
    std::cout << "Course: CS433 (Operating Systems)" << std::endl;
    std::cout << "Description : Program to simulate different page replacement algorithms" << std::endl;
    std::cout << "=================================================================\n" << std::endl;

    if (argc < 3) {
        // user does not enter enough parameters
        std::cout << "You have entered too few parameters to run the program.  You must enter" << std::endl
                  << "two command-line arguments:" << std::endl
                  << " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
                  << " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
        exit(1);
    }

    // Page size and Physical memory size
    // Their values should be read from command-line arguments, and always a power of 2
    unsigned int page_size = atoi(argv[1]);
    if (!isPowerOfTwo(page_size)) {
        std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
                  << "  (must be an power of 2 between 256 and 8192, inclusive)." << std::endl;
        return 1;
    }
    unsigned int phys_mem_size = atoi(argv[2]) << 20; // convert from MB to bytes
    if (!isPowerOfTwo(phys_mem_size)) {
        std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
                  << "  (must be an even integer between 4 and 64, inclusive)." << std::endl;
        return 1;
    }

    // calculate number of pages and frames;
    int logic_mem_bits = 27;        // 27-bit logical memory (128 MB logical memory assumed by the assignment)
    int phys_mem_bits = std::log2(
            phys_mem_size);        // Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
    int page_offset_bits = std::log2(
            page_size);                // Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
    // Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
    int num_pages = 1 << (logic_mem_bits - page_offset_bits);
    // Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
    int num_frames = 1 << (phys_mem_bits - page_offset_bits);

    std::cout << "Page size = " << page_size << " bytes" << std::endl;
    std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
    std::cout << "Number of pages = " << num_pages << std::endl;
    std::cout << "Number of physical frames = " << num_frames << std::endl;

    // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
  
    std::cout << "\n================================Test 1==================================================\n";
    std::ifstream in;
    // Open the samll reference file
    in.open("small_refs.txt");
    if (!in.is_open()) {
        std::cerr << "Cannot open small_refs.txt to read. Please check your path." << std::endl;
        return 1;
    }
    int val;
    // Create a vector to store the logical addresses
    std::vector<int> small_refs;
    while (in >> val) {
        small_refs.push_back(val);
    }
  
    // Create a virtual memory simulation using FIFO replacement algorithm
    FIFOReplacement vm(num_pages, num_frames);
    for (std::vector<int>::const_iterator it = small_refs.begin(); it != small_refs.end(); ++it) {
        int page_num = (*it) >> page_offset_bits; 
        bool isPageFault = vm.access_page(page_num, 0);
        PageEntry pg = vm.getPageEntry(page_num);
        std::cout << "Logical address: " << *it << ", \tpage number: " << page_num;
        std::cout << ", \tframe number = " << pg.frame_num << ", \tis page fault? " << isPageFault << std::endl;
    }
    in.close();
    vm.print_statistics();
    std::cout << "\n================================Test 2==================================================\n";

    std::cout << "****************Simulate FIFO replacement****************************" << std::endl;
  // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
    std::ifstream large; //set a name of the file variable
    large.open("large_refs.txt");
    if(!large.is_open()) //test case if the large_refs.txt file cannot be opened
    {
      std::cerr << "Cannot open large_refs.txt to read. Please check your path." << std::endl;
      return 1;
    }
  
    int val2;
    // Create a vector to store the logical addresses
    std::vector<int> large_refs;
    while (large >> val2) {
        large_refs.push_back(val2);
    }
    //auto t1 = std::chrono::high_resolution_clock::now(); 
    clock_t start, start2, start3, end, end2, end3;
    double elapsedTime, elapsedTime2, elapsedTime3;
    
    start = clock();
    FIFOReplacement FIFO(num_pages, num_frames);
    for(std::vector<int>::const_iterator i = large_refs.begin(); i != large_refs.end(); i++)
      {
        int page_num = (*i) >> page_offset_bits;
        FIFO.access_page(page_num, 0); 
        //PageEntry pgF = FIFO.getPageEntry(page_num);
      }
    end = clock();
    elapsedTime = double(end - start) / double(CLOCKS_PER_SEC);
    FIFO.print_statistics();
    std::cout << "Elapsed time = " << elapsedTime << " seconds" << std::endl;
    /*auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);*/
    //std::cout << "Elapsed time = " << elapsedTime.count() << " seconds" << std::endl;
    
   
    std::cout << "****************Simulate LIFO replacement****************************" << std::endl;
    // TODO: Add your code to calculate number of page faults using LIFO replacement algorithm
    //auto t3 = std::chrono::high_resolution_clock::now(); 
    start2 = clock();
    LIFOReplacement LIFO(num_pages, num_frames);
    for(std::vector<int>::const_iterator i = large_refs.begin(); i != large_refs.end(); i++)
      {
        int page_num = (*i) >> page_offset_bits;
        /*bool isPageFault =*/LIFO.access_page(page_num, 0); 
        //PageEntry pgL = LIFO.getPageEntry(page_num);
      }
    end2 = clock();  
    elapsedTime2 = double(end2 - start2) / double(CLOCKS_PER_SEC);
    LIFO.print_statistics();
    std::cout << "Elapsed time = " << elapsedTime2 << " seconds" << std::endl;
    //auto t4 = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> elapsedTime2 = std::chrono::duration_cast<std::chrono::duration<double>>(t4 - t3);
    //std::cout << "Elapsed time = " << elapsedTime2.count() << " seconds" << std::endl;

    std::cout << "****************Simulate LRU replacement****************************" << std::endl;
    start3 = clock();
    //auto t5 = std::chrono::high_resolution_clock::now(); 
    LRUReplacement LRU(num_pages, num_frames);
    for(std::vector<int>::const_iterator i = large_refs.begin(); i != large_refs.end(); i++)
      {
        int page_num = (*i) >> page_offset_bits;
        /*bool isPageFault =*/ LRU.access_page(page_num, 0); 
        //PageEntry pgLRU = LRU.getPageEntry(page_num);
      }
    end3 = clock();
    elapsedTime3 = double(end3 - start3) / double(CLOCKS_PER_SEC);
    LRU.print_statistics();
    std::cout << "Elapsed time = " << elapsedTime3 << " seconds" << std::endl;
    //auto t6 = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> elapsedTime3 = std::chrono::duration_cast<std::chrono::duration<double>>(t6 - t5);
    //std::cout << "Elapsed time = " << elapsedTime3.count() << " seconds" << std::endl;

  large.close();
}
