/**
   \class SimTreeAna.h

   \brief Analysis the simulation tree production pruduction

   Authors: Xiaozhi Bai (baixiaozhi@ustc.edu.cn,xiaozhi.bai@cern.ch),
            Guangsheng Li (ego2017@mail.ustc.edu.cn)
            
*/

#ifndef EVTGENDECAY_H
#define EVTGENDECAY_H

//evtgen
#include "EvtGen/EvtGen.hh"

#include "EvtGenBase/EvtAbsRadCorr.hh"
#include "EvtGenBase/EvtComplex.hh"
#include "EvtGenBase/EvtConst.hh"
#include "EvtGenBase/EvtDecayBase.hh"
#include "EvtGenBase/EvtDecayTable.hh"
#include "EvtGenBase/EvtDiracSpinor.hh"
#include "EvtGenBase/EvtGammaMatrix.hh"
#include "EvtGenBase/EvtIdSet.hh"
#include "EvtGenBase/EvtKine.hh"
#include "EvtGenBase/EvtMTRandomEngine.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParser.hh"
#include "EvtGenBase/EvtParticle.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtRadCorr.hh"
#include "EvtGenBase/EvtRandom.hh"
#include "EvtGenBase/EvtRandomEngine.hh"
#include "EvtGenBase/EvtReport.hh"
//#include "EvtGenBase/EvtGenEnums.h"
#include "EvtGenBase/EvtSecondary.hh"
#include "EvtGenBase/EvtSimpleRandomEngine.hh"
#include "EvtGenBase/EvtStdHep.hh"
#include "EvtGenBase/EvtTensor4C.hh"
#include "EvtGenBase/EvtVector4C.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtVectorParticle.hh"
#include "EvtGenBase/EvtSpinDensity.hh"
#include "EvtGenBase/EvtAmp.hh"
#include "EvtGenBase/EvtId.hh"
#include "EvtGenBase/EvtPatches.hh"

//#ifdef EVTGEN_EXTERNAL
#include "EvtGenExternal/EvtExternalGenList.hh"
//#endif

//root
#include "TApplication.h"
#include "TLorentzVector.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TROOT.h"
#include "TTree.h"
#include "TString.h"

//other
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

//pythia
#include "Pythia8/Pythia.h" // access to Pythia objects.
using namespace Pythia8; // allow simplified notation.


// Include EvtGen headers
// Include other necessary libraries here

class EvtGenDecay {
  
public:
    EvtGenDecay(TString OutputName); // Constructor
    ~EvtGenDecay(); // Destructor

    void initialize(); // Setup simulation environment
    void runDecay(const int); // Run the decay simulation
    void finalize(); // Cleanup and finalize

  //Pythia8::Pythia pythia;//  Pythia pythia;

    //  int storeEvtDaughter(EvtParticle* particle, int* daughterId, double* daughterPt, double* daughterRapidity, int* daughterNum, int num, int motherNum);
  double ComputePt(EvtParticle* parent);
  double ComputeRapidity(EvtParticle* parent);
  double ComputeEta(EvtParticle* parent);
    
  bool isHadron(int);  
  int storePythiaDaughter(Pythia8::Particle* particle, int order, int* daughterId, double* daughterPt, double* daughterRapidity, int* daughterNum, int num,  int motherNum);
  int storeEvtDaughter(EvtParticle* particle, int* daughterId, double* daughterPt, double* daughterRapidity, int* daughterNum, int num,  int motherNum);
  int  judgedecay(int dau1,int dau2);
  bool isBottomedHadron(int idSave);
  std::string GetEvtGenName(int PythiaID);

  
private:

  TFile *mOutputName;

  
  // EvtGen pointer, assuming you have EvtGen setup
  Pythia pythia;//  Pythia pythia;

  EvtGen* myGenerator;

  //  int nEvent;
  
    // Add other member variables as necessary
// Define histograms, external links,
    int number_tracks_event;
    int motherId, pythiaDaughterId[1000], pythiaDaughterNum[1000], evtDaughterId[1000], evtDaughterNum[1000];
    double motherPx, motherPy, motherPz, motherE, motherMass, motherPt, motherRapidity, motherEta;
    double pythiaDaughterPt[1000], pythiaDaughterRapidity[1000];
    double evtDaughterPt[1000], evtDaughterRapidity[1000];


  TTree *tree;
  
};

#endif // EVTGENDECAY_H
