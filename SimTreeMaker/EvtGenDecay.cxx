#include <iostream>

#include "EvtGenDecay.h"

//using namespace Pythia8; // allow simplified notation.
// Include specific headers from EvtGen, Pythia8, ROOT, etc.

EvtGenDecay::EvtGenDecay(TString OutputName) {
    // Constructor implementation
  //  std::cout<< "Start to  Initialize your EvtGen, Pythia8, ROOT objects, etc."<<std::endl;
  mOutputName=new TFile(OutputName.Data(),"RECREATE");
  tree=new TTree("TT","TT");  
}

EvtGenDecay::~EvtGenDecay() {
  // Destructor implementation
  // Clean up resources, delete pointers, etc.
  //  delete mOutputName;
}

void EvtGenDecay::initialize() {
    // Initialize the simulation environment
    // Setup EvtGen, Pythia8, and ROOT as necessary
// Read in settings
 Event& event = pythia.event; // quick access to current event.

 pythia.readString("Beams:idA = 2212");//2212=p
  pythia.readString("Beams:idB = 2212");//2212=p
  pythia.readString("Beams:eCM = 13000.0");
  pythia.readString("HardQCD:all = on");
  pythia.readString("Random:setSeed = on");// Random seed on
  pythia.readString("Random:seed = 0 ");//a value 0 gives a random seed based on the time

  //pythia mother
    tree->Branch("motherId", &motherId, "motherId/I");
    tree->Branch("motherPx", &motherPx, "motherPx/D");
    tree->Branch("motherPy", &motherPy, "motherPy/D");
    tree->Branch("motherPz", &motherPz, "motherPz/D");
    tree->Branch("motherE", &motherE, "motherE/D");
    tree->Branch("motherMass", &motherMass, "motherMass/D");
    tree->Branch("motherPt", &motherPt, "motherPt/D");
    tree->Branch("motherRapidity", &motherRapidity, "motherRapidity/D");
    tree->Branch("motherEta", &motherEta, "motherEta/D");
    
    //pythia daughter
    tree->Branch("pythiaDaughterId", &pythiaDaughterId, "pythiaDaughterId[1000]/I");
    tree->Branch("pythiaDaughterPt", &pythiaDaughterPt, "pythiaDaughterPt[1000]/D");
    tree->Branch("pythiaDaughterRapidity", &pythiaDaughterRapidity, "pythiaDaughterRapidity[1000]/D");
    tree->Branch("pythiaDaughterNum", &pythiaDaughterNum, "pythiaDaughterNum[1000]/I");

    //evtgen daughter
    tree->Branch("evtDaughterId", &evtDaughterId, "evtDaughterId[1000]/I");
    tree->Branch("evtDaughterPt", &evtDaughterPt, "evtDaughterPt[1000]/D");
    tree->Branch("evtDaughterRapidity", &evtDaughterRapidity, "evtDaughterRapidity[1000]/D");
    tree->Branch("evtDaughterNum", &evtDaughterNum, "evtDaughterNum[1000]/I");

    // local variables etc. here. E.g.

    pythia.init(); // Initialize
 
    //    EvtGen* myGenerator;
    //   Initialize evtgen
    EvtGenReport(EVTGEN_INFO, "EvtGen") << "Starting EvtGen" << endl;
    // Define the random number generator
    time_t t=time(nullptr);
    int seed = static_cast<int>(t);
    EvtRandomEngine* eng =  new EvtMTRandomEngine(seed);
    EvtRandom::setRandomEngine( eng );
    
    // Specify if we want to use Pythia 6 physics codes for decays
    bool convertPythiaCodes(false);
    // Specify the pythia xml data directory to use the default PYTHIA8DATA location
    std::string pythiaDir("/evtgen/share/Pythia8/xmldoc");
    // Specify the photon type for Photos
    std::string photonType("gamma");
    // Specify if we want to use the EvtGen random number engine for these generators
    bool useEvtGenRandom(true);
    // Set up the default external generator list: Photos, Pythia and/or Tauola
    EvtExternalGenList genList(convertPythiaCodes, pythiaDir, photonType, useEvtGenRandom);
    // Get the interface to the radiative correction engine
    EvtAbsRadCorr* radCorrEngine = genList.getPhotosModel();
    // Get the interface to the other external generators (Pythia and Tauola)
    std::list<EvtDecayBase*> extraModels = genList.getListOfModels();

    // Create the EvtGen generator object, passing the external generators
    myGenerator=new EvtGen("EvtGenSetUp/DECAY.DEC", "EvtGenSetUp/evt.pdl", eng, radCorrEngine, &extraModels);

    //------------------------------------------------
    
}

void EvtGenDecay::runDecay(const int nEvent) {

  for(int iEvent = 0; iEvent < nEvent; iEvent++){
    cout<< iEvent<<endl;
    // Generate next event;
        // Produce the next event, returns true on success.
        if(!pythia.next()) {
        // Any error handling goes here.
        }
        // Analyse event; fill histograms etc.
        number_tracks_event = pythia.event.size();
        for (int i=0; i<number_tracks_event; i++) {
            if(!isBottomedHadron(pythia.event[i].id()))
                continue;
            bool isMother = false;
            int daughter1_track = pythia.event[i].daughter1();
            int daughter2_track = pythia.event[i].daughter2();
            switch(judgedecay(daughter1_track, daughter2_track)){
                case 1:
                    motherId       = pythia.event[i].id();
                    motherPx       = pythia.event[i].px();
                    motherPy       = pythia.event[i].py();
                    motherPz       = pythia.event[i].pz();
                    motherE        = pythia.event[i].e();
                    motherMass     = pythia.event[i].m();
                    motherPt       = pythia.event[i].pT();
                    motherRapidity = pythia.event[i].y();
                    motherEta      = pythia.event[i].eta();
                    isMother       = true;
                    break;
                case 2:
                    if(!isBottomedHadron(pythia.event[daughter1_track].id())){
                        motherId       = pythia.event[i].id();
                        motherPx       = pythia.event[i].px();
                        motherPy       = pythia.event[i].py();
                        motherPz       = pythia.event[i].pz();
                        motherE        = pythia.event[i].e();
                        motherMass     = pythia.event[i].m();
                        motherPt       = pythia.event[i].pT();
                        motherRapidity = pythia.event[i].y();
                        motherEta      = pythia.event[i].eta();
                        isMother       = true;
                    }
                    break;
                case 3:
                    if(!isBottomedHadron(pythia.event[daughter1_track].id())){
                        motherId       = pythia.event[i].id();
                        motherPx       = pythia.event[i].px();
                        motherPy       = pythia.event[i].py();
                        motherPz       = pythia.event[i].pz();
                        motherE        = pythia.event[i].e();
                        motherMass     = pythia.event[i].m();
                        motherPt       = pythia.event[i].pT();
                        motherRapidity = pythia.event[i].y();
                        motherEta      = pythia.event[i].eta();
                        isMother       = true;
                    }
                    break;
                case 4:
                    for(int j=daughter1_track; j<=daughter2_track; j++){
                        if(isBottomedHadron(pythia.event[j].id())){
                            isMother = false;
                            break;
                        }
                        isMother = true;    
                    }
                    if(isMother){
                        motherId       = pythia.event[i].id();
                        motherPx       = pythia.event[i].px();
                        motherPy       = pythia.event[i].py();
                        motherPz       = pythia.event[i].pz();
                        motherE        = pythia.event[i].e();
                        motherMass     = pythia.event[i].m();
                        motherPt       = pythia.event[i].pT();
                        motherRapidity = pythia.event[i].y();
                        motherEta      = pythia.event[i].eta();
                        storePythiaDaughter(&pythia.event[0], i, &pythiaDaughterId[0], &pythiaDaughterPt[0], &pythiaDaughterRapidity[0], &pythiaDaughterNum[0], 0, 0);
                    }
                    break;
                case 5:
                    if(!isBottomedHadron(pythia.event[daughter1_track].id()) && !isBottomedHadron(pythia.event[daughter2_track].id())){
                        motherId       = pythia.event[i].id();
                        motherPx       = pythia.event[i].px();
                        motherPy       = pythia.event[i].py();
                        motherPz       = pythia.event[i].pz();
                        motherE        = pythia.event[i].e();
                        motherMass     = pythia.event[i].m();
                        motherPt       = pythia.event[i].pT();
                        motherRapidity = pythia.event[i].y();
                        motherEta      = pythia.event[i].eta();
                        isMother       = true;
                        storePythiaDaughter(&pythia.event[0], i, &pythiaDaughterId[0], &pythiaDaughterPt[0], &pythiaDaughterRapidity[0], &pythiaDaughterNum[0], 0, 0);
                    }
                    break;
                default:
                    break;
            }
            if(isMother){
                EvtVector4R pInit(pythia.event[i].e(), pythia.event[i].px(), pythia.event[i].py(), pythia.event[i].pz());
		        EvtParticle* parent = EvtParticleFactory::particleFactory(EvtPDL::getId(GetEvtGenName(pythia.event[i].id())), pInit);
		       
                //SET evtgen
                myGenerator->generateDecay(parent);

                storeEvtDaughter(parent, &evtDaughterId[0], &evtDaughterPt[0], &evtDaughterRapidity[0], &evtDaughterNum[0], 0, 0);
                tree->Fill();
            }
        }
    } // End event loop.
    // --- Calculate final statistics ---
    //pythia.stat();
    // Print histograms etc.

  
    // Main method to run decay simulations
    // This could involve generating initial events with Pythia8,
    // processing them with EvtGen, and storing results with ROOT
}

int EvtGenDecay::storePythiaDaughter(Pythia8::Particle* particle, int order, int* daughterId, double* daughterPt, double* daughterRapidity, int* daughterNum, int num, int motherNum){
  //   int  judgedecay(int dau1,int dau2);
    int daughter1_track = particle[order].daughter1();
    int daughter2_track = particle[order].daughter2();
    switch(judgedecay(daughter1_track, daughter2_track)){
        int temp, mother;
        case 4:
            for(int k=daughter1_track; k<=daughter2_track; k++){
                daughterId[num]       = particle[k].id();
                daughterPt[num]       = particle[k].pT();
                daughterRapidity[num] = particle[k].y();
                daughterNum[num]      = 100*motherNum + motherNum%100 - motherNum%10 + 10 + k-daughter1_track;
                num++;
                num = storePythiaDaughter(particle, k, &daughterId[0], &daughterPt[0], &daughterRapidity[0], &daughterNum[0], num, 100*motherNum + motherNum%100 - motherNum%10 + 10 + k-daughter1_track);
            }
            break;
        case 5:
            daughterId[num]       = particle[daughter1_track].id();
            daughterPt[num]       = particle[daughter1_track].pT();
            daughterRapidity[num] = particle[daughter1_track].y();
            daughterNum[num]      = 100*motherNum + motherNum%100 - motherNum%10 + 10;
            num++;
            num = storePythiaDaughter(particle, daughter1_track, &daughterId[0], &daughterPt[0], &daughterRapidity[0], &daughterNum[0], num, 100*motherNum + motherNum%100 - motherNum%10 + 10);
            daughterId[num]       = particle[daughter2_track].id();
            daughterPt[num]       = particle[daughter2_track].pT();
            daughterRapidity[num] = particle[daughter2_track].y();
            daughterNum[num]      = 100*motherNum + motherNum%100 - motherNum%10 + 11;
            num++;
            num = storePythiaDaughter(particle, daughter2_track, &daughterId[0], &daughterPt[0], &daughterRapidity[0], &daughterNum[0], num, 100*motherNum + motherNum%100 - motherNum%10 + 11);
            break;
        default:
            break;
    }
    return num;
}

int EvtGenDecay::storeEvtDaughter(EvtParticle* particle, int* daughterId, double* daughterPt, double* daughterRapidity, int* daughterNum, int num, int motherNum){
    // double ComputePt(EvtParticle* parent);
    // double ComputeRapidity(EvtParticle* parent);
    // double ComputeEta(EvtParticle* parent);
    if(particle->getNDaug()>1){
        for(int k=0; k<particle->getNDaug(); k++){
            daughterId[num]       = EvtPDL::getStdHep(particle->getDaug(k)->getId());
            daughterPt[num]       = ComputePt(particle->getDaug(k));
            daughterRapidity[num] = ComputeRapidity(particle->getDaug(k));
            daughterNum[num]      = 100*motherNum + motherNum%100 - motherNum%10 + 10 + k;
            num++;
            num = storeEvtDaughter(particle->getDaug(k), &daughterId[0], &daughterPt[0], &daughterRapidity[0], &daughterNum[0], num, 100*motherNum + motherNum%100 - motherNum%10 + 10 + k);
        }
    }
    return num;
}

int EvtGenDecay::judgedecay(int dau1, int dau2){
    if(dau1==dau2)
        if(0==dau1)
            return 1;//daughter1 = daughter2 = 0: there are no daughters (so far);
        else 
            return 2;//daughter1 = daughter2 > 0: the particle has a "carbon copy" as its sole daughter, but with changed momentum as a "recoil" effect, e.g. in a shower;
    if(0==dau2)
        return 3;//daughter1 > 0, daughter2 = 0: each of the incoming beams has only (at most) one daughter, namely the initiator parton of the hardest interaction; further, in a 2->1 hard interaction, like q qbar->Z^0, or in a clustering of two nearby partons, the initial partons only have this one daughter;
    if(dau1<dau2)
        return 4;//daughter1 < daughter2, both > 0: the particle has a range of decay products from daughter1 to daughter2;
    else
        return 5;//daughter2 < daughter1, both > 0: the particle has two separately stored decay products (e.g. in backwards evolution of initial-state showers).
    return 0;
}

bool EvtGenDecay::isBottomedHadron(int idSave) {
  //  bool isHadron(int idSave);
  idSave = abs(idSave);
  if (!isHadron(idSave))
    return false;
  if (idSave / 100 == 5 || idSave / 1000 == 5 || idSave / 10000 == 5 || idSave / 1000000 == 5)
    return true;
  return false;
}

bool EvtGenDecay::isHadron(int idSave) {
  idSave = abs(idSave);
  if (idSave <= 100 || (idSave >= 1000000 && idSave <= 9000000) ||
      idSave >= 9900000)
    return false;
  if (idSave == 130 || idSave == 310)
    return true;
  if (idSave % 10 == 0 || (idSave / 10) % 10 == 0 || (idSave / 100) % 10 == 0)
    return false;
  return true;
}
    
std::string EvtGenDecay::GetEvtGenName(int PythiaID){
    // Convert Pythia particle ID to EvtGen particle Name
    EvtId EvtGenID=EvtPDL::evtIdFromLundKC(PythiaID);
    return EvtGenID.getName();
}

double EvtGenDecay::ComputePt(EvtParticle* parent){
    EvtVector4R p = parent->getP4Lab();
    TLorentzVector pairP;
    pairP.SetPxPyPzE(p.get(1),p.get(2),p.get(3),p.get(0));
    return pairP.Pt();
}

double EvtGenDecay::ComputeRapidity(EvtParticle* parent){
    EvtVector4R p = parent->getP4Lab();  
    TLorentzVector pairP;
    pairP.SetPxPyPzE(p.get(1),p.get(2),p.get(3),p.get(0));
    return pairP.Rapidity();
}

double ComputeEta(EvtParticle* parent){
    EvtVector4R p = parent->getP4Lab();
    TLorentzVector pairP;
    pairP.SetPxPyPzE(p.get(1),p.get(2),p.get(3),p.get(0));
    return pairP.Eta();
}


// void EvtGenDecay::finalize() {
//     // Cleanup and finalization
//     // Might include writing results to files, printing statistics, etc.
// }
void  EvtGenDecay::finalize(){
  mOutputName->cd();
  // //  TFile *out = new TFile("outputevtgen.root","recreate");/////////  
  tree->Write();
  mOutputName->Close();
  return;
}
