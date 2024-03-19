#include <iostream>
#include <fstream>
#include "TSystem.h"

#include "EvtGenDecay.h"

void runSimTreeMaker(const int NEvent=10000, const char* outFileName = "SimTreeTest.root") {

    // Analysis starts here
  EvtGenDecay *mEvtGenDecay=  new EvtGenDecay(outFileName);
  mEvtGenDecay->initialize();
  mEvtGenDecay->runDecay(NEvent);
  mEvtGenDecay-> finalize();
  
  return ;
}

// Main function to allow compilation into an executable
int main(int argc, char* argv[]) {

  // Check if the correct number of arguments is passed
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <integer> <TString>" << std::endl;
        return 1; // Return error code if not
    }
    

    // If the program reaches this point, the correct number of arguments were passed
    std::cout << "Argument 1: " << argv[1] << std::endl;
    std::cout << "Argument 2: " << argv[2] << std::endl;
    
    const int NEvents= std::atoi(argv[1]);
    const TString outputname=argv[2];

    // Example usage of the arguments
    std::cout << "Number of events : " << NEvents << std::endl;
    std::cout << "TString argument: " << outputname.Data() << std::endl;
    
  
    
    runSimTreeMaker(NEvents,outputname.Data());
    return 0;
}
