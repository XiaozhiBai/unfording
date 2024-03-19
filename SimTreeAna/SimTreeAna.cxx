#include "SimTreeAna.h"
#include "TFile.h"
#include "TChain.h"
#include "TRandom.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
//#include "RooUnfoldSvd.h"
//#include "RooUnfoldTUnfold.h"
//#include "RooUnfoldIds.h"

#include "TApplication.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TTree.h"
#include "TString.h"

#include <TMath.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TFitter.h>
#include <TF1.h>
#include <TStyle.h>
#include <TVector.h>
#include <TGraph.h>

#include <iostream>
#include <TFile.h>
#include <TMatrixD.h>
#include "TUnfoldDensity.h"

SimTreeAna::SimTreeAna(const std::string& outputFile) : outputFile(outputFile) {
  //    hExampleHistogram = nullptr;
}

SimTreeAna::~SimTreeAna() {
    // Cleanup if necessary
}

void SimTreeAna::bookHistogram() {
    // Example histogram booking
    hExampleHistogram = new TH1F("hExample", "Example Histogram", 100, 0, 100);
    //    hpythiaB = new TH1D("hpythiaB", "hpythiaB;p_{T}(GeV/c)", binnB, binB);


    
}

void SimTreeAna::read(const std::string& inputFile) {
    // Example of reading a file and filling the histogram
    TChain chain("TT"); // Use the correct tree name
    chain.Add(inputFile.c_str());

    // Example variable to read from the tree
    double exampleVariable = 0;
    chain.SetBranchAddress("motherPx", &exampleVariable); // Use the correct branch name

    Long64_t nEntries = chain.GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        chain.GetEntry(i);
        hExampleHistogram->Fill(exampleVariable);
	//hpythiaB->Fill(sdsdsd);

	// if(EtaCut09(eta)
	//    FIll
	//    w
    }
}

void SimTreeAna::WriteHistogram() {
    TFile outFile(outputFile.c_str(), "RECREATE");

    hExampleHistogram->Write();
    //    hpythiaB->Wite()
    outFile.Close();
}
// bool SimTreeAna::EtaCut09() {
// ifskdhjgsjkdgf
//   {}
// }
