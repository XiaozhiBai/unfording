#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "SimTreeAna.h"

void runTreeAna(const char* filelist = "input.txt", const char* outFileName = "test.root") {

    // Analysis starts here
    SimTreeAna* mSimTreeAna = new SimTreeAna(outFileName);
    mSimTreeAna->bookHistogram();

    char filename[1000];
    std::ifstream fstream(filelist);
    while (fstream >> filename) {
        mSimTreeAna->read(filename);
    }

    mSimTreeAna->WriteHistogram();
    delete mSimTreeAna;
}

// Main function to allow compilation into an executable
int main(int argc, char* argv[]) {

  // Checking if the number of arguments is equal to 3
    // argc always includes the program name as the first argument, so we expect argc to be 3
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " arg1 arg2" << std::endl;
        return 1; // Return an error code
    }

    // If the program reaches this point, the correct number of arguments were passed
    std::cout << "Argument 1: " << argv[1] << std::endl;
    std::cout << "Argument 2: " << argv[2] << std::endl;
    
  TString inputlist=argv[1];
  TString outputname=argv[2];
  
  
    
  runTreeAna(inputlist.Data(),outputname.Data());
    return 0;
}
