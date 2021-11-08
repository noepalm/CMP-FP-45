//export ROOTSYS=/opt/local/libexec/root6/
//export LD_LIBRARY_PATH=$ROOTSYS/lib

#include <stdio.h>
#include <iostream>
#include <cmath>

#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1F.h>
#include <TCanvas.h>

#include "TwoBodyDecay.h"

//Let's define mass and momentum of the particles [MeV]
#define M_B 5279
#define M_PION 140
#define M_K 500

#define P_B 300 //along the x-axis

using namespace std;

int main(){
   
  TLorentzVector Meson, Pion, Kaon;
  Meson.SetPxPyPzE(P_B,0,0,sqrt(M_B*M_B + P_B*P_B));
  Pion.SetPxPyPzE(0,0,0, M_PION);
  Kaon.SetPxPyPzE(0,0,0, M_K);
   
  TwoBodyDecay *event= new TwoBodyDecay(Meson, Pion, Kaon);
   
  event->StartDecay();

  cout << "Invariant mass of K and pi = " << (Pion+Kaon).M() << endl;
   
  // Open TFile for output
  TString rootfname("./output.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
   std::cout << "problems creating root file. existing... " << std::endl;
   exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;
   
  //TH1F for truemass
  int nbins=100;
  int xlo=4000;
  int xhi=7000;
  double binwidth = (xhi-xlo) / nbins;
  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;
  TH1F htruemass("truemass","distribution of the true mass",nbins,xlo,xhi);
   
   
  int nsig=10000;
   
   
  for(int i=0;i<nsig;++i){
    TwoBodyDecay *eventi= new TwoBodyDecay(Meson, Pion, Kaon);
    eventi->StartDecay();
    double InvariantMass=(Pion+Kaon).M();
    htruemass.Fill(InvariantMass);
    delete eventi;
  }
   
  TCanvas canvTrueMass("canvTrueMass","canvas for plotting",1280,1024);
  htruemass.GetXaxis()->SetTitle("Distribution of the Invariant Mass [MeV]");
  htruemass.Draw();
  canvTrueMass.SaveAs("./true_mass.pdf");
  canvTrueMass.SaveAs("./true_mass.jpg");
   
  htruemass.Write();
   
   
  delete event;

  rfile.Close();
   
  return 0;
   
}