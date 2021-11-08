//export ROOTSYS=/opt/local/libexec/root6/
//export LD_LIBRARY_PATH=$ROOTSYS/lib

#include <stdio.h>
#include <iostream>
#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include <cmath>
#include "Particle.h"
#include "TwoBodyDecay.h"

//Let's define mass and momentum of the particles [MeV]
#define M_B 5279
#define M_PION 140
#define M_K 500

#define P_B 300 //along the x-axis

using namespace std;

int main(){
    
    Particle *Meson = new Particle("B",M_B,P_B,0,0);
    Particle *Pion = new Particle("π",M_PION,0,0,0);
    Particle *Kaon = new Particle("k",M_K,0,0,0);
    
    TwoBodyDecay *event= new TwoBodyDecay(*Meson,*Pion,*Kaon);
    
    Meson->print();
    Pion->print();
    Kaon->print();
    
    
    
    event->StartDecay(*Meson,*Pion,*Kaon);
    
    delete Meson;
    delete Pion;
    delete Kaon;
    

    return 0;
    
}
