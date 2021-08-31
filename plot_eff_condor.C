#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TFile.h>
#include <TEfficiency.h>
#include <TTree.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include "fstream"
using namespace std;

double deltaR (double eta1, double phi1, double eta2, double phi2){
  double dp = std::abs(phi1 - phi2);
  if (dp > double(M_PI)) dp -= double(2 * M_PI);
  double deltaR2 = (eta1 - eta2) * (eta1 - eta2) + dp * dp;
  return std::sqrt(deltaR2);
};

void calc_jet_eff(string path, const char *inFile, const char *outFile){
  double ETHIGH = 800;
  if(path=="HLT_PFHT800" || path=="HLT_PFHT900" || path=="HLT_PFHT1050") ETHIGH = 2500;
  TH1F* h_all = new TH1F("h_all", "h_all", 50, 0, ETHIGH);
  TH1F* h_pass = new TH1F("h_pass", "h_pass", 50, 0, ETHIGH);
  h_all->Sumw2();
  h_pass->Sumw2();

  TFile* f = new TFile(inFile);
  TTree* t = (TTree*)(f->Get("JMETriggerNTuple/Events"));
  bool HLT_IsoMu24, HLT_IsoMu27, HLT_PFHT800, HLT_PFHT900, HLT_PFHT1050;
  vector<float> *offlineMuons_pt = new vector<float>();
  vector<float> *offlineMuons_eta = new vector<float>();
  vector<float> *offlineMuons_phi = new vector<float>();
  vector<float> *offlineMuons_id = new vector<float>();
  vector<float> *offlineMuons_pfIso = new vector<float>();
  vector<float> *offlineElectrons_pt = new vector<float>();
  vector<float> *offlineJetsAK04PFCHS_pt = new vector<float>();
  vector<float> *offlineJetsAK04PFCHS_eta = new vector<float>();
  vector<float> *offlineJetsAK04PFCHS_phi = new vector<float>();
  vector<float> *offlineJetsAK04PFCHS_pfid = new vector<float>();
  //for HLT_PFJet40
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet40 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet40 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet40 = new vector<bool>();
  bool Flag_HLT_PFJet40_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet40_HLTPathPrescaled;
  //for HLT_PFJet60
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet60 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet60 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet60 = new vector<bool>();
  bool Flag_HLT_PFJet60_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet60_HLTPathPrescaled;
  //for HLT_PFJet80
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet80 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet80 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet80 = new vector<bool>();
  bool Flag_HLT_PFJet80_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet80_HLTPathPrescaled;
  //for HLT_PFJet140
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet140 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet140 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet140 = new vector<bool>();
  bool Flag_HLT_PFJet140_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet140_HLTPathPrescaled;
  //for HLT_PFJet200
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet200 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet200 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet200 = new vector<bool>();
  bool Flag_HLT_PFJet200_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet200_HLTPathPrescaled;
  //for HLT_PFJet260
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet260 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet260 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet260 = new vector<bool>();
  bool Flag_HLT_PFJet260_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet260_HLTPathPrescaled;
  //for HLT_PFJet320
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet320 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet320 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet320 = new vector<bool>();
  bool Flag_HLT_PFJet320_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet320_HLTPathPrescaled;
  //for HLT_PFJet400
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet400 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet400 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet400 = new vector<bool>();
  bool Flag_HLT_PFJet400_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet400_HLTPathPrescaled;
  //for HLT_PFJet500
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet500 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet500 = new vector<bool>();
  vector<bool> *offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet500 = new vector<bool>();
  bool Flag_HLT_PFJet500_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFJet500_HLTPathPrescaled;
  //for HLT_PFHT1050
  bool Flag_HLT_PFHT1050_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFHT1050_HLTPathPrescaled;
  //for HLT_PFHT900
  bool Flag_HLT_PFHT900_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFHT900_HLTPathPrescaled;
  //for HLT_PFHT800
  bool Flag_HLT_PFHT800_L1TSeedPrescaledOrMasked;
  bool Flag_HLT_PFHT800_HLTPathPrescaled;

  t->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24);
  t->SetBranchAddress("HLT_IsoMu27",&HLT_IsoMu27);
  t->SetBranchAddress("HLT_PFHT800",&HLT_PFHT800);
  t->SetBranchAddress("HLT_PFHT900",&HLT_PFHT900);
  t->SetBranchAddress("HLT_PFHT1050",&HLT_PFHT1050);
  t->SetBranchAddress("offlineMuons_pt",&offlineMuons_pt);
  t->SetBranchAddress("offlineMuons_eta",&offlineMuons_eta);
  t->SetBranchAddress("offlineMuons_phi",&offlineMuons_phi);
  t->SetBranchAddress("offlineMuons_id",&offlineMuons_id);
  t->SetBranchAddress("offlineMuons_pfIso",&offlineMuons_pfIso);
  t->SetBranchAddress("offlineElectrons_pt",&offlineElectrons_pt);
  t->SetBranchAddress("offlineJetsAK04PFCHS_pt",&offlineJetsAK04PFCHS_pt);
  t->SetBranchAddress("offlineJetsAK04PFCHS_eta",&offlineJetsAK04PFCHS_eta);
  t->SetBranchAddress("offlineJetsAK04PFCHS_phi",&offlineJetsAK04PFCHS_phi);
  t->SetBranchAddress("offlineJetsAK04PFCHS_pfid",&offlineJetsAK04PFCHS_pfid);
  //for HLT_PFJet40
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet40",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet40);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet40",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet40);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet40",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet40);
  t->SetBranchAddress("Flag_HLT_PFJet40_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet40_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet40_HLTPathPrescaled",&Flag_HLT_PFJet40_HLTPathPrescaled);
  //for HLT_PFJet60
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet60",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet60);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet60",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet60);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet60",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet60);
  t->SetBranchAddress("Flag_HLT_PFJet60_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet60_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet60_HLTPathPrescaled",&Flag_HLT_PFJet60_HLTPathPrescaled);
  //for HLT_PFJet80
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet80",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet80);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet80",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet80);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet80",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet80);
  t->SetBranchAddress("Flag_HLT_PFJet80_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet80_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet80_HLTPathPrescaled",&Flag_HLT_PFJet80_HLTPathPrescaled);
  //for HLT_PFJet140
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet140",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet140);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet140",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet140);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet140",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet140);
  t->SetBranchAddress("Flag_HLT_PFJet140_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet140_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet140_HLTPathPrescaled",&Flag_HLT_PFJet140_HLTPathPrescaled);
  //for HLT_PFJet200
   t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet200",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet200);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet200",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet200);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet200",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet200);
  t->SetBranchAddress("Flag_HLT_PFJet200_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet200_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet200_HLTPathPrescaled",&Flag_HLT_PFJet200_HLTPathPrescaled);
  //for HLT_PFJet260
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet260",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet260);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet260",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet260);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet260",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet260);
  t->SetBranchAddress("Flag_HLT_PFJet260_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet260_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet260_HLTPathPrescaled",&Flag_HLT_PFJet260_HLTPathPrescaled);
  //for HLT_PFJet320
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet320",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet320);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet320",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet320);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet320",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet320);
  t->SetBranchAddress("Flag_HLT_PFJet320_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet320_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet320_HLTPathPrescaled",&Flag_HLT_PFJet320_HLTPathPrescaled);
  //for HLT_PFJet400
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet400",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet400);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet400",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet400);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet400",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet400);
  t->SetBranchAddress("Flag_HLT_PFJet400_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet400_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet400_HLTPathPrescaled",&Flag_HLT_PFJet400_HLTPathPrescaled);
  //for HLT_PFJet500
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet500",&offlineJetsAK04PFCHS_trigObjMatchL1TSeed_HLT_PFJet500);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet500",&offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet500);
  t->SetBranchAddress("offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet500",&offlineJetsAK04PFCHS_trigObjMatchHLTAllFilters_HLT_PFJet500);
  t->SetBranchAddress("Flag_HLT_PFJet500_L1TSeedPrescaledOrMasked",&Flag_HLT_PFJet500_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFJet500_HLTPathPrescaled",&Flag_HLT_PFJet500_HLTPathPrescaled);
  //for HLT_PFHT800
  t->SetBranchAddress("Flag_HLT_PFHT800_L1TSeedPrescaledOrMasked",&Flag_HLT_PFHT800_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFHT800_HLTPathPrescaled",&Flag_HLT_PFHT800_HLTPathPrescaled);
  //for HLT_PFHT900
  t->SetBranchAddress("Flag_HLT_PFHT900_L1TSeedPrescaledOrMasked",&Flag_HLT_PFHT900_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFHT900_HLTPathPrescaled",&Flag_HLT_PFHT900_HLTPathPrescaled);
  //for HLT_PFHT1050
  t->SetBranchAddress("Flag_HLT_PFHT1050_L1TSeedPrescaledOrMasked",&Flag_HLT_PFHT1050_L1TSeedPrescaledOrMasked);
  t->SetBranchAddress("Flag_HLT_PFHT1050_HLTPathPrescaled",&Flag_HLT_PFHT1050_HLTPathPrescaled);

  int n_events = t->GetEntries();

  bool flag_HLTPrescale;
  bool flag_L1Prescale;
  bool jet_trigger;
  vector<bool> *flag_trigObjMatch = new vector<bool>();

  for(int ie=0; ie<n_events; ie++){
    t->GetEntry(ie);

    if(path=="HLT_PFJet40"){
      flag_HLTPrescale = Flag_HLT_PFJet60_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet60_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet40;
    }

    if(path=="HLT_PFJet60"){
      flag_HLTPrescale = Flag_HLT_PFJet60_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet60_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet60;
    }

    if(path=="HLT_PFJet80"){
      flag_HLTPrescale = Flag_HLT_PFJet80_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet80_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet80;
    }

    if(path=="HLT_PFJet140"){
      flag_HLTPrescale = Flag_HLT_PFJet140_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet140_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet140;
    }

    if(path=="HLT_PFJet200"){
      flag_HLTPrescale = Flag_HLT_PFJet200_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet200_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet200;
    }

    if(path=="HLT_PFJet260"){
      flag_HLTPrescale = Flag_HLT_PFJet260_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet260_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet260;
    }

    if(path=="HLT_PFJet320"){
      flag_HLTPrescale = Flag_HLT_PFJet320_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet320_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet320;
    }

    if(path=="HLT_PFJet400"){
      flag_HLTPrescale = Flag_HLT_PFJet400_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet400_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet400;
    }

    if(path=="HLT_PFJet500"){
      flag_HLTPrescale = Flag_HLT_PFJet500_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFJet500_L1TSeedPrescaledOrMasked;
      flag_trigObjMatch = offlineJetsAK04PFCHS_trigObjMatchHLTLastFilter_HLT_PFJet500;
    }

    if(path=="HLT_PFHT800"){
      flag_HLTPrescale = Flag_HLT_PFHT800_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFHT800_L1TSeedPrescaledOrMasked;
      jet_trigger = HLT_PFHT800;
    }

    if(path=="HLT_PFHT900"){
      flag_HLTPrescale = Flag_HLT_PFHT900_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFHT900_L1TSeedPrescaledOrMasked;
      jet_trigger = HLT_PFHT900;
    }

    if(path=="HLT_PFHT1050"){
      flag_HLTPrescale = Flag_HLT_PFHT1050_HLTPathPrescaled;
      flag_L1Prescale = Flag_HLT_PFHT1050_L1TSeedPrescaledOrMasked;
      jet_trigger = HLT_PFHT1050;
    }
 
    if(flag_HLTPrescale || flag_L1Prescale) continue;

    if(!HLT_IsoMu27) continue;
     
    if(offlineMuons_pt->size() != 1 || offlineMuons_pt->at(0) < 30 || offlineElectrons_pt->size() != 0) continue;

    if(path=="HLT_PFHT800" || path=="HLT_PFHT900" || path=="HLT_PFHT1050"){
      double offlineHT = 0.;
      for(int i = 0; i < offlineJetsAK04PFCHS_pt->size(); i++){
        if(offlineJetsAK04PFCHS_pt->at(i) > 30 && abs(offlineJetsAK04PFCHS_eta->at(i)) < 2.5 && deltaR(offlineJetsAK04PFCHS_eta->at(i), offlineJetsAK04PFCHS_phi->at(i), offlineMuons_eta->at(0), offlineMuons_phi->at(0)) > 0.4 && offlineJetsAK04PFCHS_pfid->at(i) > 1) offlineHT += offlineJetsAK04PFCHS_pt->at(i);
      }
      h_all->Fill(offlineHT);
      if(jet_trigger) h_pass->Fill(offlineHT);
    }

    else{
      for(int i = 0; i < offlineJetsAK04PFCHS_pt->size(); i++){
        if(abs(offlineJetsAK04PFCHS_eta->at(i)) < 2.4 && deltaR(offlineJetsAK04PFCHS_eta->at(i), offlineJetsAK04PFCHS_phi->at(i), offlineMuons_eta->at(0), offlineMuons_phi->at(0)) > 0.4  && offlineJetsAK04PFCHS_pfid->at(i) > 1){ 
          h_all->Fill(offlineJetsAK04PFCHS_pt->at(i));
          if(flag_trigObjMatch->at(i)) h_pass->Fill(offlineJetsAK04PFCHS_pt->at(i));
        }
      }
    }
  }
  delete t;
  f->Close();
  delete f;

  TH1F* histogram_base = new TH1F("histogram_base", "", 50, 0., ETHIGH);
  histogram_base->SetTitle("Eff_for_"+TString(path));
  histogram_base->SetStats(false);
  histogram_base->SetMinimum(0.0);
  histogram_base->SetMaximum(1.2);
  histogram_base->GetYaxis()->SetTitle("Efficiency");
  histogram_base->GetYaxis()->SetTitleOffset(1.);
  histogram_base->GetXaxis()->SetTitleOffset(1.);
  if(path=="HLT_PFHT800" || path=="HLT_PFHT900" || path=="HLT_PFHT1050") histogram_base->GetXaxis()->SetTitle("HT [GeV]");
  else histogram_base->GetXaxis()->SetTitle("Jet p_{T} [GeV]");

  TEfficiency* pEff1 = 0;
  if(TEfficiency::CheckConsistency(*h_pass,*h_all)){
    pEff1 = new TEfficiency(*h_pass,*h_all);
    pEff1->SetLineWidth(2.);
    pEff1->SetLineColor(kBlack);
  }

  TFile out(outFile, "RECREATE");
  out.cd();
  histogram_base->Write();
  h_all->Write();
  h_pass->Write();
  pEff1->Write();
  out.Close();
}

int main(int argc, char *argv[])
{
  if(argc > 1)
    {
      calc_jet_eff(argv[1], argv[2], argv[3]);
    }
  return 0;
}
