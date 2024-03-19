/**
1;95;0c   \class SimTreeAna.h

   \brief Analysis the simulation tree

   Authors: Xiaozhi Bai (baixiaozhi@ustc.edu.cn,xiaozhi.bai@cern.ch),
            Guangsheng Li (ego2017@mail.ustc.edu.cn)
            
*/

#ifndef SIMTREEANA_H
#define SIMTREEANA_H

#include "TTree.h"
#include "TH1F.h"
#include <string>
#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"

class SimTreeAna {
public:
    SimTreeAna(const std::string& outputFile);
    virtual ~SimTreeAna();

    void bookHistogram();
    void read(const std::string& inputFile);
    void WriteHistogram();

private:
    TH1F* hExampleHistogram;

  TH1D* hpythiaB;// = new TH1D("hpythiaB", "hpythiaB;p_{T}(GeV/c)", binnB, binB);
    // TH1D* hpythiaJpsi = new TH1D("hpythiaJpsi", "hpythiaJpsi;p_{T}(GeV/c)", binnJpsi, binJpsi);
    // TH1D* hevtgenB = new TH1D("hevtgenB", "hevtgenB;p_{T}(GeV/c)", binnB, binB);
    // TH1D* hevtgenJpsi = new TH1D("hevtgenJpsi", "hevtgenJpsi;p_{T}(GeV/c)", binnJpsi, binJpsi);
  RooUnfoldResponse response_pyt_15_25;//(40, -10.0, 10.0);
  //  RooUnfoldResponse response (40, -10.0, 10.0);
  //  RooUnfoldResponse response (40, -10.0, 10.0);
  std::string outputFile;
};

#endif // SIMTREEANA_H
