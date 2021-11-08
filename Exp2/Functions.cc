#include <iostream>
#include "TRandom3.h"
#include <cmath>

double genTheta(){
    TRandom3 *r = new TRandom3(0);
    Double_t rho = 1;
    Double_t x = 0, y = 0, z = 0;
    //Genero theta
    r->Sphere(x, y, z, rho);
    Double_t thetaS=acos(z)*360/(2*M_PI);
   
    return thetaS;
    delete r;
    
};

double genPhi(){
    TRandom3 *r = new TRandom3(0);
    Double_t rho = 1;
    Double_t x = 0, y = 0, z = 0;
    //Genero Phi
    r->Sphere(x, y, z, rho);
    Double_t phiS=atan2(y,x)*360/(2*M_PI); //restituisce in radianti
    return phiS;
    delete r;
    
};
