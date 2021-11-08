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
    
    
    cout << "Starting invariant mass = " << (Pion+Kaon).M() << endl;
    event->StartDecay();
    cout << "Invariant mass of K and pi = " << (Pion+Kaon).M() << endl;

    delete event;

    return 0;
    
}
