#include <iostream>
#include "AsTheCrowFlies.h"


//class AsTheCrowFlies;

int main(int argc, char* argv[]) {
    
    // Check if the program is given 2 command line arguments
    // including the program name.
    if (argc != 2) {
      std::cerr << "USAGE: ./a.out <total_city_list> "
                << std::endl;
      return -1;
      }
      
      // Open the input file(s) containing the raw data.
      
      AsTheCrowFlies session;
      
      
      
    
    return session.menu(argv[1]);
}