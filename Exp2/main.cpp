//export ROOTSYS=/opt/local/libexec/root6/
//export LD_LIBRARY_PATH=$ROOTSYS/lib

#include <stdio.h>
#include <iostream>
#include <cmath>

#include "TwoBodyDecay.h"

#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1F.h>
#include <TCanvas.h>

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

    TString rootfname("./data.root");
    TFile* ofile = new TFile(rootfname, "RECREATE");

    TRandom3* gen = new TRandom3();
    gen->SetSeed(0);

    if( !ofile->IsOpen() ) {
        std::cout << "problems creating root file. existing... " << std::endl;
        exit(-1);
    }

    ofile->Close();

    delete event;

    return 0;
    
}
