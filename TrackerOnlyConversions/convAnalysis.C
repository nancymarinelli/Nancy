
#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TLegend.h>
#include <TCut.h>
#include <TGraph.h>
#include <TPaveText.h>
#include <TString.h>
#include <TLatex.h>
#else

#endif

////// H. Liu, N. Marinelli

typedef struct {
  int run, event;
  int lumi;
} EVT;

typedef struct { 
		int run, event;
		int isAssoc;
		int q1, q2;
		float pt1, phi1, theta1;
		float pt2, phi2, theta2;
		float pt, phi, theta, x, y, z;
		float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz;
		float r_pt1, r_chi21, r_d01, r_theta1, r_phi1;//its associated reco tk properties
		float r_pt2, r_chi22, r_d02, r_theta2, r_phi2;
		int r_algo1, r_hits1, r_missHits1, r_before1;
		int r_algo2, r_hits2, r_missHits2, r_before2;
		float r_minapp, r_chi2prob;
} SIMTORECO;

typedef struct {
		int run, event;
		int isAssoc;
		int q1, q2;
  int algo1, algo2;
  int nHits1, nHits2;
  //added by hlliu
  int missHits1, missHits2;//missed hits
  int npHits1, npHits2;//pixel hits
  int nsHits1, nsHits2;//strip stereo hits
  int beforeHits1, beforeHits2;//num of hits before vertex
  float pt1, iphi1, phi1, theta1, x1, y1, z1, chi21;
  float pt2, iphi2, phi2, theta2, x2, y2, z2, chi22;
  float ipx1, ipy1, ipz1;//momentum at vertex
  float ipx2, ipy2, ipz2;
  float pt, phi, theta, x, y, z, chi2, chi2prob;
  float vx, vy, vz;//primary vertex position
  float tx, ty, tz;//primary vertex position
  float bsx, bsy, bsz;
  float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz;
  float minapp;
  float d01, d02;//added by hlliu
  float cx, cy, cz;//xyz by track cross
  float mass;
} RECOTOSIM;

double map_2pi(double dphi){
  while (dphi<-3.1415926)
    dphi+=2*3.1415926;
  while (dphi>3.1415926)
    dphi-=2*3.1415926;
  return dphi;
}
float pairInvariantMass(float ipx1, float ipy1, float ipz1, float ipx2, float ipy2, float ipz2){
  const float mElec= 0.000511;
  float invMass=-99.;
  const float px = ipx1+ipx2;
  const float py = ipy1+ipy2;
  const float pz = ipz1+ipz2;
  const float mom1 = ipx1*ipx1+ipy1*ipy1+ipz1*ipz1;
  const float mom2 = ipx2*ipx2+ipy2*ipy2+ipz2*ipz2;
  const float e = sqrt( mom1+ mElec*mElec ) + sqrt( mom2 + mElec*mElec );
  invMass= ( e*e - px*px -py*py - pz*pz);
  if ( invMass>0.) invMass = sqrt(invMass);
  else 
    invMass = -1;
  return invMass;
}

float pairPt(float ipx1, float ipy1, float ipz1, float ipx2, float ipy2, float ipz2){
  float pt=-999999999999.;
  const float px = ipx1+ipx2;
  const float py = ipy1+ipy2;
  pt = sqrt (px*px + py*py);
  

  return pt;
}


void doIt(){
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  /*
    gStyle -> SetPalette(45);
    gStyle -> SetHistLineWidth(1);
    gStyle->SetTextFont(132);
    gStyle->SetTextSize(0.08);
    gStyle->SetLabelFont(132,"x");
    gStyle->SetLabelFont(132,"y");
    gStyle->SetTitleFont(132,"x");
    gStyle->SetTitleFont(132,"y");
    gStyle->SetLabelSize(0.05,"x");
    gStyle->SetLabelSize(0.05,"y");
    gStyle->SetTitleFont(132);
    gStyle->SetTitleSize(0.05,"x");
    gStyle->SetTitleSize(0.05,"y");
    //gStyle->SetOptStat(1110);
    gROOT->ForceStyle();
  */
  gROOT->cd();

  EVT evtbranch;

  SIMTORECO sim_;
  RECOTOSIM data_, mc_;

  bool by_event = false;//normalization by events or not?
  
  Int_t r1_use_events = 0, r2_use_events = 0;

  //TFile *_file0 = TFile::Open("/tmp/nancy/ntuple_conversion_minbias_357_rereco_V26A.root");
  //TFile *_file0 = TFile::Open("/tmp/nancy/newNtuples/ntuple_conversion_CMSSW356_minbias7TeV_2010-05-03.root");
  //  TFile *_file0 = TFile::Open("/tmp/nancy/newNtuples/ntuple_conversion_minbias7TeV_test_hit.root");
  //TFile *_file0 = TFile::Open("/tmp/nancy/newNtuples/ntuple_conversion_minbias7TeV_test.root");
  //TFile *_file0 = TFile::Open("/tmp/nancy/newNtuplesMay20/ntuple_conversion_CMSSW356_minbias7TeV_2010-05-10.root");
  //  TFile *_file0 = TFile::Open("/tmp/nancy/newNtuplesMay25/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-05-25.root");
  // TFile* _file0 = TFile::Open("/tmp/nancy/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04.root");


  TChain* evt1 = new TChain("ntupleEvt");
  evt1->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04_v1.root");
  evt1->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04_v2.root");
  TChain* s2r = new TChain("ntupleS2R");
  s2r->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04_v1.root");
  s2r->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04_v2.root");
  TChain* r2s = new TChain("ntupleR2S");
  r2s->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04_v1.root");
  r2s->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_minbias7TeV_2010-06-04_v2.root");


  if (by_event){
    // TTree *evt1 = (TTree *) gROOT->FindObject("ntupleEvt");
    r1_use_events = evt1->GetEntries();
    std::cout<<"Events Total in MC "<< evt1->GetEntries()<<std::endl;
  }
  //TTree *r2s = (TTree *) gROOT->FindObject("ntupleR2S");
  std::cout<<"Events on Sim "<< r2s->GetEntries()<<std::endl;
  Int_t r1_entries = r2s->GetEntries();
  //r1_entries=10000000;
  //TTree *s2r = (TTree *) gROOT->FindObject("ntupleS2R");
  std::cout<<"Events on Sim "<< s2r->GetEntries()<<std::endl;
  Int_t s1_entries = s2r->GetEntries();

  s2r->SetBranchAddress("run", &sim_.run);
  s2r->SetBranchAddress("event", &sim_.event);
  s2r->SetBranchAddress("isAssoc", &sim_.isAssoc);
  s2r->SetBranchAddress("q1", &sim_.q1);
  s2r->SetBranchAddress("q2", &sim_.q2);
  s2r->SetBranchAddress("pt1", &sim_.pt1);
  s2r->SetBranchAddress("phi1", &sim_.phi1);
  s2r->SetBranchAddress("theta1", &sim_.theta1);
  s2r->SetBranchAddress("pt2", &sim_.pt2);
  s2r->SetBranchAddress("phi2", &sim_.phi2);
  s2r->SetBranchAddress("theta2", &sim_.theta2);
  s2r->SetBranchAddress("pt", &sim_.pt);
  s2r->SetBranchAddress("phi", &sim_.phi);
  s2r->SetBranchAddress("theta", &sim_.theta);
  s2r->SetBranchAddress("x", &sim_.x);
  s2r->SetBranchAddress("y", &sim_.y);
  s2r->SetBranchAddress("z", &sim_.z);
  s2r->SetBranchAddress("deltapt", &sim_.deltapt);
  s2r->SetBranchAddress("deltaphi", &sim_.deltaphi);
  s2r->SetBranchAddress("deltatheta", &sim_.deltatheta);
  s2r->SetBranchAddress("deltax", &sim_.deltax);
  s2r->SetBranchAddress("deltay", &sim_.deltay);
  s2r->SetBranchAddress("deltaz", &sim_.deltaz);
  s2r->SetBranchAddress("r_pt1",&sim_.r_pt1);
  //s2r->SetBranchAddress("r_chi21",&sim_.r_chi21);
  s2r->SetBranchAddress("r_d01",&sim_.r_d01);
  s2r->SetBranchAddress("r_theta1",&sim_.r_theta1);
  s2r->SetBranchAddress("r_phi1",&sim_.r_phi1);
  s2r->SetBranchAddress("r_pt2",&sim_.r_pt2);
  //s2r->SetBranchAddress("r_chi22",&sim_.r_chi22);
  s2r->SetBranchAddress("r_d02",&sim_.r_d02);
  s2r->SetBranchAddress("r_theta2",&sim_.r_theta2);
  s2r->SetBranchAddress("r_phi2",&sim_.r_phi2);
  s2r->SetBranchAddress("r_algo1",&sim_.r_algo1);
  s2r->SetBranchAddress("r_hits1",&sim_.r_hits1);
  s2r->SetBranchAddress("r_missHits1",&sim_.r_missHits1);
  s2r->SetBranchAddress("r_before1",&sim_.r_before1);
  s2r->SetBranchAddress("r_algo2",&sim_.r_algo2);
  s2r->SetBranchAddress("r_hits2",&sim_.r_hits2);
  s2r->SetBranchAddress("r_missHits2",&sim_.r_missHits2);
  s2r->SetBranchAddress("r_before2",&sim_.r_before2);
  s2r->SetBranchAddress("r_minapp",&sim_.r_minapp);
  s2r->SetBranchAddress("r_chi2prob",&sim_.r_chi2prob);

  gROOT->cd();


  // TFile *_file1 = TFile::Open("/tmp/nancy/ntuple_conversion_VenturiMay12.root");
  // TFile *_file1 = TFile::Open("/tmp/nancy/newNtuples/ntuple_conversion_CMSSW356_goodcoll7TeV_2010-05-03.root");
  //  TFile *_file1 = TFile::Open("/tmp/nancy/newNtuples/ntuple_conversion_minbias7TeV_test_hit.root");
  //  TFile *_file1 = TFile::Open("/tmp/nancy/newNtuplesMay12/ntuple_conversion_CMSSW356_minbias7TeV_hit_2010-05-10.root");
  //TFile *_file1 = TFile::Open("/tmp/nancy/newNtuplesMay12/ntuple_conversion_CMSSW356_minbias7TeV_2010-05-10.root");
  //  TFile *_file1 = TFile::Open("/tmp/nancy/newNtuplesMay25/ntuple_conversion_CMSSW358p3_goodcoll7TeV_2010-05-25.root");
  //  TFile *_file1 = TFile::Open("/tmp/nancy/newNtuplesJune4/update/ntuple_conversion_CMSSW358p3_goodcoll7TeV_2010-06-04.root");
  

  TChain* r2s2 = new TChain("ntupleR2S");
  r2s2->Add("/data/ndpc0/b/nancy/datasets/newNtuplesJune4/ntuple_conversion_CMSSW358p3_goodcoll7TeV_2010-06-04.root");
  //  TTree *r2s2 = (TTree *) gROOT->FindObject("ntupleR2S");

  if (by_event){
    TTree *evt2 = (TTree *) gROOT->FindObject("ntupleEvt");
    evt2->SetBranchAddress("run", &evtbranch.run);
    evt2->SetBranchAddress("event", &evtbranch.event);
    evt2->SetBranchAddress("lumi", &evtbranch.lumi);

    Int_t data_entries = evt2->GetEntries();
    for (Int_t i = 0; i<data_entries; ++i){
      evt2->GetEntry(i);
      //TODO check the 7 TeV run numbers
      int run = evtbranch.run;
      bool run_quality = true ; 
      //= run==132440 || run==132471 || run==132474 || run==132476 || run==132477 || run==132478 || run==132479  ;
				
      //r2_use_events = evt2->GetEntries();
      if (run_quality)
	r2_use_events++;
    }
    std::cout<<"Events Total in data "<< r2_use_events <<std::endl;
  }

  Int_t r2_entries = r2s2->GetEntries();
  //TFile *_fileOut = TFile::Open("histosDataWithAssByHit.root","recreate");
  TFile *_fileOut = TFile::Open("histosAssByPos.root","recreate");

  r2s->SetBranchAddress("run", &mc_.run);
  r2s->SetBranchAddress("event", &mc_.event);
  r2s->SetBranchAddress("isAssoc", &mc_.isAssoc);
  r2s->SetBranchAddress("q1", &mc_.q1);
  r2s->SetBranchAddress("q2", &mc_.q2);
  r2s->SetBranchAddress("algo1", &mc_.algo1);
  r2s->SetBranchAddress("algo2", &mc_.algo2);
  r2s->SetBranchAddress("nHits1", &mc_.nHits1);
  r2s->SetBranchAddress("missHits1", &mc_.missHits1);
  r2s->SetBranchAddress("npHits1", &mc_.npHits1);
  r2s->SetBranchAddress("nsHits1", &mc_.nsHits1);
  r2s->SetBranchAddress("beforeHits1", &mc_.beforeHits1);
  r2s->SetBranchAddress("nHits2", &mc_.nHits2);
  r2s->SetBranchAddress("missHits2", &mc_.missHits2);
  r2s->SetBranchAddress("npHits2", &mc_.npHits2);
  r2s->SetBranchAddress("nsHits2", &mc_.nsHits2);
  r2s->SetBranchAddress("beforeHits2", &mc_.beforeHits2);
  r2s->SetBranchAddress("pt1", &mc_.pt1);
  r2s->SetBranchAddress("iphi1", &mc_.iphi1);
  r2s->SetBranchAddress("phi1", &mc_.phi1);
  r2s->SetBranchAddress("theta1", &mc_.theta1);
  r2s->SetBranchAddress("x1", &mc_.x1);
  r2s->SetBranchAddress("y1", &mc_.y1);
  r2s->SetBranchAddress("z1", &mc_.z1);
  r2s->SetBranchAddress("ipx1", &mc_.ipx1);
  r2s->SetBranchAddress("ipy1", &mc_.ipy1);
  r2s->SetBranchAddress("ipz1", &mc_.ipz1);
  r2s->SetBranchAddress("chi21", &mc_.chi21);
  r2s->SetBranchAddress("pt2", &mc_.pt2);
  r2s->SetBranchAddress("iphi2", &mc_.iphi2);
  r2s->SetBranchAddress("phi2", &mc_.phi2);
  r2s->SetBranchAddress("theta2", &mc_.theta2);
  r2s->SetBranchAddress("x2", &mc_.x2);
  r2s->SetBranchAddress("y2", &mc_.y2);
  r2s->SetBranchAddress("z2", &mc_.z2);
  r2s->SetBranchAddress("ipx2", &mc_.ipx2);
  r2s->SetBranchAddress("ipy2", &mc_.ipy2);
  r2s->SetBranchAddress("ipz2", &mc_.ipz2);
  r2s->SetBranchAddress("chi22", &mc_.chi22);
  r2s->SetBranchAddress("pt", &mc_.pt);
  r2s->SetBranchAddress("phi", &mc_.phi);
  r2s->SetBranchAddress("theta", &mc_.theta);
  r2s->SetBranchAddress("x", &mc_.x);
  r2s->SetBranchAddress("y", &mc_.y);
  r2s->SetBranchAddress("z", &mc_.z);
  r2s->SetBranchAddress("chi2", &mc_.chi2);
  r2s->SetBranchAddress("chi2prob", &mc_.chi2prob);
  r2s->SetBranchAddress("minapp", &mc_.minapp);
  r2s->SetBranchAddress("d01", &mc_.d01);
  r2s->SetBranchAddress("d02", &mc_.d02);
  r2s->SetBranchAddress("bsx", &mc_.bsx);
  r2s->SetBranchAddress("bsy", &mc_.bsy);
  r2s->SetBranchAddress("bsz", &mc_.bsz);
  r2s->SetBranchAddress("vx", &mc_.vx);
  r2s->SetBranchAddress("vy", &mc_.vy);
  r2s->SetBranchAddress("vz", &mc_.vz);
  r2s->SetBranchAddress("tx", &mc_.tx);
  r2s->SetBranchAddress("ty", &mc_.ty);
  r2s->SetBranchAddress("tz", &mc_.tz);
  r2s->SetBranchAddress("mass", &mc_.mass);
  r2s->SetBranchAddress("deltax", &mc_.deltax);
  r2s->SetBranchAddress("deltay", &mc_.deltay);
  r2s->SetBranchAddress("deltaz", &mc_.deltaz);


  r2s2->SetBranchAddress("run", &data_.run);
  r2s2->SetBranchAddress("event", &data_.event);
  r2s2->SetBranchAddress("isAssoc", &data_.isAssoc);
  r2s2->SetBranchAddress("q1", &data_.q1);
  r2s2->SetBranchAddress("q2", &data_.q2);
  r2s2->SetBranchAddress("algo1", &data_.algo1);
  r2s2->SetBranchAddress("algo2", &data_.algo2);
  r2s2->SetBranchAddress("nHits1", &data_.nHits1);
  r2s2->SetBranchAddress("missHits1", &data_.missHits1);
  r2s2->SetBranchAddress("npHits1", &data_.npHits1);
  r2s2->SetBranchAddress("nsHits1", &data_.nsHits1);
  r2s2->SetBranchAddress("beforeHits1", &data_.beforeHits1);
  r2s2->SetBranchAddress("nHits2", &data_.nHits2);
  r2s2->SetBranchAddress("missHits2", &data_.missHits2);
  r2s2->SetBranchAddress("npHits2", &data_.npHits2);
  r2s2->SetBranchAddress("nsHits2", &data_.nsHits2);
  r2s2->SetBranchAddress("beforeHits2", &data_.beforeHits2);
  r2s2->SetBranchAddress("pt1", &data_.pt1);
  r2s2->SetBranchAddress("iphi1", &data_.iphi1);
  r2s2->SetBranchAddress("phi1", &data_.phi1);
  r2s2->SetBranchAddress("theta1", &data_.theta1);
  r2s2->SetBranchAddress("x1", &data_.x1);
  r2s2->SetBranchAddress("y1", &data_.y1);
  r2s2->SetBranchAddress("z1", &data_.z1);
  r2s2->SetBranchAddress("ipx1", &data_.ipx1);
  r2s2->SetBranchAddress("ipy1", &data_.ipy1);
  r2s2->SetBranchAddress("ipz1", &data_.ipz1);
  r2s2->SetBranchAddress("chi21", &data_.chi21);
  r2s2->SetBranchAddress("pt2", &data_.pt2);
  r2s2->SetBranchAddress("iphi2", &data_.iphi2);
  r2s2->SetBranchAddress("phi2", &data_.phi2);
  r2s2->SetBranchAddress("theta2", &data_.theta2);
  r2s2->SetBranchAddress("x2", &data_.x2);
  r2s2->SetBranchAddress("y2", &data_.y2);
  r2s2->SetBranchAddress("z2", &data_.z2);
  r2s2->SetBranchAddress("ipx2", &data_.ipx2);
  r2s2->SetBranchAddress("ipy2", &data_.ipy2);
  r2s2->SetBranchAddress("ipz2", &data_.ipz2);
  r2s2->SetBranchAddress("chi22", &data_.chi22);
  r2s2->SetBranchAddress("pt", &data_.pt);
  r2s2->SetBranchAddress("phi", &data_.phi);
  r2s2->SetBranchAddress("theta", &data_.theta);
  r2s2->SetBranchAddress("x", &data_.x);
  r2s2->SetBranchAddress("y", &data_.y);
  r2s2->SetBranchAddress("z", &data_.z);
  r2s2->SetBranchAddress("chi2", &data_.chi2);
  r2s2->SetBranchAddress("chi2prob", &data_.chi2prob);
  r2s2->SetBranchAddress("minapp", &data_.minapp);
  r2s2->SetBranchAddress("d01", &data_.d01);
  r2s2->SetBranchAddress("d02", &data_.d02);
  r2s2->SetBranchAddress("bsx", &data_.bsx);
  r2s2->SetBranchAddress("bsy", &data_.bsy);
  r2s2->SetBranchAddress("bsz", &data_.bsz);
  r2s2->SetBranchAddress("vx", &data_.vx);
  r2s2->SetBranchAddress("vy", &data_.vy);
  r2s2->SetBranchAddress("vz", &data_.vz);
  r2s2->SetBranchAddress("tx", &data_.tx);
  r2s2->SetBranchAddress("ty", &data_.ty);
  r2s2->SetBranchAddress("tz", &data_.tz);
  r2s2->SetBranchAddress("mass", &data_.mass);



  TCanvas *c1 = new TCanvas("plot1", "plot1",430, 10, 600, 600);
  c1->SetBorderMode(0);
  //regular
  TCanvas *c2 = new TCanvas("plot2", "plot2",430, 10, 700, 450);
  c2->SetBorderMode(0);
  //log
  TCanvas *c3 = new TCanvas("plot3", "plot3",430, 10, 700, 450);
  c3->SetBorderMode(0);
  c3->SetLogy();

  TH1F *h_mc_photon_pt_ext = new TH1F("h_mc_photon_pt_ext", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_mc_photon_pt_fakes_ext = new TH1F("h_mc_photon_pt_fakes_ext", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_data_photon_pt_ext = new TH1F("h_data_photon_pt_ext", "CMS preliminary 2010", 100, 0, 25);

  TH1F *h_mc_photon_pt_recal = new TH1F("h_mc_photon_pt_recal", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_mc_photon_pt_fakes_recal = new TH1F("h_mc_photon_pt_fakes_recal", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_data_photon_pt_recal = new TH1F("h_data_photon_pt_recal", "CMS preliminary 2010", 100, 0, 25);


  TH1F *h_mc_photon_pt_ext_barrel = new TH1F("h_mc_photon_pt_ext_barrel", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_mc_photon_pt_fakes_ext_barrel = new TH1F("h_mc_photon_pt_fakes_ext_barrel", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_data_photon_pt_ext_barrel = new TH1F("h_data_photon_pt_ext_barrel", "CMS preliminary 2010", 100, 0, 25);


  TH1F *h_mc_photon_pt_ext_endcap = new TH1F("h_mc_photon_pt_ext_endcap", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_mc_photon_pt_fakes_ext_endcap = new TH1F("h_mc_photon_pt_fakes_ext_endcap", "CMS preliminary 2010", 100, 0, 25);
  TH1F *h_data_photon_pt_ext_endcap = new TH1F("h_data_photon_pt_ext_endcap", "CMS preliminary 2010", 100, 0, 25);



  TH1F *h_mc_photon_phi = new TH1F("h_mc_photon_phi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_phi = new TH1F("h_mc_photon_fakes_phi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_phi = new TH1F("h_data_photon_phi", "CMS preliminary 2010", 80, -3.5, 3.5);

  TH1F *h_mc_photon_phi_ZLT26_RLT19 = new TH1F("h_mc_photon_phi_ZLT26_RLT19", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_phi_ZLT26_RLT19 = new TH1F("h_mc_photon_fakes_phi_ZLT26_RLT19", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_phi_ZLT26_RLT19 = new TH1F("h_data_photon_phi_ZLT26_RLT19", "CMS preliminary 2010", 80, -3.5, 3.5);

  TH1F *h_mc_photon_phi_ZLT26_28_R_30 = new TH1F("h_mc_photon_phi_ZLT26_28_R_30", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_phi_ZLT26_28_R_30 = new TH1F("h_mc_photon_fakes_phi_ZLT26_28_R_30", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_phi_ZLT26_28_R_30 = new TH1F("h_data_photon_phi_ZLT26_28_R_30", "CMS preliminary 2010", 80, -3.5, 3.5);


  TH1F *h_mc_photon_phi_posZLT73_27_R_35 = new TH1F("h_mc_photon_phi_posZLT73_27_R_35", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_phi_posZLT73_27_R_35  = new TH1F("h_mc_photon_fakes_phi_posZLT73_27_R_35", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_phi_posZLT73_27_R_35  = new TH1F("h_data_photon_phi_posZLT73_27_R_35", "CMS preliminary 2010", 80, -3.5, 3.5);

  TH1F *h_mc_photon_phi_negZLT73_27_R_35 = new TH1F("h_mc_photon_phi_negZLT73_27_R_35", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_phi_negZLT73_27_R_35  = new TH1F("h_mc_photon_fakes_phi_negZLT73_27_R_35", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_phi_negZLT73_27_R_35  = new TH1F("h_data_photon_phi_negZLT73_27_R_35", "CMS preliminary 2010", 80, -3.5, 3.5);



  TH1F *h_mc_photon_phi_ZLT73_RGT22 = new TH1F("h_mc_photon_phi_ZLT73_RGT22", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_phi_ZLT73_RGT22 = new TH1F("h_mc_photon_fakes_phi_ZLT73_RGT22", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_phi_ZLT73_RGT22 = new TH1F("h_data_photon_phi_ZLT73_RGT22", "CMS preliminary 2010", 80, -3.5, 3.5);


  TH1F *h_mc_photon_iphi = new TH1F("h_mc_photon_iphi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_iphi = new TH1F("h_mc_photon_fakes_iphi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_iphi = new TH1F("h_data_photon_iphi", "CMS preliminary 2010", 80, -3.5, 3.5);


  TH1F *h_mc_photon_chi2prob = new TH1F("h_mc_photon_chi2prob", "CMS preliminary 2010", 100, 0., 1.);
  TH1F *h_mc_photon_fakes_chi2prob = new TH1F("h_mc_photon_fakes_chi2prob", "CMS preliminary 2010", 100,0.,1.);
  TH1F *h_data_photon_chi2prob = new TH1F("h_data_photon_chi2prob", "CMS preliminary 2010", 100, 0., 1.);

  TH1F *h_mc_photon_chi2prob_zoom = new TH1F("h_mc_photon_chi2prob_zoom", "CMS preliminary 2010", 100, 0., 0.1);
  TH1F *h_mc_photon_fakes_chi2prob_zoom = new TH1F("h_mc_photon_fakes_chi2prob_zoom", "CMS preliminary 2010", 100,0.,0.1);
  TH1F *h_data_photon_chi2prob_zoom = new TH1F("h_data_photon_chi2prob_zoom", "CMS preliminary 2010", 100, 0.,0.1);



  TH1F *h_mc_photon_chi2prob_beforeCut = new TH1F("h_mc_photon_chi2prob_beforeCut", "CMS preliminary 2010", 100, 0., 1.);
  TH1F *h_mc_photon_fakes_chi2prob_beforeCut = new TH1F("h_mc_photon_fakes_chi2prob_beforeCut", "CMS preliminary 2010", 100,0.,1.);
  TH1F *h_data_photon_chi2prob_beforeCut = new TH1F("h_data_photon_chi2prob_beforeCut", "CMS preliminary 2010", 100, 0., 1.);



  TH1F *h_mc_photon_z_phi = new TH1F("h_mc_photon_z_phi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_z_phi = new TH1F("h_mc_photon_fakes_z_phi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_z_phi = new TH1F("h_data_photon_z_phi", "CMS preliminary 2010", 80, -3.5, 3.5);

  TH1F *h_mc_photon_z_iphi = new TH1F("h_mc_photon_z_iphi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_mc_photon_fakes_z_iphi = new TH1F("h_mc_photon_fakes_z_iphi", "CMS preliminary 2010", 80, -3.5, 3.5);
  TH1F *h_data_photon_z_iphi = new TH1F("h_data_photon_z_iphi", "CMS preliminary 2010", 80, -3.5, 3.5);


  TH1F *h_mc_photon_eta = new TH1F("h_mc_photon_eta", "CMS preliminary 2010", 100, -3., 3.);
  TH1F *h_mc_photon_fakes_eta = new TH1F("h_mc_photon_fakes_eta", "CMS preliminary 2010", 100, -3., 3.);
  TH1F *h_data_photon_eta = new TH1F("h_data_photon_eta", "CMS preliminary 2010", 100, -3., 3.);

  //invariant mass from inner momentum
  TH1F *h_mc_photon_mass = new TH1F("h_mc_photon_mass", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_mc_photon_fakes_mass = new TH1F("h_mc_photon_fakes_mass", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_data_photon_mass = new TH1F("h_data_photon_mass", "CMS preliminary 2010", 100, 0., 0.25);

  //invariant mass from momentum at vtx
  TH1F *h_mc_photon_mass2 = new TH1F("h_mc_photon_mass2", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_mc_photon_fakes_mass2 = new TH1F("h_mc_photon_fakes_mass2", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_mc_photon_fakesGT02_mass2 = new TH1F("h_mc_photon_fakesGT02_mass2", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_data_photon_mass2 = new TH1F("h_data_photon_mass2", "CMS preliminary 2010", 100, 0., 0.25);

  TH1F *h_mc_photon_mass2_barrel = new TH1F("h_mc_photon_mass2_barrel", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_mc_photon_fakes_mass2_barrel = new TH1F("h_mc_photon_fakes_mass2_barrel", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_mc_photon_fakesGT02_mass2_barrel = new TH1F("h_mc_photon_fakesGT02_mass2_barrel", "CMS preliminary 2010", 100, 0., 0.25);
  TH1F *h_data_photon_mass2_barrel = new TH1F("h_data_photon_mass2_barrel", "CMS preliminary 2010", 100, 0., 0.25);


  TH2F *h_mc_photon_mass2_vs_r = new TH2F("h_mc_photon_mass2_vs_r", "CMS preliminary 2010", 300, 0, 60,100, 0., 0.25);
  TH2F *h_mc_photon_fakes_mass2_vs_r = new TH2F("h_mc_photon_fakes_mass2_vs_r", "CMS preliminary 2010", 300, 0, 60, 100, 0., 0.25);
  TH2F *h_mc_photon_fakesGT02_mass2_vs_r = new TH2F("h_mc_photon_fakesGT02_mass2_vs_r", "CMS preliminary 2010",  300, 0, 60,100, 0., 0.25);
  TH2F *h_data_photon_mass2_vs_r = new TH2F("h_data_photon_mass2_vs_r", "CMS preliminary 2010",  300, 0, 60,100, 0., 0.25);


  TH1F *h_mc_photon_eta_s = new TH1F("h_mc_photon_eta_s", "CMS preliminary 2010", 100, -3., 3.);
  TH1F *h_data_photon_eta_s = new TH1F("h_data_photon_eta_s", "CMS preliminary 2010", 100, -3., 3.);

  TH1F *h_mc_photon_r = new TH1F("h_mc_photon_r", "CMS preliminary 2010", 100, 0, 60);
  TH1F *h_data_photon_r = new TH1F("h_data_photon_r", "CMS preliminary 2010", 100, 0, 60);

  TH1F *h_mc_photon_r_pixel = new TH1F("h_mc_photon_r_pixel", "CMS preliminary 2010", 100, 0, 20);
  TH1F *h_data_photon_r_pixel = new TH1F("h_data_photon_r_pixel", "CMS preliminary 2010", 100, 0, 20);

  TH1F *h_mc_photon_vr_pixel = new TH1F("h_mc_photon_vr_pixel", "CMS preliminary 2010", 100, 0, 20);
  TH1F *h_data_photon_vr_pixel = new TH1F("h_data_photon_vr_pixel", "CMS preliminary 2010", 100, 0, 20);
  TH1F *h_mc_photon_r_pixel_s = new TH1F("h_mc_photon_r_pixel_s", "CMS preliminary 2010", 100, 0, 12);
  TH1F *h_data_photon_r_pixel_s = new TH1F("h_data_photon_r_pixel_s", "CMS preliminary 2010", 100, 0, 12);

  TH1F *h_mc_tk_hits = new TH1F("h_mc_tk_hits", "CMS preliminary 2010", 30, 0, 30);
  TH1F *h_mc_tk_hits_fakes = new TH1F("h_mc_tk_hits_fakes", "CMS preliminary 2010", 30, 0, 30);
  TH1F *h_data_tk_hits = new TH1F("h_data_tk_hits", "CMS preliminary 2010", 30, 0, 30);

  TH1F *h_mc_tk_charge = new TH1F("h_mc_tk_charge", "CMS preliminary 2010", 3, -1, 1.);
  TH1F *h_mc_tk_charge_fakes = new TH1F("h_mc_tk_charge_fakes", "CMS preliminary 2010", 3, -1., 1.);
  TH1F *h_data_tk_charge = new TH1F("h_data_tk_charge", "CMS preliminary 2010", 3, -1., 1.);


  TH1F *h_mc_tk_chi2 = new TH1F("h_mc_tk_chi2", "CMS preliminary 2010", 50, 0, 10);
  TH1F *h_mc_tk_chi2_fakes = new TH1F("h_mc_tk_chi2_fakes", "CMS preliminary 2010", 50, 0, 10);
  TH1F *h_data_tk_chi2 = new TH1F("h_data_tk_chi2", "CMS preliminary 2010", 50, 0, 10);

  TH1F *h_mc_tk_pt = new TH1F("h_mc_tk_pt", "CMS preliminary 2010", 100, 0, 10);
  TH1F *h_mc_tk_pt_fakes = new TH1F("h_mc_tk_pt_fakes", "CMS preliminary 2010", 100, 0, 10);
  TH1F *h_mc_tk_pt_fakesGT02 = new TH1F("h_mc_tk_pt_fakesGT02", "CMS preliminary 2010", 100, 0, 10);
  TH1F *h_data_tk_pt = new TH1F("h_data_tk_pt", "CMS preliminary 2010", 100, 0, 10);

  TH1F *h_mc_tk_pt_barrel = new TH1F("h_mc_tk_pt_barrel", "CMS preliminary 2010", 100, 0, 10);
  TH1F *h_mc_tk_pt_fakes_barrel = new TH1F("h_mc_tk_pt_fakes_barrel", "CMS preliminary 2010", 100, 0, 10);
  TH1F *h_data_tk_pt_barrel = new TH1F("h_data_tk_pt_barrel", "CMS preliminary 2010", 100, 0, 10);


  TH1F *h_mc_tk_pt1 = new TH1F("h_mc_tk_pt1", "CMS preliminary 2010", 100, 0, 2.);
  TH1F *h_mc_tk_pt1_fakes = new TH1F("h_mc_tk_pt1_fakes", "CMS preliminary 2010", 100, 0, 2.);
  TH1F *h_mc_tk_pt1_fakesGT02 = new TH1F("h_mc_tk_pt1_fakesGT02", "CMS preliminary 2010", 100, 0, 2);
  TH1F *h_data_tk_pt1 = new TH1F("h_data_tk_pt1", "CMS preliminary 2010", 100, 0, 2.);

  TH1F *h_mc_tk_pt2 = new TH1F("h_mc_tk_pt2", "CMS preliminary 2010", 100, 0, 2.);
  TH1F *h_mc_tk_pt2_fakes = new TH1F("h_mc_tk_pt2_fakes", "CMS preliminary 2010", 100, 0, 2.);
  TH1F *h_mc_tk_pt2_fakesGT02 = new TH1F("h_mc_tk_pt2_fakesGT02", "CMS preliminary 2010", 100, 0, 2); 
  TH1F *h_data_tk_pt2 = new TH1F("h_data_tk_pt2", "CMS preliminary 2010", 100, 0, 2.);

  TH1F *h_mc_tk_pt3 = new TH1F("h_mc_tk_pt3", "CMS preliminary 2010", 100, 0, 5.);
  TH1F *h_mc_tk_pt3_fakes = new TH1F("h_mc_tk_pt3_fakes", "CMS preliminary 2010", 100, 0, 5.);
  TH1F *h_mc_tk_pt3_fakesGT02 = new TH1F("h_mc_tk_pt3_fakesGT02", "CMS preliminary 2010", 100, 0, 5.); 
  TH1F *h_data_tk_pt3 = new TH1F("h_data_tk_pt3", "CMS preliminary 2010", 100, 0, 5.);

  TH2F *h_mcTrue_eta_vs_r = new TH2F ("h_mcTrue_eta_vs_r","Conversion MC truth eta vs r ",  200, 0., 60., 100, -3., 3.);

  TH2F *h_mcTrue_tk1_vs_tk2_l1 = new TH2F ("h_mcTrue_tk1_vs_tk2_l1","Conversion MC truth tk1 vs tk2 pxl1 ",  100, 0., 2., 100, 0., 2.);
  TH2F *h_mcTrue_tk1_vs_tk2_l2 = new TH2F ("h_mcTrue_tk1_vs_tk2_l2","Conversion MC truth tk1 vs tk2 pxl2 ",  100, 0., 2., 100, 0., 2.);
  TH2F *h_mcTrue_tk1_vs_tk2_l3 = new TH2F ("h_mcTrue_tk1_vs_tk2_l3","Conversion MC truth tk1 vs tk2 pxl3 ",  100, 0., 2., 100, 0., 2.);

  TH2F *h_mcTrue_tkMinPt_vs_r = new TH2F ("h_mcTrue_tkMinPt_vs_r","Conversion MC truth min pt track vs r  ",  200, 0., 60., 100, 0., 5.);
  TH2F *h_mcTrue_tkMaxPt_vs_r = new TH2F ("h_mcTrue_tkMaxPt_vs_r","Conversion MC truth max pt track vs r  ",  200, 0., 60., 100, 0., 5.);


  TH2F *h2_data_tk_pt_l1 = new TH2F("h2_data_tk_pt_l1", " Data pt1 vs pt2 PXL1", 100, 0, 2., 100, 0., 2. );
  TH2F *h2_data_tk_pt_l2 = new TH2F("h2_data_tk_pt_l2", " Data pt1 vs pt2 PXL2", 100, 0, 2., 100, 0., 2. );
  TH2F *h2_data_tk_pt_l3 = new TH2F("h2_data_tk_pt_l3", " Data pt1 vs pt2 PXL3", 100, 0, 2., 100, 0., 2. );

  TH2F *h_mcReco_tkMinPt_vs_r = new TH2F ("h_mcReco_tkMinPt_vs_r","Conversion MC reco tk min pt vs r  ",  200, 0., 60., 100, 0., 2.);
  TH2F *h_mcReco_tkMaxPt_vs_r = new TH2F ("h_mcReco_tkMaxPt_vs_r","Conversion MC reco tk max pt vs r  ",  200, 0., 60., 100, 0., 2.);

  TH1F *h_data_d0 = new TH1F("h_data_d0", "CMS preliminary 2010", 100, -0.01, 1.5); 
  TH1F *h_mc_d0 = new TH1F("h_mc_d0", "CMS preliminary 2010", 100, -0.01, 1.5); 
  TH1F *h_mc_fakes_d0 = new TH1F("h_mc_fakes_d0", "CMS preliminary 2010", 100, -0.01, 1.5); 

  TH1F *h_data_d0_ext = new TH1F("h_data_d0_ext", "CMS preliminary 2010", 200, -0.01, 60); 
  TH1F *h_mc_d0_ext = new TH1F("h_mc_d0_ext", "CMS preliminary 2010", 200, -0.01, 60); 
  TH1F *h_mc_fakes_d0_ext = new TH1F("h_mc_fakes_d0_ext", "CMS preliminary 2010", 200, -0.01, 60); 



  TH1F *h_mc_tk_algo = new TH1F("h_mc_tk_algo", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakes = new TH1F("h_mc_tk_algo_fakes", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakesGT02 = new TH1F("h_mc_tk_algo_fakesGT02", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_data_tk_algo = new TH1F("h_data_tk_algo", "CMS preliminary 2010", 8, 3.5, 11.5); 

  TH1F *h_mc_tk_algo_l1 = new TH1F("h_mc_tk_algo_l1", " ", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakes_l1 = new TH1F("h_mc_tk_algo_fakes_l1", " ", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakesGT02_l1 = new TH1F("h_mc_tk_algo_fakesGT02_l1", " ", 8, 3.5, 11.5);
  TH1F *h_data_tk_algo_l1 = new TH1F("h_data_tk_algo_l1", " ", 8, 3.5, 11.5); 

  TH1F *h_mc_tk_algo_l2 = new TH1F("h_mc_tk_algo_l2", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakes_l2 = new TH1F("h_mc_tk_algo_fakes_l2", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakesGT02_l2 = new TH1F("h_mc_tk_algo_fakesGT02_l2", " ", 8, 3.5, 11.5);
  TH1F *h_data_tk_algo_l2 = new TH1F("h_data_tk_algo_l2", "CMS preliminary 2010", 8, 3.5, 11.5); 

  TH1F *h_mc_tk_algo_l3 = new TH1F("h_mc_tk_algo_l3", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakes_l3 = new TH1F("h_mc_tk_algo_fakes_l3", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakesGT02_l3 = new TH1F("h_mc_tk_algo_fakesGT02_l3", " ", 8, 3.5, 11.5);
  TH1F *h_data_tk_algo_l3 = new TH1F("h_data_tk_algo_l3", "CMS preliminary 2010", 8, 3.5, 11.5); 

  TH1F *h_mc_photon_br = new TH1F("h_mc_photon_br", "CMS preliminary 2010", 100, 0, 60);
  TH1F *h_data_photon_br = new TH1F("h_data_photon_br", "CMS preliminary 2010", 100, 0, 60);


  TH1F *h_mc_photon_br_eta_pixel = new TH1F("h_mc_photon_br_eta_pixel", "CMS preliminary 2010", 300, 0, 60);
  TH1F *h_mc_photon_br_eta_fakes_pixel = new TH1F("h_mc_photon_br_eta_fakes_pixel", "CMS preliminary 2010",300, 0, 60);
  TH1F *h_data_photon_br_eta_pixel = new TH1F("h_data_photon_br_eta_pixel", "CMS preliminary 2010", 300, 0,60);
  TH1F *h_data_photon_br_eta_pixel_beampipe = new TH1F("h_data_photon_br_eta_pixel_beampipe", "CMS preliminary 2010", 300, 0, 60);


  TH1F *h_mc_photon_br_eta_barrel = new TH1F("h_mc_photon_br_eta_barrel", "CMS preliminary 2010", 300, 0, 60);
  TH1F *h_mc_photon_br_eta_fakes_barrel = new TH1F("h_mc_photon_br_eta_fakes_barrel", "CMS preliminary 2010",300, 0, 60);
  TH1F *h_data_photon_br_eta_barrel = new TH1F("h_data_photon_br_eta_barrel", "CMS preliminary 2010", 300, 0,60);
  TH1F *h_data_photon_br_eta_barrel_beampipe = new TH1F("h_data_photon_br_eta_barrel_beampipe", "CMS preliminary 2010", 300, 0, 60);


  TH1F *h_mc_photon_br_etaz_pixel = new TH1F("h_mc_photon_br_etaz_pixel", "CMS preliminary 2010", 100, 0, 20);
  TH1F *h_mc_photon_br_etaz_fakes_pixel = new TH1F("h_mc_photon_br_etaz_fakes_pixel", "CMS preliminary 2010", 100, 0, 20);
  TH1F *h_data_photon_br_etaz_pixel = new TH1F("h_data_photon_br_etaz_pixel", "CMS preliminary 2010", 100, 0, 20);
  TH1F *h_data_photon_bpr_etaz_pixel = new TH1F("h_data_photon_bpr_etaz_pixel", "CMS preliminary 2010", 100, 0, 20);


  TH1F *h_mc_photon_br_z_pixel = new TH1F("h_mc_photon_br_z_pixel", "CMS preliminary 2010", 60, 0, 12);
  TH1F *h_mc_photon_br_z_fakes_pixel = new TH1F("h_mc_photon_br_z_fakes_pixel", "CMS preliminary 2010", 60, 0, 12);
  TH1F *h_data_photon_br_z_pixel = new TH1F("h_data_photon_br_z_pixel", "CMS preliminary 2010", 60, 0, 12);//detector center
  TH1F *h_data_photon_bpr_z_pixel = new TH1F("h_data_photon_bpr_z_pixel", "CMS preliminary 2010", 60, 0, 12);//pixel center
  TH1F *h_data_photon_br_z_pixel_beampipe = new TH1F("h_data_photon_br_z_pixel_beampipe", "CMS preliminary 2010", 60, 0, 12);//detector center


  TH1F *h_mc_photon_br_z_barrel = new TH1F("h_mc_photon_br_z_barrel", "CMS preliminary 2010", 300, 0, 60);
  TH1F *h_mc_photon_br_z_fakes_barrel = new TH1F("h_mc_photon_br_z_fakes_barrel", "CMS preliminary 2010", 300, 0, 60);
  TH1F *h_data_photon_br_z_barrel = new TH1F("h_data_photon_br_z_barrel", "CMS preliminary 2010", 300, 0, 60);

  TH1F *h_mc_photon_br_z_barrel2 = new TH1F("h_mc_photon_br_z_barrel2", "CMS preliminary 2010", 300, 0, 60);
  TH1F *h_mc_photon_br_z_fakes_barrel2 = new TH1F("h_mc_photon_br_z_fakes_barrel2", "CMS preliminary 2010", 300, 0, 60);
  TH1F *h_data_photon_br_z_barrel2 = new TH1F("h_data_photon_br_z_barrel2", "CMS preliminary 2010", 300, 0, 60);



  TH1F *h_mc_photon_br_z_pixel_rebin = new TH1F("h_mc_photon_br_z_pixel_rebin", "CMS preliminary 2010", 120, 0, 60);
  TH1F *h_mc_photon_br_z_fakes_pixel_rebin = new TH1F("h_mc_photon_br_z_fakes_pixel_rebin", "CMS preliminary 2010", 120, 0, 60);
  TH1F *h_data_photon_br_z_pixel_rebin = new TH1F("h_data_photon_br_z_pixel_rebin", "CMS preliminary 2010", 120, 0, 60);//pixel center


  TH1F *h_mc_photon_crossR = new TH1F("h_mc_photon_crossR", "CMS preliminary 2010", 60, 0, 12);
  TH1F *h_mc_photon_crossR_fakes = new TH1F("h_mc_photon_crossR_fakes", "CMS preliminary 2010", 60, 0, 12);
  TH1F *h_data_photon_crossR = new TH1F("h_data_photon_crossR", "CMS preliminary 2010", 60, 0, 12);//detector center
  
  TH1F *h_mc_photon_z_pixel = new TH1F("h_mc_photon_z_pixel", "CMS preliminary 2010", 180, -90, 90);
  TH1F *h_mc_photon_z_pixel_fakes = new TH1F("h_mc_photon_z_pixel_fakes", "CMS preliminary 2010", 180, -90, 90);
  TH1F *h_data_photon_z_pixel = new TH1F("h_data_photon_z_pixel", "CMS preliminary 2010", 180, -90, 90);

  TH1F *h_mc_photon_z = new TH1F("h_mc_photon_z", "CMS preliminary 2010", 320, -160, 160);
  TH1F *h_mc_photon_z_fakes = new TH1F("h_mc_photon_z_fakes", "CMS preliminary 2010", 320, -160, 160);
  TH1F *h_data_photon_z = new TH1F("h_data_photon_z", "CMS preliminary 2010", 320, -160, 160);

  TH1F *h_mc_photon_z_ZGT124 = new TH1F("h_mc_photon_z_ZGT124", "CMS preliminary 2010", 160, 120, 280);
  TH1F *h_mc_photon_z_ZGT124_fakes = new TH1F("h_mc_photon_z__ZGT124_fakes", "CMS preliminary 2010", 160, 120, 280);
  TH1F *h_data_photon_z_ZGT124 = new TH1F("h_data_photon_z_ZGT124", "CMS preliminary 2010", 160, 120, 280);


  TH1F *h_mc_photon_z_flange = new TH1F("h_mc_photon_z_flange", "CMS preliminary 2010", 180, -90, 90);
  TH1F *h_mc_photon_z_flange_fakes = new TH1F("h_mc_photon_z_flange_fakes", "CMS preliminary 2010", 180, -90, 90);
  TH1F *h_data_photon_z_flange = new TH1F("h_data_photon_z_flange", "CMS preliminary 2010", 180, -90, 90);




  TH1F *h_mc_photon_dz = new TH1F("h_mc_photon_dz", "CMS preliminary 2010", 100, -5.5, 5.5);
  TH1F *h_data_photon_dz = new TH1F("h_data_photon_dz", "CMS preliminary 2010", 100, -5.5, 5.5);

  TH1F *h_mc_photon_dz_s = new TH1F("h_mc_photon_dz_s", "CMS preliminary 2010", 100, -5.5, 5.5);
  TH1F *h_mc_photon_dz_fakes_s = new TH1F("h_mc_photon_dz_fakes_s", "CMS preliminary 2010", 100, -5.5, 5.5);
  TH1F *h_data_photon_dz_s = new TH1F("h_data_photon_dz_s", "CMS preliminary 2010", 100, -5.5, 5.5);

  TH1F *h_mc_photon_dcot = new TH1F("h_mc_photon_dcot", "CMS preliminary 2010", 100, -0.12, 0.12);
  TH1F *h_mc_photon_fakes_dcot = new TH1F("h_mc_photon_fakes_dcot", "CMS preliminary 2010", 100, -0.12, 0.12);
  TH1F *h_data_photon_dcot = new TH1F("h_data_photon_dcot", "CMS preliminary 2010", 100, -0.12, 0.12);

  TH1F *h_mc_photon_minapp = new TH1F("h_mc_photon_minapp", "CMS preliminary 2010", 100, -0.3, 1.0);
  TH1F *h_mc_photon_fakes_minapp = new TH1F("h_mc_photon_fakes_minapp", "CMS preliminary 2010", 100, -0.3, 1.0);
  TH1F *h_data_photon_minapp = new TH1F("h_data_photon_minapp", "CMS preliminary 2010", 100, -0.3, 1.0);

  TH1F *h_mc_photon_dphi = new TH1F("h_mc_photon_dphi", "CMS preliminary 2010", 100, -0.5, 0.5);
  TH1F *h_mc_photon_fakes_dphi = new TH1F("h_mc_photon_fakes_dphi", "CMS preliminary 2010", 100, -0.5, 0.5);
  TH1F *h_data_photon_dphi = new TH1F("h_data_photon_dphi", "CMS preliminary 2010", 100, -0.5, 0.5);


  TH1F *h_fakeRate_r_d = new TH1F("h_fakeRate_r_d", "FakeRate vs R in barrel", 100, 0, 60.);
  TH1F *h_fakeRate_r_n = new TH1F("h_fakeRate_r_n", "FakeRate vs R in barrel", 100, 0, 60.);

  TH1F *h_fakeRate_eta_d = new TH1F("h_fakeRate_eta_d", "FakeRate vs Eta", 100,-2.5, 2.5); 
  TH1F *h_fakeRate_eta_n = new TH1F("h_fakeRate_eta_n", "FakeRate vs Eta", 100,-2.5, 2.5); 

  TH1F *h_fakeRate_phi_d = new TH1F("h_fakeRate_phi_d", "FakeRate vs #phi", 100,-3.2, 3.2); 
  TH1F *h_fakeRate_phi_n = new TH1F("h_fakeRate_phi_n", "FakeRate vs #phi", 100,-3.2, 3.2); 

  TH1F *h_fakeRate_pt_d = new TH1F("h_fakeRate_pt_d", "FakeRate vs pt", 100,0.,25.);
  TH1F *h_fakeRate_pt_n = new TH1F("h_fakeRate_pt_n", "FakeRate vs pt", 100,0.,25.); 

  TH1F *h_eff_r_d = new TH1F("h_eff_r_d", "Efficiency vs r", 100, 0., 60.);
  TH1F *h_eff_r_n = new TH1F("h_eff_r_n", "Efficiency vs r", 100, 0., 60.);
  TH1F *h_eff_pt_d = new TH1F("h_eff_pt_d", "Efficiency vs pt", 100, 0.,25.);
  TH1F *h_eff_pt_n = new TH1F("h_eff_pt_n", "Efficiency vs pt", 100, 0.,25.);
  TH1F *h_eff_eta_d = new TH1F("h_eff_eta_d", "Efficiency vs Eta", 100, -2.5, 2.5);
  TH1F *h_eff_eta_n = new TH1F("h_eff_eta_n", "Efficiency vs Eta", 100, -2.5, 2.5);
  TH1F *h_eff_phi_d = new TH1F("h_eff_phi_d", "Efficiency vs #phi", 100,-3.2, 3.2); 
  TH1F *h_eff_phi_n = new TH1F("h_eff_phi_n", "Efficiency vs #phi", 100,-3.2, 3.2); 


  TH1F *h_eff_tkPtMin_d = new TH1F("h_eff_tkPtMin_d", "Efficiency vs min pt track", 100, 0., 5.);
  TH1F *h_eff_tkPtMin_n = new TH1F("h_eff_tkPtMin_n", "Efficiency vs min pt track", 100, 0., 5.);


  TH2F* h2_mc_RvsZ =new TH2F("h2_mc_RvsZ", "Trk Only Conv: R vs Z " , 1000, -200., 200., 1000, 0., 60);
  TH2F* h2_data_RvsZ =new TH2F("h2_data_RvsZ", "Trk Only Conv: R vs Z " , 1000, -200., 200., 1000, 0., 60);


  TH2F* h2_mc_YvsXBarrelPix =new TH2F("h2_mc_YvsXBarrelPix", "Trk Only Conv: X vs Y Pixels |z|<26 cm, r<20" , 1000, -12., 12., 1000, -12., 12.);
  TH2F* h2_mc_YvsXBarrel =new TH2F("h2_mc_YvsXBarrel", "Trk Only Conv: X vs Y  |z|<26 cm" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_mc_YvsXBarrel_fakes =new TH2F("h2_mc_YvsXBarrel_fakes", "Trk Only Conv: X vs Y  |z|<26 cm" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_mc_YvsXBarrelPix_eta =new TH2F("h2_mc_YvsXBarrelPix_eta", "Trk Only Conv: X vs Y Pixels |eta|<1.4" , 1000, -12., 12., 1000, -12., 12.);
  TH2F* h2_mc_YvsXBarrel_eta =new TH2F("h2_mc_YvsXBarrel_eta", "Trk Only Conv: X vs Y |eta|<1.4" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_mc_YvsX_Z28_32 =new TH2F("h2_mc_YvsX_Z28_32", "Trk Only Conv: X vs Y 28.5<|z|<32, r<18" , 150, -30., 30., 150, -30., 30.);
  TH2F* h2_mc_YvsX_ZLT110 = new TH2F("h2_mc_YvsX_ZLT110", "Trk Only Conv: X vs Y |z|<110, r<30" , 1000, -30., 30., 1000, -30., 30.);
  TH2F* h2_mc_YvsX_ZGT110 = new TH2F("h2_mc_YvsX_ZGT110", "Trk Only Conv: X vs Y |z|>110, r<30" , 1000, -30., 30., 1000, -30., 30.);


  TH2F* h2_data_YvsXBarrelPix =new TH2F("h2_data_YvsXBarrelPix", "Trk Only Conv: X vs Y Pixels |z|<26 cm" , 1000, -12., 12., 1000, -12., 12.);
  TH2F* h2_data_YvsXBarrel =new TH2F("h2_data_YvsXBarrel", "Trk Only Conv: X vs Y Pixels |z|<26 cm" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_data_YvsXBarrelPix_eta =new TH2F("h2_data_YvsXBarrelPix_eta", "Trk Only Conv: X vs Y Pixels |eta|<1.4" , 1000, -12., 12., 1000, -12., 12.);
  TH2F* h2_data_YvsXBarrel_eta =new TH2F("h2_data_YvsXBarrel_eta", "Trk Only Conv: X vs Y  |eta|<1.4" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_data_YvsX_Z28_32 =new TH2F("h2_data_YvsX_Z28_32", "Trk Only Conv: X vs Y  28.5<|z|<32, r<18" , 150, -30., 30., 150, -30., 30.);
  TH2F* h2_data_YvsX_ZLT110 = new TH2F("h2_data_YvsX_ZLT110", "Trk Only Conv: X vs Y |z|<110, r<30" , 1000, -30., 30., 1000, -30., 30.);
  TH2F* h2_data_YvsX_ZGT110 = new TH2F("h2_data_YvsX_ZGT110", "Trk Only Conv: X vs Y |z|>110, r<30" , 1000, -30., 30., 1000, -30., 30.);

  /// resolution on the vertex position  
  TH1F*  h_convVtxdX =    new TH1F("convVtxdX","Vtx dX",100, -5.,5.);
  TH1F*  h_convVtxdY =    new TH1F("convVtxdY","Vtx dY",100, -5.,5.);
  TH1F*  h_convVtxdZ =    new TH1F("convVtxdZ","Vtx dZ",100, -5.,5.);
  TH1F*  h_convVtxdR =    new TH1F("convVtxdR","Vtx dR",100, -5.,5.);

  /// test 5 vs 6 hits
  TH2F *h2_data_tk_hits_vs_pt = new TH2F("h2_data_tk_hits_vs_pt", "CMS preliminary 2010", 50, 0., 50., 30, 0, 30);
  TH2F *h2_mc_tk_hits_vs_pt = new TH2F("h2_mc_tk_hits_vs_pt", "CMS preliminary 2010", 50, 0., 50., 30, 0, 30);
  TH2F *h2_data_tk_hits_vs_eta = new TH2F("h2_data_tk_hits_vs_eta", "CMS preliminary 2010", 50, -2.5, 2.5, 30, 0, 30);
  TH2F *h2_mc_tk_hits_vs_eta = new TH2F("h2_mc_tk_hits_vs_eta", "CMS preliminary 2010", 50, -2.5, 2.5, 30, 0, 30);
  TH2F *h2_data_pt_vs_eta = new TH2F("h2_data_pt_vs_eta", "CMS preliminary 2010", 50, -2.5, 2.5,  100, 0., 50. );
  TH2F *h2_mc_pt_vs_eta = new TH2F("h2_mc_pt_vs_eta", "CMS preliminary 2010", 50, -2.5, 2.5, 100, 0., 50.);

  TH2F *h2_data_tk_pt_vs_algo = new TH2F("h2_data_tk_pt_vs_algo", "CMS preliminary 2010",  8, 3.5, 11.5,  100, 0., 25. );
  TH2F *h2_mc_tk_pt_vs_algo = new TH2F("h2_mc_tk_pt_vs_algo", "CMS preliminary 2010",  8, 3.5, 11.5, 100, 0., 25.);
  TH2F *h2_mc_tk_pt_vs_algo_fakes = new TH2F("h2_mc_tk_pt_vs_algo_fakes", "CMS preliminary 2010",  8, 3.5, 11.5, 100, 0., 25.);


  TH1F *h_mc_photon_eta_5hits = new TH1F("h_mc_photon_eta_5hits", "CMS preliminary 2010",  50, -2.5, 2.5);
  TH1F *h_mc_photon_eta_fakes_5hits = new TH1F("h_mc_photon_eta_fakes_5hits", "CMS preliminary 2010",  50, -2.5, 2.5);
  TH1F *h_data_photon_eta_5hits = new TH1F("h_data_photon_eta_5hits", "CMS preliminary 2010",  50, -2.5, 2.5);

  TH1F *h_mc_photon_z_5hits = new TH1F("h_mc_photon_z_5hits", "CMS preliminary 2010", 300, -150, 150);
  TH1F *h_mc_photon_z_fakes_5hits = new TH1F("h_mc_photon_z_fakes_5hits", "CMS preliminary 2010",  300, -150, 150);
  TH1F *h_data_photon_z_5hits = new TH1F("h_data_photon_z_5hits", "CMS preliminary 2010",  300, -150, 150);

  TH1F *h_mc_photon_pt_5hits = new TH1F("h_mc_photon_pt_5hits", "CMS preliminary 2010", 50, 0, 50);  
  TH1F *h_mc_photon_pt_fakes_5hits = new TH1F("h_mc_photon_pt_fakes_5hits", "CMS preliminary 2010", 50, 0, 50);  
  TH1F *h_data_photon_pt_5hits = new TH1F("h_data_photon_pt_5hits", "CMS preliminary 2010", 50, 0, 50);  

  TH2F* h2_mc_YvsXBarrel_5hits =new TH2F("h2_mc_YvsXBarrel_5hits", "Trk Only Conv: X vs Y Pixels |z|<26 cm at least one tracks with >=5 hits" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_mc_YvsXBarrel_fakes_5hits =new TH2F("h2_mc_YvsXBarrel_fakes_5hits", "Trk Only Conv: X vs Y Pixels |z|<26 cm at least one tracks with >=5 hits" , 1000, -60., 60., 1000, -60., 60.);
  TH2F* h2_data_YvsXBarrel_5hits =new TH2F("h2_data_YvsXBarrel_5hits", "Trk Only Conv: X vs Y Pixels |z|<26 cm at least one tracks with >=5 hits" , 1000, -60., 60., 1000, -60., 60.);

  TH2F* h2_mc_RvsZ_5hits =new TH2F("h2_mc_RvsZ_5hits", "Trk Only Conv: R vs Z  at least one tracks with >=5 hits" , 1000, -200., 200., 1000, 0., 60);
  TH2F* h2_mc_RvsZ_fakes_5hits =new TH2F("h2_mc_RvsZ_fakes_5hits", "Trk Only Conv: R vs Z  at least one tracks with >=5 hits" , 1000, -200., 200., 1000, 0., 60);
  TH2F* h2_data_RvsZ_5hits =new TH2F("h2_data_RvsZ_5hits", "Trk Only Conv: R vs Z  at least one tracks with >=5 hits" , 1000, -200., 200., 1000, 0., 60);

  TH1F *h_mc_tk_algo_5hits = new TH1F("h_mc_tk_algo_5hits", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_mc_tk_algo_fakes_5hits = new TH1F("h_mc_tk_algo_fakes_5hits", "CMS preliminary 2010", 8, 3.5, 11.5);
  TH1F *h_data_tk_algo_5hits = new TH1F("h_data_tk_algo_5hits", "CMS preliminary 2010", 8, 3.5, 11.5); 



  TH1F *h_mc_photon_eta_6hits = new TH1F("h_mc_photon_eta_6hits", "CMS preliminary 2010",  50, -2.5, 2.5);
  TH1F *h_mc_photon_eta_fakes_6hits = new TH1F("h_mc_photon_eta_fakes_6hits", "CMS preliminary 2010",  50, -2.5, 2.5);
  TH1F *h_data_photon_eta_6hits = new TH1F("h_data_photon_eta_6hits", "CMS preliminary 2010",  50, -2.5, 2.5);

  TH1F *h_mc_photon_z_6hits = new TH1F("h_mc_photon_z_6hits", "CMS preliminary 2010", 300, -150, 150);
  TH1F *h_mc_photon_z_fakes_6hits = new TH1F("h_mc_photon_z_fakes_6hits", "CMS preliminary 2010",  300, -150, 150);
  TH1F *h_data_photon_z_6hits = new TH1F("h_data_photon_z_6hits", "CMS preliminary 2010",  300, -150, 150);

  TH1F *h_mc_photon_pt_6hits = new TH1F("h_mc_photon_pt_6hits", "CMS preliminary 2010", 50, 0, 50);  
  TH1F *h_mc_photon_pt_fakes_6hits = new TH1F("h_mc_photon_pt_fakes_6hits", "CMS preliminary 2010", 50, 0, 50);  
  TH1F *h_data_photon_pt_6hits = new TH1F("h_data_photon_pt_6hits", "CMS preliminary 2010", 50, 0, 50);  




  for (Int_t i = 0; i<s1_entries; ++i){
    s2r->GetEntry(i);
    if (i%1000000==1){
      std::cout<<" sim processing "<<i<<std::endl;
    }
    bool isAssoc = sim_.isAssoc;
    double x = sim_.x;
    double y = sim_.y;
    double z = sim_.z;
    double r = sqrt(x*x+y*y);
    double pt = sim_.pt;
    double eta = -log(tan(sim_.theta/2.));
    //	  if ( sim_.pt1<0.2 || sim_.pt2<0.2) continue;
    if ( sim_.pt1<0.05 || sim_.pt2<0.05) continue;
    double minPt=sim_.pt1;
    double maxPt=sim_.pt2;
    if ( sim_.pt1 > sim_.pt2 ) {
      minPt=sim_.pt2;
      maxPt=sim_.pt1;
    }
    h_mcTrue_tkMinPt_vs_r->Fill(r, minPt); 
    h_mcTrue_tkMaxPt_vs_r->Fill(r, maxPt); 
    h_mcTrue_eta_vs_r->Fill ( r, eta);

    if ( r>3.5 && r < 5.) {
      h_mcTrue_tk1_vs_tk2_l1->Fill(minPt, maxPt); 
    } else if ( r>6.5 && r < 8) {
      h_mcTrue_tk1_vs_tk2_l2->Fill(minPt, maxPt); 
    } else if  ( r>9.5 && r <11) {
      h_mcTrue_tk1_vs_tk2_l3->Fill(minPt, maxPt); 
    }


    if (isAssoc) {

      bool tk_algo = sim_.r_algo1 <10 && sim_.r_algo2< 10;
      //bool chi2_quality = (sim_.r_chi2prob>0.003);
      bool chi2_quality = (sim_.r_chi2prob>0.0005);
      bool minapp_q = (sim_.r_minapp<1.);
      bool tk_quality = sim_.r_hits1 > 5 &&  sim_.r_hits2 >5 ;
      bool tkPtCut = sim_.pt1 > 0.5 && sim_.pt2 > 0.5;
      double dphi =  map_2pi(sim_.r_phi1-sim_.r_phi2);
      bool dPhiCut = fabs(dphi)<0.2;
      if (tk_quality && chi2_quality && minapp_q && dPhiCut && tkPtCut  ){
	h_eff_tkPtMin_n ->Fill(minPt);
	if (fabs(z)<26 ) h_eff_r_n->Fill(r);
	if (fabs(z)<120) h_eff_phi_n->Fill(sim_.phi);
	h_eff_eta_n->Fill(eta);
	h_eff_pt_n->Fill(pt);



      }
    }

    h_eff_tkPtMin_d ->Fill(minPt);
    if (fabs(z)<26 ) h_eff_r_d->Fill(r);
    if (fabs(z)<120) h_eff_phi_d->Fill(sim_.phi);
    h_eff_eta_d->Fill(eta);
    h_eff_pt_d->Fill(pt);



  }
  TLegend *leg = new TLegend(0.50,0.83,0.75,.98);
  TLegend *leg2 = new TLegend(0.50,0.83,0.75,.98);
  TLegend *leg3 = new TLegend(0.50,0.73,0.75,.88);
  Int_t r1_use_entries = 0;
  Int_t r1_use_barrel = 0;
  Int_t r1_use_entries_forw = 0;
  Int_t r1_use_entries_allforw = 0;
  Int_t r1_use_entries_forw2 = 0;
  // for (Int_t i = 0; i<0; ++i){
  for (Int_t i = 0; i<r1_entries; ++i){
    r2s->GetEntry(i);
    if (i%10000==0){
      std::cout<<" mc processing "<<i<<std::endl;
    }
    bool isAssoc = mc_.isAssoc;
    int before_hit = mc_.beforeHits1 + mc_.beforeHits2;
    double eta = -log(tan(mc_.theta/2.));
    double x = mc_.x-mc_.vx;
    double y = mc_.y-mc_.vy;
    double z = mc_.z-mc_.vz;

    double cross_x = mc_.tx-mc_.vx;
    double cross_y = mc_.ty-mc_.vy;
    double cross_z = mc_.tz-mc_.vz;
    double cross_r = sqrt(cross_x*cross_x + cross_y*cross_y );

    double r = sqrt(x*x+y*y);
    double vr = sqrt(x*x+y*y);
    double rr = sqrt(mc_.x*mc_.x+mc_.y*mc_.y);
    //double bx = mc_.x-mc_.bsx;
    //double by = mc_.y-mc_.bsy;
    //double bz = mc_.z-mc_.bsz;
    double bx = mc_.x;
    double by = mc_.y;
    double bz = mc_.z;
    double br = sqrt(bx*bx+by*by);
    double dcot = 1./tan(mc_.theta1)-1/tan(mc_.theta2);
    double dz = mc_.z1-mc_.z2;
    double minapp = mc_.minapp;
    float phiPos, phiNeg;
    if ( mc_.pt1 > mc_.pt2 ) {
         phiPos=mc_.iphi1;
	 phiNeg=mc_.iphi2;
    } else {
         phiPos=mc_.iphi2;
	 phiNeg=mc_.iphi1;
    }
    //    double dphi =  map_2pi(mc_.iphi1-mc_.iphi2);
    double dphi =  map_2pi(phiPos-phiNeg);

    bool tk_quality = mc_.nHits1 > 5 &&  mc_.nHits2 >5 ; 
    bool tkPtCut = mc_.pt1 > 0.5 && mc_.pt2 > 0.5;
    bool convPtCut =  mc_.pt<5;
     bool tk_algo = mc_.algo1 <10 && mc_.algo2< 10; 
    // bool chi2_quality = (mc_.chi2prob>0.003);
    bool chi2_quality = (mc_.chi2prob>0.0005);
    bool minapp_q = (mc_.minapp<1.);
    bool d0_cut =  mc_.d01*mc_.q1>0.05 && mc_.d02*mc_.q2>0.05; 
    bool dPhiCut = fabs(dphi)<0.2;
    bool run_quality = true;
    double minPt = mc_.pt1;
    double maxPt = mc_.pt2;
    if (  mc_.pt1 >   mc_.pt2) {
      double minPt = mc_.pt2;
      double maxPt = mc_.pt1;
    }

    if (tk_quality && minapp_q  ) {
      h_mc_photon_chi2prob_beforeCut -> Fill(mc_.chi2prob);
      if ( !isAssoc) h_mc_photon_fakes_chi2prob_beforeCut -> Fill(mc_.chi2prob);
    }

    //		  if (vtx_quality && tk_quality && eta_quality && minapp_q){
    if (tk_quality && minapp_q   && chi2_quality && dPhiCut && tkPtCut ){
		    
		    
      if (! isAssoc) {
	if (fabs(z)<26 ) h_fakeRate_r_n->Fill(r);
	if (fabs(z)<120 ) h_fakeRate_phi_n->Fill(mc_.phi);
	h_fakeRate_eta_n->Fill (eta); 
	h_fakeRate_pt_n->Fill (mc_.pt); 

      } 
      if (fabs(z)<26 ) h_fakeRate_r_d->Fill(r);
      h_fakeRate_eta_d->Fill (eta); 
      h_fakeRate_pt_d->Fill (mc_.pt); 
      if (fabs(z)<120 ) h_fakeRate_phi_d->Fill(mc_.phi);
		    
      r1_use_entries++;
      if  (fabs(mc_.z) >=26 && br<=20 ) r1_use_entries_forw++;
      if  (fabs(mc_.z) >=26  ) r1_use_entries_allforw++;
      if  (fabs(mc_.z) >20 && fabs(mc_.z) <40 &&  br>12 && br<20  ) r1_use_entries_forw2++;


      //// fill in scatter plots
      //h2_mc_RvsZ->Fill( mc_.z, br*(mc_.y>0?1:-1));
      h2_mc_RvsZ->Fill( mc_.z, br);
      if ( fabs(mc_.z) <26) {
	if ( br<20) h2_mc_YvsXBarrelPix ->Fill(mc_.x, mc_.y);
	h2_mc_YvsXBarrel ->Fill(mc_.x, mc_.y);
	if ( !isAssoc)  h2_mc_YvsXBarrel_fakes->Fill(mc_.x, mc_.y);
      }
      if ( fabs(eta) <1.2) {
	if ( br<20) h2_mc_YvsXBarrelPix_eta ->Fill(mc_.x, mc_.y);
	h2_mc_YvsXBarrel_eta ->Fill(mc_.x, mc_.y);
      }
      if ( fabs(mc_.z) > 29 && fabs(mc_.z) <33 )  h2_mc_YvsX_Z28_32 ->Fill(mc_.x,mc_.y);
      if ( fabs(mc_.z) < 110 && br <30 )  h2_mc_YvsX_ZLT110 ->Fill(mc_.x,mc_.y);
      if ( fabs(mc_.z) > 110 && br <30 )  h2_mc_YvsX_ZGT110 ->Fill(mc_.x,mc_.y);


      // vertx resolution
      if ( isAssoc ) {
	h_convVtxdX->Fill ( mc_.deltax );
	h_convVtxdY->Fill ( mc_.deltay );
	h_convVtxdZ->Fill ( mc_.deltaz );
        float recoR= sqrt(mc_.x*mc_.x + mc_.y*mc_.y );
        float simR = sqrt((mc_.x+mc_.deltax)*(mc_.x+mc_.deltax)+(mc_.y+mc_.deltay)*(mc_.y+mc_.deltay)); 
        float deltar= recoR-simR;
	h_convVtxdR->Fill ( deltar );
      }
      
      float mass_recal = pairInvariantMass(mc_.ipx1, mc_.ipy1, mc_.ipz1, mc_.ipx2, mc_.ipy2, mc_.ipz2);
      if ( mass_recal >= 0.25) mass_recal =  0.25 -0.0001; 
      h_mc_photon_mass2->Fill(mass_recal);
      if ( fabs(mc_.z) < 26 ) h_mc_photon_mass2_barrel->Fill(mass_recal);
      if ( fabs(mc_.z) < 26 ) h_mc_photon_mass2_vs_r->Fill(br,mass_recal);
		    
      float phoPtAtVtx = pairPt (mc_.ipx1, mc_.ipy1, mc_.ipz1, mc_.ipx2, mc_.ipy2,mc_.ipz2);
      h_mc_photon_pt_ext->Fill(mc_.pt);
      h_mc_photon_pt_recal->Fill(phoPtAtVtx );
      h2_mc_pt_vs_eta -> Fill (eta,mc_.pt); 
      //      if ( fabs(eta)< 0.9 )  h_mc_photon_pt_ext_barrel->Fill(mc_.pt);
      if   ( fabs(mc_.z)<26 ) {
	h_mc_photon_pt_ext_barrel->Fill(mc_.pt);
      }


      h_mc_photon_crossR -> Fill (cross_r);
      h_mc_photon_chi2prob -> Fill(mc_.chi2prob);
      h_mc_photon_chi2prob_zoom -> Fill(mc_.chi2prob);
		    
      h_mc_photon_phi->Fill(mc_.phi);
      if ( fabs(mc_.z) < 26 && r < 19) 
        h_mc_photon_phi_ZLT26_RLT19 -> Fill ( mc_.phi );
      if ( fabs(mc_.z) < 26 && r > 28 && r < 30 )  
	h_mc_photon_phi_ZLT26_28_R_30 -> Fill ( mc_.phi );

      if ( fabs(mc_.z) < 73 && r > 22 ) 
        h_mc_photon_phi_ZLT73_RGT22 -> Fill ( mc_.phi );
      if (  mc_.z > 0 && mc_.z < 73 && r>27 && r < 35) 
        h_mc_photon_phi_posZLT73_27_R_35 -> Fill ( mc_.phi );
      if ( mc_.z < 0 && mc_.z >- 73 && r>27 && r < 35) 
        h_mc_photon_phi_negZLT73_27_R_35 -> Fill ( mc_.phi );
	

      float iphi = atan2(mc_.y, mc_.x);//pixel center at 000
      h_mc_photon_iphi->Fill(iphi);

		    
      if (fabs(mc_.z) < 26 ) {
	h_mc_photon_z_phi->Fill(mc_.phi);
	float iphi = atan2(mc_.y, mc_.x);//pixel center at 000
	h_mc_photon_z_iphi->Fill(iphi);
      }
		    
      h_mc_photon_eta->Fill(eta);
      h_mc_photon_dz->Fill(dz);
      if ( fabs(mc_.z1)<120 && fabs(sqrt(mc_.x1*mc_.x1+mc_.x2*mc_.x2))>55
	   || fabs(mc_.z1)<70 && fabs(sqrt(mc_.x1*mc_.x1+mc_.x2*mc_.x2)) <55){
	h_mc_photon_dz_s->Fill(dz);
	if ( !isAssoc) h_mc_photon_dz_fakes_s->Fill(dz);
      }

      h_mc_photon_dphi->Fill(dphi);
      h_mc_photon_dcot->Fill(dcot);
      h_mc_photon_minapp->Fill(minapp);
      h_mc_tk_hits->Fill(mc_.nHits1);
      h_mc_tk_hits->Fill(mc_.nHits2);

      h_mc_tk_charge->Fill(mc_.q1);
      h_mc_tk_charge->Fill(mc_.q2);

      h2_mc_tk_hits_vs_pt -> Fill (mc_.pt, float(mc_.nHits1)); 
      h2_mc_tk_hits_vs_pt -> Fill (mc_.pt, float(mc_.nHits2)); 

      h2_mc_tk_hits_vs_eta -> Fill (eta, float(mc_.nHits1)); 
      h2_mc_tk_hits_vs_eta -> Fill (eta, float(mc_.nHits2)); 

      h2_mc_tk_pt_vs_algo-> Fill(float(mc_.algo1),mc_.pt1); 
      h2_mc_tk_pt_vs_algo-> Fill(float(mc_.algo2),mc_.pt2); 
      if ( !isAssoc) {
	h2_mc_tk_pt_vs_algo_fakes-> Fill(float(mc_.algo1),mc_.pt1); 
	h2_mc_tk_pt_vs_algo_fakes-> Fill(float(mc_.algo2),mc_.pt2); 
      }

      if ( mc_.nHits1==5 || mc_.nHits2==5) {
	h_mc_photon_eta_5hits->Fill(eta);
	h_mc_photon_z_5hits->Fill(mc_.z);
	h_mc_photon_pt_5hits->Fill(mc_.pt);
	h2_mc_YvsXBarrel_5hits ->Fill(mc_.x, mc_.y);
	h2_mc_RvsZ_5hits -> Fill( mc_.z, br); 
	if ( mc_.nHits1==5 ) 
           h_mc_tk_algo_5hits->Fill(mc_.algo1);
	else if ( mc_.nHits2==5 ) 
	  h_mc_tk_algo_5hits->Fill(mc_.algo2);
        if (!isAssoc) {
	  h_mc_photon_eta_fakes_5hits->Fill(eta);
	  h_mc_photon_z_fakes_5hits->Fill(mc_.z);
	  h_mc_photon_pt_fakes_5hits->Fill(mc_.pt);
	  h2_mc_YvsXBarrel_fakes_5hits ->Fill(mc_.x, mc_.y);
	  h2_mc_RvsZ_fakes_5hits ->Fill( mc_.z, br);
	  if ( mc_.nHits1==5 ) 
	    h_mc_tk_algo_fakes_5hits->Fill(mc_.algo1);
	  else if ( mc_.nHits2==5 ) 
	    h_mc_tk_algo_fakes_5hits->Fill(mc_.algo2);

	}
      }

      if ( mc_.nHits1==6 || mc_.nHits2==6) {
	h_mc_photon_eta_6hits->Fill(eta);
	h_mc_photon_z_6hits->Fill(mc_.z);
	h_mc_photon_pt_6hits->Fill(mc_.pt);
        if (!isAssoc) {
	  h_mc_photon_eta_fakes_6hits->Fill(eta);
	  h_mc_photon_z_fakes_6hits->Fill(mc_.z);
	  h_mc_photon_pt_fakes_6hits->Fill(mc_.pt);

	}
      }



      h_mc_tk_chi2->Fill(mc_.chi21);
      h_mc_tk_chi2->Fill(mc_.chi22);
      h_mc_tk_pt->Fill(mc_.pt1);
      h_mc_tk_pt->Fill(mc_.pt2);
      if ( fabs(mc_.z) < 26 ) {
	h_mc_tk_pt_barrel->Fill(mc_.pt1);
	h_mc_tk_pt_barrel->Fill(mc_.pt2);
	
      }

      if ( fabs(mc_.z) < 26 ) {
		      
	h_mcReco_tkMinPt_vs_r->Fill(br, minPt); 
	h_mcReco_tkMaxPt_vs_r->Fill(br, maxPt); 
		      
      }
 
      if ( fabs(mc_.z) < 26 &&  br>3.5 && br < 5.) {
	h_mc_tk_pt1->Fill(mc_.pt1);
	h_mc_tk_pt1->Fill(mc_.pt2);
	h_mc_tk_algo_l1->Fill(float(mc_.algo1));
	h_mc_tk_algo_l1->Fill(float(mc_.algo2));
	
      } else if (  fabs(mc_.z) < 26 &&  br>6.5 && br < 8) {
	h_mc_tk_pt2->Fill(mc_.pt1);
	h_mc_tk_pt2->Fill(mc_.pt2);
	h_mc_tk_algo_l2->Fill(float(mc_.algo1));
	h_mc_tk_algo_l2->Fill(float(mc_.algo2));
	
      } else if  (  fabs(mc_.z) < 26 && br>9.5 && br <11) {
	h_mc_tk_pt3->Fill(mc_.pt1);
	h_mc_tk_pt3->Fill(mc_.pt2);
	h_mc_tk_algo_l3->Fill(float(mc_.algo1));
	h_mc_tk_algo_l3->Fill(float(mc_.algo2));
	
      }


      //  if ( fabs(mc_.z) < 26 && br < 12) {  
	h_mc_tk_algo->Fill(float(mc_.algo1));
	h_mc_tk_algo->Fill(float(mc_.algo2));
	// }


      h_mc_d0->Fill(mc_.d01*mc_.q1);
      h_mc_d0->Fill(mc_.d02*mc_.q2);
      h_mc_d0_ext->Fill(mc_.d01*mc_.q1);
      h_mc_d0_ext->Fill(mc_.d02*mc_.q2);
			
                                  
      if ( !isAssoc) {
	h_mc_tk_hits_fakes->Fill(mc_.nHits1);
	h_mc_tk_hits_fakes->Fill(mc_.nHits2);
	h_mc_tk_chi2_fakes->Fill(mc_.chi21);
	h_mc_tk_chi2_fakes->Fill(mc_.chi22);
	h_mc_tk_charge_fakes->Fill(mc_.q1);
	h_mc_tk_charge_fakes->Fill(mc_.q2);


	if ( mc_.pt1 > 0.2 && mc_.pt2 > 0.2 ) {
	  h_mc_tk_pt_fakesGT02->Fill(mc_.pt1);
	  h_mc_tk_pt_fakesGT02->Fill(mc_.pt2);			
	} 

	h_mc_tk_pt_fakes->Fill(mc_.pt1);
	h_mc_tk_pt_fakes->Fill(mc_.pt2);
	if ( fabs(mc_.z) < 26 ) {
	  h_mc_tk_pt_fakes_barrel->Fill(mc_.pt1);
	  h_mc_tk_pt_fakes_barrel->Fill(mc_.pt2);

	}			    

	if ( fabs(mc_.z) < 26 && br>3.5 && br < 5.) {

	  if ( mc_.pt1 > 0.2 && mc_.pt2 > 0.2 ) {
	    h_mc_tk_pt1_fakesGT02->Fill(mc_.pt1);
	    h_mc_tk_pt1_fakesGT02->Fill(mc_.pt2);			
	    h_mc_tk_algo_fakesGT02_l1->Fill(float(mc_.algo1));
	    h_mc_tk_algo_fakesGT02_l1->Fill(float(mc_.algo2));
				      
	  } 
	  h_mc_tk_pt1_fakes->Fill(mc_.pt1);
	  h_mc_tk_pt1_fakes->Fill(mc_.pt2);
	  h_mc_tk_algo_fakes_l1->Fill(float(mc_.algo1));
	  h_mc_tk_algo_fakes_l1->Fill(float(mc_.algo2));
				     
	} else if (  fabs(mc_.z) < 26 && br>6.5 && br < 8) {

	  if ( mc_.pt1 > 0.2 && mc_.pt2 > 0.2 ) {
	    h_mc_tk_pt2_fakesGT02->Fill(mc_.pt1);
	    h_mc_tk_pt2_fakesGT02->Fill(mc_.pt2);			
	    h_mc_tk_algo_fakesGT02_l2->Fill(float(mc_.algo1));
	    h_mc_tk_algo_fakesGT02_l2->Fill(float(mc_.algo2));
			
	  } 
	  h_mc_tk_pt2_fakes->Fill(mc_.pt1);
	  h_mc_tk_pt2_fakes->Fill(mc_.pt2);
	  h_mc_tk_algo_fakes_l2->Fill(float(mc_.algo1));
	  h_mc_tk_algo_fakes_l2->Fill(float(mc_.algo2));

	} else if  (  fabs(mc_.z) < 26 && br>9.5 && br <11) {


	  if ( mc_.pt1 > 0.2 && mc_.pt2 > 0.2 ) {
	    h_mc_tk_pt3_fakesGT02->Fill(mc_.pt1);
	    h_mc_tk_pt3_fakesGT02->Fill(mc_.pt2);			
	    h_mc_tk_algo_fakesGT02_l3->Fill(float(mc_.algo1));
	    h_mc_tk_algo_fakesGT02_l3->Fill(float(mc_.algo2));
			
	  } 
	  h_mc_tk_pt3_fakes->Fill(mc_.pt1);
	  h_mc_tk_pt3_fakes->Fill(mc_.pt2);
	  h_mc_tk_algo_fakes_l3->Fill(float(mc_.algo1));
	  h_mc_tk_algo_fakes_l3->Fill(float(mc_.algo2));

	}

	//	if ( fabs(mc_.z) < 26 && br < 12) {
	  h_mc_tk_algo_fakes->Fill(float(mc_.algo1));
	  h_mc_tk_algo_fakes->Fill(float(mc_.algo2));
	  //	}

	h_mc_fakes_d0->Fill(mc_.d01*mc_.q1);
	h_mc_fakes_d0->Fill(mc_.d02*mc_.q2);
	h_mc_fakes_d0_ext->Fill(mc_.d01*mc_.q1);
	h_mc_fakes_d0_ext->Fill(mc_.d02*mc_.q2);
	h_mc_photon_pt_fakes_ext->Fill(mc_.pt);
	h_mc_photon_pt_fakes_recal->Fill(phoPtAtVtx );

	if  (fabs(mc_.z)<26  ){
	  h_mc_photon_pt_fakes_ext_barrel->Fill(mc_.pt);
	}
	  //if ( fabs(eta)< 0.9 )  h_mc_photon_pt_fakes_ext_barrel->Fill(mc_.pt);
	h_mc_photon_fakes_eta->Fill(eta);
	h_mc_photon_crossR_fakes -> Fill (cross_r);
	h_mc_photon_fakes_chi2prob -> Fill(mc_.chi2prob);
	h_mc_photon_fakes_chi2prob_zoom -> Fill(mc_.chi2prob);


	h_mc_photon_fakes_phi->Fill(mc_.phi);
	if ( fabs(mc_.z) < 26 && r < 19) 
	  h_mc_photon_fakes_phi_ZLT26_RLT19 -> Fill ( mc_.phi );

	if ( fabs(mc_.z) < 26 && r > 28 && r < 30 )  
	  h_mc_photon_fakes_phi_ZLT26_28_R_30 -> Fill ( mc_.phi );


	if  ( fabs(mc_.z) < 73 && r > 22) 
	  h_mc_photon_fakes_phi_ZLT73_RGT22 -> Fill ( mc_.phi );
	if (  mc_.z>0 && mc_.z < 73 && r>27 && r < 35) 
	  h_mc_photon_fakes_phi_posZLT73_27_R_35 -> Fill ( mc_.phi );
	if (  mc_.z <0 && mc_.z >- 73 && r>27 && r < 35) 
	  h_mc_photon_fakes_phi_negZLT73_27_R_35 -> Fill ( mc_.phi );
	


	h_mc_photon_fakes_iphi->Fill(iphi);
	if (fabs(mc_.z) < 26 ) {
	  h_mc_photon_fakes_z_phi->Fill(mc_.phi);
	  h_mc_photon_fakes_z_iphi->Fill(iphi);
	}


	h_mc_photon_fakes_dphi->Fill(dphi);
	h_mc_photon_fakes_dcot->Fill(dcot);
	h_mc_photon_fakes_minapp->Fill(minapp);
	if ( mc_.pt1 > 0.2 && mc_.pt2 > 0.2 ) {
	  h_mc_photon_fakesGT02_mass2->Fill(mass_recal);
	  h_mc_photon_fakesGT02_mass2_vs_r->Fill(br, mass_recal);
	}
	h_mc_photon_fakes_mass2->Fill(mass_recal);
	if ( fabs(mc_.z) < 26 ) 	h_mc_photon_fakes_mass2_barrel->Fill(mass_recal);
	if ( fabs(mc_.z) < 26 ) h_mc_photon_fakes_mass2_vs_r->Fill(br,mass_recal);
				    
	
      }

      if (  (fabs(mc_.z)<26 && r<20) ||  (fabs(mc_.z)<66 && (r>20 && r< 65) ) ){
	h_mc_photon_br_z_barrel2->Fill(br);
        if ( !isAssoc ) h_mc_photon_br_z_fakes_barrel2->Fill(br);
      }

      if (fabs(mc_.z)<26){
	h_mc_photon_br_z_barrel->Fill(br);
	if ( !isAssoc) h_mc_photon_br_z_fakes_barrel->Fill(br);
	if (r<20) {
	  h_mc_photon_br_z_pixel->Fill(br);
	  if ( !isAssoc) h_mc_photon_br_z_fakes_pixel->Fill(br);
	}
	if ( r<60) {
	  h_mc_photon_br_z_pixel_rebin->Fill(br);
	  if ( !isAssoc) h_mc_photon_br_z_fakes_pixel_rebin->Fill(br);
	}
      }
      if (fabs(eta)<1.2){
	h_mc_photon_r->Fill(r);
	if (r<20){
	  h_mc_photon_vr_pixel->Fill(vr);
	  h_mc_photon_r_pixel->Fill(rr);
	}
	h_mc_photon_br->Fill(br);
	if (r<20) {
	  h_mc_photon_br_eta_pixel->Fill(br);
	  if ( !isAssoc) h_mc_photon_br_eta_fakes_pixel->Fill(br);
			
	}
	h_mc_photon_br_eta_barrel->Fill(br);
	if ( !isAssoc) h_mc_photon_br_eta_fakes_barrel->Fill(br);


	if (r<12)
	  h_mc_photon_r_pixel_s->Fill(br);
      }

      //if (fabs(mc_.z) >= 26 ) {
      if ( br<19 && br>3.5 ) {
      //if ( br< 19 ) {
      //if ( br<=20 ) {
	  h_mc_photon_z_pixel ->Fill(mc_.z);	
	  if ( !isAssoc ) 
	    h_mc_photon_z_pixel_fakes ->Fill(mc_.z); 	  		
      }
      h_mc_photon_z ->Fill(mc_.z);
      if ( !isAssoc ) 
	h_mc_photon_z_fakes ->Fill(mc_.z);
	//    }
      

      if (fabs(mc_.z) >124  ) {
	if ( br>22 ) {
	  h_mc_photon_z_ZGT124 ->Fill(fabs(mc_.z)); 
	  if ( !isAssoc ) 
	    h_mc_photon_z_ZGT124_fakes ->Fill(fabs(mc_.z)); 
	}

      }

      if  (fabs(mc_.z) >20 && fabs(mc_.z) <40 &&  br>12 && br<20  ) {
	h_mc_photon_z_flange ->Fill(mc_.z);
	if ( !isAssoc ) h_mc_photon_z_flange_fakes ->Fill(mc_.z);

      }

      if (fabs(eta)<2.){
	if (fabs(mc_.z)<26){
	  h_mc_photon_br_etaz_pixel->Fill(br);
	  if ( !isAssoc) h_mc_photon_br_etaz_fakes_pixel->Fill(br);
	}
					  
      }

      if (fabs(eta)>.2){
	h_mc_photon_eta_s->Fill(eta);
	if (fabs(eta)<0.9){
	  //if (r<20)
	  //h_mc_photon_r_pixel_s->Fill(r);
	}

      } else if (fabs(mc_.minapp)<1. && fabs(mc_.iphi1-mc_.iphi2)<0.4){
	h_mc_photon_eta_s->Fill(eta);
	if (fabs(eta)<0.9){
	  //if (r<20)
	  //h_mc_photon_r_pixel_s->Fill(r);
	}
      }
    }
  }
  Int_t r2_use_entries = 0;
  Int_t r2_use_entries_forw = 0;
  Int_t r2_use_entries_allforw = 0;
  Int_t r2_use_entries_forw2 = 0;



  Double_t xx[5595], yy[5595];
  int id =0;
  for (Int_t i = 0; i<r2_entries; ++i){
    r2s2->GetEntry(i);
    int run = data_.run;
    int before_hit = data_.beforeHits1 + data_.beforeHits2;
    double eta = -log(tan(data_.theta/2.));
    double x = data_.x-data_.vx;
    double y = data_.y-data_.vy;
    double z = data_.z-data_.vz;
    double r = sqrt(x*x+y*y);
    double vr = sqrt(x*x+y*y);
    double rr = sqrt(data_.x*data_.x+data_.y*data_.y);
    double bx = data_.x+0.1475;
    double by = data_.y+0.3782;
    //    double bz = data_.z+0.4847;
    double bz = data_.z+0.3;

    double br = sqrt(bx*bx+by*by);

    double cross_x = data_.tx-data_.vx;
    double cross_y = data_.ty-data_.vy;
    double cross_z = data_.tz-data_.vz;
    double cross_r = sqrt(cross_x*cross_x + cross_y*cross_y );


    double xBP = data_.x-0.0933;
    double yBP = data_.y+0.1696;
    double  rBP = sqrt(xBP*xBP + yBP*yBP);

    double bpr = sqrt((data_.x+0.1393)*(data_.x+0.1393)+(data_.y+0.3767)*(data_.y+0.3767));
    double dcot = 1./tan(data_.theta1)-1/tan(data_.theta2);
    double dz = data_.z1-data_.z2;
    double minapp = data_.minapp;
    float phiPos, phiNeg;
    if ( data_.pt1 > data_.pt2  ) {
         phiPos=data_.iphi1;
	 phiNeg=data_.iphi2;
    } else {
         phiPos=data_.iphi2;
	 phiNeg=data_.iphi1;
    }
    double dphi =  map_2pi(phiPos-phiNeg);
    //    double dphi = map_2pi(data_.iphi1-data_.iphi2);

    bool  run_quality=true;
    bool tk_algo = data_.algo1 <10 && data_.algo2 <10; 
    // bool chi2_quality = (data_.chi2prob>0.003);
    bool chi2_quality = (data_.chi2prob>0.0005);
    bool d0_cut = data_.d01*data_.q1>0.05 && data_.d02*data_.q2>0.05;
    bool minapp_q = (data_.minapp<1.);
    bool tk_quality = data_.nHits1 >5 &&  data_.nHits2 >5;
    bool tkPtCut = data_.pt1 > 0.5 && data_.pt2 > 0.5;
    bool convPtcut =  data_.pt<5 ;
    bool dPhiCut = fabs(dphi)<0.2;
    //bool minapp_q = true;
    if (run_quality){
      if ( tk_quality && minapp_q   )
	h_data_photon_chi2prob_beforeCut -> Fill(data_.chi2prob);

      if ( tk_quality && minapp_q  && chi2_quality && dPhiCut && tkPtCut  ){

	r2_use_entries++;
	if (fabs(data_.z) >= 26 && br <= 20 )  r2_use_entries_forw++;
	if (fabs(data_.z) >= 2 )  r2_use_entries_allforw++;
	if  (fabs(data_.z) >20 && fabs(data_.z) <40 &&  br>12 && br<20  ) r2_use_entries_forw2++;
	
	// fill scatter plots	
	//	h2_data_RvsZ->Fill( data_.z, br*(data_.y>0?1:-1));
	h2_data_RvsZ->Fill( data_.z, br);
	if ( fabs(data_.z) <26) {
	  if ( br<20) h2_data_YvsXBarrelPix ->Fill(data_.x, data_.y);
	  //h2_data_YvsXBarrel ->Fill(data_.x, data_.y);
	  h2_data_YvsXBarrel ->Fill(bx, by);
	}
	if ( fabs(eta) <1.2) {
	  if ( br<20) h2_data_YvsXBarrelPix_eta ->Fill(data_.x, data_.y);
	  h2_data_YvsXBarrel_eta ->Fill(data_.x, data_.y);
	}
	if ( fabs(data_.z) > 29 && fabs(data_.z) <33 )  h2_data_YvsX_Z28_32 ->Fill(bx,by);
	if ( fabs(data_.z) < 110 && br <30 )  h2_data_YvsX_ZLT110 ->Fill(data_.x,data_.y);
	if ( fabs(data_.z) > 110 && br <30 )  h2_data_YvsX_ZGT110 ->Fill(data_.x,data_.y);

        float ptAtVtx= pairPt( data_.ipx1, data_.ipy1, data_.ipz1, data_.ipx2, data_.ipy2, data_.ipz2);
	h_data_photon_pt_recal->Fill(ptAtVtx);
	h_data_photon_pt_ext->Fill(data_.pt);
	h2_data_pt_vs_eta -> Fill (eta,data_.pt); 

	if (fabs(data_.z)<26  ) {
	  h_data_photon_pt_ext_barrel->Fill(data_.pt);
	}

	 //	if ( fabs(eta)< 0.9 )  h_data_photon_pt_ext_barrel->Fill(data_.pt);
	float mass_recal = pairInvariantMass(data_.ipx1, data_.ipy1, data_.ipz1, data_.ipx2, data_.ipy2, data_.ipz2);
	if ( mass_recal >= 0.25) mass_recal =  0.25 -0.0001; 
	h_data_photon_mass2->Fill(mass_recal);
	if ( fabs(data_.z) < 26 )  	h_data_photon_mass2_barrel->Fill(mass_recal);
	if ( fabs(data_.z) < 26 ) h_data_photon_mass2_vs_r->Fill(br,mass_recal);
		      
		      
	h_data_photon_phi->Fill(data_.phi);
	if ( fabs(data_.z) < 26 && r < 19) 
	  h_data_photon_phi_ZLT26_RLT19 -> Fill ( data_.phi );

	if ( fabs(data_.z) < 26 && r > 28 && r < 30 )  
	  h_data_photon_phi_ZLT26_28_R_30 -> Fill ( data_.phi );

	if  ( fabs(data_.z) < 73 && r > 22) 
	  h_data_photon_phi_ZLT73_RGT22 -> Fill ( data_.phi );

	if (  data_.z>0 && data_.z < 73 && r> 27 && r < 35) 
	  h_data_photon_phi_posZLT73_27_R_35 -> Fill ( data_.phi );

	if (  data_.z <0 && data_.z > -73 && r> 27 && r < 35) 
	  h_data_photon_phi_negZLT73_27_R_35 -> Fill ( data_.phi );
	
	


	float iphi = atan2(by, bx);
	h_data_photon_iphi->Fill(iphi);
	if (fabs(data_.z) < 26 ) {
	  h_data_photon_z_phi->Fill(data_.phi);
	  h_data_photon_z_iphi->Fill(iphi);
	}
		      
		      
	h_data_photon_chi2prob -> Fill(data_.chi2prob);
	h_data_photon_chi2prob_zoom -> Fill(data_.chi2prob);
	h_data_photon_crossR -> Fill (cross_r);
	h_data_photon_eta->Fill(eta);
	h_data_tk_hits->Fill(data_.nHits1);
	h_data_tk_hits->Fill(data_.nHits2);
	h_data_tk_charge->Fill(data_.q1);
	h_data_tk_charge->Fill(data_.q2);


	h2_data_tk_hits_vs_pt -> Fill (data_.pt, float(data_.nHits1)); 
	h2_data_tk_hits_vs_pt -> Fill (data_.pt, float(data_.nHits2)); 
	h2_data_tk_hits_vs_eta -> Fill (eta, float(data_.nHits1)); 
	h2_data_tk_hits_vs_eta -> Fill (eta, float(data_.nHits2)); 

	h2_data_tk_pt_vs_algo-> Fill(float(data_.algo1),data_.pt1); 
	h2_data_tk_pt_vs_algo-> Fill(float(data_.algo2),data_.pt2); 


	if ( data_.nHits1==5 || data_.nHits2==5) {
	  h_data_photon_eta_5hits->Fill(eta);
	  h_data_photon_z_5hits->Fill(bz);
	  h_data_photon_pt_5hits->Fill(data_.pt);
	  h2_data_YvsXBarrel_5hits ->Fill(data_.x, data_.y);
	  h2_data_RvsZ_5hits -> Fill( data_.z, br); 
	  if ( data_.nHits1==5 ) 
	    h_data_tk_algo_5hits->Fill(data_.algo1);
	  else if ( data_.nHits2==5 ) 
	    h_data_tk_algo_5hits->Fill(data_.algo2);
	}

	if ( data_.nHits1==6 || data_.nHits2==6) {
	  h_data_photon_eta_6hits->Fill(eta);
	  h_data_photon_z_6hits->Fill(bz);
	  h_data_photon_pt_6hits->Fill(data_.pt);
	}
	


	h_data_tk_chi2->Fill(data_.chi21);
	h_data_tk_chi2->Fill(data_.chi22);
	h_data_tk_pt->Fill(data_.pt1);
	h_data_tk_pt->Fill(data_.pt2);
	if   ( fabs(data_.z) < 26 ) {
	  h_data_tk_pt_barrel->Fill(data_.pt1);
	  h_data_tk_pt_barrel->Fill(data_.pt2);

	}

		      
	if ( fabs(data_.z) < 26 && br>3.5 && br < 5.) {
	  h2_data_tk_pt_l1 -> Fill ( data_.pt1, data_.pt2);
	  h_data_tk_pt1->Fill(data_.pt1);
	  h_data_tk_pt1->Fill(data_.pt2);
	  h_data_tk_algo_l1->Fill(float(data_.algo1));
	  h_data_tk_algo_l1->Fill(float(data_.algo2));
			
	} else if (fabs(data_.z) < 26 && br>6.5 && br < 8) {
	  h2_data_tk_pt_l2 -> Fill ( data_.pt1, data_.pt2);
	  h_data_tk_pt2->Fill(data_.pt1);
	  h_data_tk_pt2->Fill(data_.pt2);
	  h_data_tk_algo_l2->Fill(float(data_.algo1));
	  h_data_tk_algo_l2->Fill(float(data_.algo2));
			
	} else if  ( fabs(data_.z) < 26 && br>9.5 && br <11) {
	  h2_data_tk_pt_l3 -> Fill ( data_.pt1, data_.pt2);
	  h_data_tk_pt3->Fill(data_.pt1);
	  h_data_tk_pt3->Fill(data_.pt2);
	  h_data_tk_algo_l3->Fill(float(data_.algo1));
	  h_data_tk_algo_l3->Fill(float(data_.algo2));
			
	}
		      
	//	if ( fabs(data_.z) < 26 && br < 12) {
	  h_data_tk_algo->Fill(float(data_.algo1));
	  h_data_tk_algo->Fill(float(data_.algo2));
	  //	}
	h_data_d0->Fill(data_.d01*data_.q1);
	h_data_d0->Fill(data_.d02*data_.q2);
	h_data_d0_ext->Fill(data_.d01*data_.q1);
	h_data_d0_ext->Fill(data_.d02*data_.q2);
	h_data_photon_dz->Fill(dz);
	if (fabs(data_.z1)<120 && fabs(sqrt(data_.x1*data_.x1+data_.x2*data_.x2))>55
	    || fabs(data_.z1)<70 && fabs(sqrt(data_.x1*data_.x1+data_.x2*data_.x2))<55){
	  h_data_photon_dz_s->Fill(dz);
	}
	if (fabs(eta)>0.8 && fabs(eta)<1.2 && fabs(rr>50)){
	  //std::cout<<" run "<<run<<" Event "<<data_.event<<std::endl;
	  //		  std::cout<<" tk1 pT "<<data_.pt1<<" eta "<<-log(tan(data_.theta1/2))<<" inner r "<<sqrt(data_.x1*data_.x1+data_.y1*data_.y1)
	  //			  <<" hits "<<data_.nHits1<<"  pixel hit "<<data_.npHits1<<" stereo hits "<<data_.nsHits1<<"  miss "<<data_.missHits1
	  //			  <<"\n tk2 pT "<<data_.pt2<<" eta "<<-log(tan(data_.theta2/2))<<" inner r "<<sqrt(data_.x1*data_.x1+data_.y1*data_.y2)
	  //			  <<" hits "<<data_.nHits2<<"  pixel hit "<<data_.npHits2<<" stereo hits "<<data_.nsHits2<<"  miss "<<data_.missHits2
	  //			  <<std::endl;
	}
	h_data_photon_dphi->Fill(dphi);
	h_data_photon_dcot->Fill(dcot);
	h_data_photon_minapp->Fill(minapp);

	if (  (fabs(data_.z)<26 && r<20) ||  (fabs(data_.z)<66 && (r>20 && r< 65) ) ){
	  h_data_photon_br_z_barrel2->Fill(br);
	}
	if (fabs(data_.z)<26){
	  h_data_photon_br_z_barrel->Fill(br);
	  if (r<20){
	    h_data_photon_br_z_pixel->Fill(br);
	    h_data_photon_br_z_pixel_beampipe->Fill(rBP);
	    h_data_photon_bpr_z_pixel->Fill(bpr);
	  }
	  if (r<60){
	    h_data_photon_br_z_pixel_rebin->Fill(br);
	  }
	}
	//	if (fabs(bz) >= 26 ) {
	if ( br<19 && br>3.5 ) {
	//if ( br< 19 ) {
	//if ( br<=20 ) {
	    h_data_photon_z_pixel ->Fill(bz);
	  }
	  h_data_photon_z ->Fill(bz);
	  //	}
	
	if (fabs(data_.z) > 124 ) {
	  if ( br> 22 ) {
	    h_data_photon_z_ZGT124 ->Fill(fabs(data_.z)); 
	  }
	}

	if  (fabs(bz) >20 && fabs(bz) <40 &&  br>12 && br<20  ) {
	  h_data_photon_z_flange ->Fill(bz);
	}
	if (fabs(eta)<1.2){
	  h_data_photon_r->Fill(r);
	  if (r<20){
	    h_data_photon_r_pixel->Fill(rr);
	    h_data_photon_vr_pixel->Fill(vr);
	  }
	  h_data_photon_br->Fill(br);
	  if (r<20){
	    h_data_photon_br_eta_pixel->Fill(br);
	    h_data_photon_br_eta_pixel_beampipe->Fill(rBP);
	  }
								                  
	  h_data_photon_br_eta_barrel->Fill(br);
	  h_data_photon_br_eta_barrel_beampipe->Fill(rBP);

	  if (r<12)
	    h_data_photon_r_pixel_s->Fill(br);
	}
	//if (before_hit<2 && data_.d01*data_.q1>0.1 && data_.d02*data_.q2>0.1){
	if (fabs(eta)<2 && fabs(data_.z)<26 ) {
	  h_data_photon_br_etaz_pixel->Fill(br);
	  h_data_photon_bpr_etaz_pixel->Fill(bpr);
	}
	if (fabs(eta)>.2){
	  h_data_photon_eta_s->Fill(eta);
	  if (fabs(eta)<0.9){
	    //if (r<20)
	    //		  h_data_photon_r_pixel_s->Fill(r);
	  }
	} else if (fabs(data_.minapp)<1. && fabs(map_2pi(data_.iphi1-data_.iphi2))<0.4){
	  h_data_photon_eta_s->Fill(eta);
	  if (fabs(eta)<0.9){
	    //if (r<20)
	    //		  h_data_photon_r_pixel_s->Fill(r);
	  }
	}
      }
    }
  }

  
  std::cout << " candidates in data " << r2_use_entries << " and in MC " << r1_use_entries << std::endl;
  std::cout << " candidates in data forw |z|>28cm and r<=20 " << r2_use_entries_forw << " and in MC forw " << r1_use_entries_forw << std::endl;
  std::cout << " candidates in data forw |z|>28cm " << r2_use_entries_allforw << " and in MC forw " << r1_use_entries_allforw << std::endl;
  std::cout << " candidates in data flange " << r2_use_entries_forw2 << " and in MC flange " << r1_use_entries_forw2 << std::endl;


  if (by_event){
    r1_use_entries = r1_use_events;
    r2_use_entries = r2_use_events;
    std::cout << " Total events in data " << r2_use_entries << " and events in MC " << r1_use_entries << std::endl;
  } else {
  }
  /*
    h_mc_photon_pt_ext->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_pt_fakes_ext->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_dz_s->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_dz_fakes_s->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_phi->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_phi->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_iphi->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_iphi->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_eta->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_eta->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_mass->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_mass->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_mass2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_mass2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakesGT02_mass2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_mass2_vs_r->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_mass2_vs_r->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakesGT02_mass2_vs_r->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_chi2prob->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_chi2prob->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_minapp->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_minapp->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_dcot->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_fakes_dcot->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_l1->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakes_l1->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakesGT02_l1->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_l2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakes_l2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakesGT02_l2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_l3->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakes_l3->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_algo_fakesGT02_l3->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_hits->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_hits_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_chi2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_chi2_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt1->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt1_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt1_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt2->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt2_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt2_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt3->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt3_fakes->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_tk_pt3_fakesGT02->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_d0->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_fakes_d0->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_d0_ext->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_fakes_d0_ext->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_br_z_pixel->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_br_z_fakes_pixel->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_br_etaz_pixel->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_br_etaz_fakes_pixel->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_br_eta_pixel->Scale((double)r2_use_entries/r1_use_entries);
    h_mc_photon_br_eta_fakes_pixel->Scale((double)r2_use_entries/r1_use_entries);
  */
  _fileOut->Write(); // Save all histograms to file
  _fileOut->Close();


  //TCut tk_qualityCut = "(((pt1>2 && nHits1>6)||(pt1<2)) && ((pt2>2 && nHits2>6)||(pt2<2))) && missHits1<2 && missHits2<2";
  TCut tk_qualityCut = "missHits1<2 && missHits2<2";
  TCut vtx_qualityCut = "beforeHits1<2 && beforeHits2<2 && beforeHits1+beforeHits2<3";
  TCut chi2_qualityCut = "chi2prob>0.005";
  TCut eta_qualityCut = "(abs(-log(tan(theta/2.)))>0.2) || (abs(-log(tan(theta/2.)))<0.2 && abs(minapp)<1. )";
  //TCut run_qualityCut = true;
  //"run==132440 || run==132471 || run==132474 || run==132476 || run==132477 || run==132478 || run==132479" ;
  TCut z_qualityCut = "missHits1<2 && missHits2<2";
  TCut minappCut = "minapp<1.";
  TCut xyzrange = "abs(x)<8. && abs(y)<8 && abs(z)<26";
  TCut zrange = "abs(z)> 30";
  TCut xyzrangeLarge = "abs(x)<40. && abs(y)<40 ";
  TCut etaRange = "(abs(-log(tan(theta/2.)))<1.2)";
  TCut allCuts =  chi2_qualityCut&& tk_qualityCut && vtx_qualityCut &&  eta_qualityCut &&   z_qualityCut && minappCut && xyzrange ;
  TCut allCutsEta =  chi2_qualityCut && tk_qualityCut && vtx_qualityCut &&  eta_qualityCut &&    z_qualityCut && minappCut && etaRange ;
  TCut allCutsEtaLarge =  chi2_qualityCut && tk_qualityCut && vtx_qualityCut &&  eta_qualityCut &&    z_qualityCut && minappCut && etaRange && xyzrangeLarge ;
  TCut allCutsZ =  chi2_qualityCut && tk_qualityCut && vtx_qualityCut &&  eta_qualityCut &&    z_qualityCut && minappCut && xyzrange ;
  TCut allCuts2 =  chi2_qualityCut && tk_qualityCut && vtx_qualityCut &&  eta_qualityCut &&   z_qualityCut && minappCut && zrange ;
  TCut allCutsLarge =  chi2_qualityCut && tk_qualityCut && vtx_qualityCut &&  eta_qualityCut &&   z_qualityCut && minappCut && xyzrangeLarge ;

  /*
  c1->cd();
  r2s->Draw("y:x",allCuts);
  TGraph *hConversionRPhiPixelBarrelMCAllCuts = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRPhiPixelBarrelMCAllCuts->SetTitle("xRay in MC ");
  //  hConversionRPhiPixelBarrel->SetMarkerStyle(6);
  hConversionRPhiPixelBarrelMCAllCuts->GetXaxis()->SetTitle("x (cm)");
  hConversionRPhiPixelBarrelMCAllCuts->GetYaxis()->SetTitle("y (cm)");
  hConversionRPhiPixelBarrelMCAllCuts->GetXaxis()->SetRangeUser(-8.0,8.0);
  hConversionRPhiPixelBarrelMCAllCuts->GetYaxis()->SetRangeUser(-8.0,8.0);
  hConversionRPhiPixelBarrelMCAllCuts->Draw("AP");
  TPaveText *textBox1 = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  TString entMCAllCuts;
  entMCAllCuts += "Entries ";
  entMCAllCuts += hConversionRPhiPixelBarrelMCAllCuts->GetN();
  textBox1->AddText(entMCAllCuts);
  textBox1->Draw();
  c1->SaveAs("material_mc_xy_pixels_unbinned.eps");
  c1->SaveAs("material_mc_xy_pixels_unbinned.png");


  c1->cd();
  r2s->Draw("y:x",allCutsLarge);
  TGraph *hConversionRPhiPixelBarrelMCAllCutsLarge = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRPhiPixelBarrelMCAllCutsLarge->SetTitle("xRay in MC ");
  // hConversionRPhiPixelBarrel->SetMarkerStyle(6);
  hConversionRPhiPixelBarrelMCAllCutsLarge->GetXaxis()->SetTitle("x (cm)");
  hConversionRPhiPixelBarrelMCAllCutsLarge->GetYaxis()->SetTitle("y (cm)");
  hConversionRPhiPixelBarrelMCAllCutsLarge->GetXaxis()->SetRangeUser(-40.0,40.0);
  hConversionRPhiPixelBarrelMCAllCutsLarge->GetYaxis()->SetRangeUser(-40.0,40.0);
  hConversionRPhiPixelBarrelMCAllCutsLarge->Draw("AP");
  TPaveText *textBox2 = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  TString entMCAllCutsLarge;
  entMCAllCutsLarge += "Entries ";
  entMCAllCutsLarge += hConversionRPhiPixelBarrelMCAllCutsLarge->GetN();
  textBox2->AddText(entMCAllCutsLarge);
  textBox2->Draw();
  c1->SaveAs("material_mc_xy_all_unbinned.eps");
  c1->SaveAs("material_mc_xy_all_unbinned.png");


  TLatex myText;
  myText.SetTextSize(0.05);

  c1->cd();
  r2s2->Draw("y:x",allCuts);
  TGraph *hConversionRPhiPixelBarrelDataAllCuts = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRPhiPixelBarrelDataAllCuts->SetTitle("");
  //hConversionRPhiPixelBarrel->SetMarkerStyle(6);
  hConversionRPhiPixelBarrelDataAllCuts->GetXaxis()->SetTitle("x (cm)");
  hConversionRPhiPixelBarrelDataAllCuts->GetYaxis()->SetTitle("y (cm)");
  hConversionRPhiPixelBarrelDataAllCuts->GetXaxis()->SetRangeUser(-8.0,8.0);
  hConversionRPhiPixelBarrelDataAllCuts->GetYaxis()->SetRangeUser(-8.0,8.0);
  hConversionRPhiPixelBarrelDataAllCuts->Draw("AP");
  //  TPaveText *textBox = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  TString dataString;
  dataString += "CMS Preliminary 7 TeV ";
  // entString += hConversionRPhiPixelBarrel->GetN();
  //textBox->AddText(entString);
  //textBox->Draw();
  myText.DrawLatex(-7,7.,"CMS Preliminary   #sqrt{s}=7 TeV");
  c1->SaveAs("material_data_xy_pixels_unbinned.png");
  c1->SaveAs("material_data_xy_pixels_unbinned.root");
  c1->SaveAs("material_data_xy_pixels_unbinned.eps");



  c1->cd();
  r2s2->Draw("y:x",allCutsEta);
  TGraph *hConversionRPhiPixelBarrelDataAllCutsEta  = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRPhiPixelBarrelDataAllCutsEta->SetTitle("CMS Preliminary 2010 ");
  //hConversionRPhiPixelBarrel->SetMarkerStyle(6);
  hConversionRPhiPixelBarrelDataAllCutsEta->GetXaxis()->SetTitle("x (cm)");
  hConversionRPhiPixelBarrelDataAllCutsEta->GetYaxis()->SetTitle("y (cm)");
  hConversionRPhiPixelBarrelDataAllCutsEta->GetXaxis()->SetRangeUser(-8.0,8.0);
  hConversionRPhiPixelBarrelDataAllCutsEta->GetYaxis()->SetRangeUser(-8.0,8.0);
  hConversionRPhiPixelBarrelDataAllCutsEta->Draw("AP");
  TPaveText *textBox3 = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  TString dataAllCutsEtaString;
  dataAllCutsEtaString += "Entries ";
  dataAllCutsEtaString += hConversionRPhiPixelBarrelDataAllCutsEta->GetN();
  // textBox3->AddText(dataAllCutsEtaString);
  //textBox3->Draw();
  myText.DrawLatex(-7,7.,"CMS Preliminary   #sqrt{s}=7 TeV");
  c1->SaveAs("material_data_xy_pixels_eta_unbinned.png");


  c1->cd();
  r2s2->Draw("y:x",allCutsEtaLarge);
  TGraph *hConversionRPhiPixelBarrelDataAllCutsEtaLarge  = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRPhiPixelBarrelDataAllCutsEtaLarge->SetTitle("CMS Preliminary 2010 ");
  //hConversionRPhiPixelBarrel->SetMarkerStyle(6);
  hConversionRPhiPixelBarrelDataAllCutsEtaLarge->GetXaxis()->SetTitle("x (cm)");
  hConversionRPhiPixelBarrelDataAllCutsEtaLarge->GetYaxis()->SetTitle("y (cm)");
  hConversionRPhiPixelBarrelDataAllCutsEtaLarge->GetXaxis()->SetRangeUser(-40.0,40.0);
  hConversionRPhiPixelBarrelDataAllCutsEtaLarge->GetYaxis()->SetRangeUser(-40.0,40.0);
  hConversionRPhiPixelBarrelDataAllCutsEtaLarge->Draw("AP");
  TPaveText *textBox4 = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  TString dataAllCutsEtaLargeString;
  dataAllCutsEtaLargeString += "Entries ";
  dataAllCutsEtaLargeString += hConversionRPhiPixelBarrelDataAllCutsEtaLarge->GetN();
  // textBox4->AddText(dataAllCutsEtaLargeString);
  //extBox4->Draw();
  myText.DrawLatex(-35,35.,"CMS Preliminary   #sqrt{s}=7 TeV");
  c1->SaveAs("material_data_xy_eta_unbinned.png");




  c1->cd();
  r2s2->Draw("y:x",allCutsLarge);
  TGraph *hConversionRPhiPixelBarrelDataAllCutsLarge = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRPhiPixelBarrelDataAllCutsLarge->SetTitle("");
  //  hConversionRPhiPixelBarrel->SetMarkerStyle(6);
  hConversionRPhiPixelBarrelDataAllCutsLarge->GetXaxis()->SetTitle("x (cm)");
  hConversionRPhiPixelBarrelDataAllCutsLarge->GetYaxis()->SetTitle("y (cm)");
  hConversionRPhiPixelBarrelDataAllCutsLarge->GetXaxis()->SetRangeUser(-40.0,40.0);
  hConversionRPhiPixelBarrelDataAllCutsLarge->GetYaxis()->SetRangeUser(-40.0,40.0);
  hConversionRPhiPixelBarrelDataAllCutsLarge->Draw("AP");
  //TPaveText *textBox = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  // TString entString;
  //entString += "Entries ";
  //entString += hConversionRPhiPixelBarrel->GetN();
  //textBox->AddText(entString);
  //textBox->Draw();
  myText.DrawLatex(-30,30.,"CMS Preliminary");
  c1->SaveAs("material_data_xy_all_unbinned.eps");
  c1->SaveAs("material_data_xy_all_unbinned.png");



  c2->cd();
  r2s2->Draw("sqrt(x*x+y*y):z",allCutsLarge);
  TGraph *hConversionRZPixelBarrelDataAllCutsLarge = (TGraph*)gPad->GetPrimitive("Graph")->Clone();
  hConversionRZPixelBarrelDataAllCutsLarge->SetTitle("");
  //  hConversionRZPixelBarrel->SetMarkerStyle(6);
  hConversionRZPixelBarrelDataAllCutsLarge->GetXaxis()->SetTitle("x (cm)");
  hConversionRZPixelBarrelDataAllCutsLarge->GetYaxis()->SetTitle("y (cm)");
  hConversionRZPixelBarrelDataAllCutsLarge->GetXaxis()->SetRangeUser(-110.0,110.0);
  hConversionRZPixelBarrelDataAllCutsLarge->GetYaxis()->SetRangeUser(0.0,45.0);
  hConversionRZPixelBarrelDataAllCutsLarge->Draw("AP");
  //TPaveText *textBox = new TPaveText(0.7,0.83,0.95,0.9,"NDC");
  // TString entString;
  //entString += "Entries ";
  //entString += hConversionRZPixelBarrel->GetN();
  //textBox->AddText(entString);
  //textBox->Draw();
  myText.DrawLatex(-30,30.,"CMS Preliminary");
  c2->SaveAs("material_data_rz_all_unbinned.eps");
  c2->SaveAs("material_data_rz_all_unbinned.png");
  */


}
