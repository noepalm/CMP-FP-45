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
#include "TVector3.h"


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
    
    //event->StartDecay();

    //cout << "Invariant mass of K and pi = " << (Pion+Kaon).M() << endl;
    
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

    TTree data_tree();

    //TH1F for truemass
    int nbins=100;
    int xlo=4000;
    int xhi=7000;
    int xloAngle=0;
    int xlhiAngle=10;
    int xloMomentum=2000;
    int xhiMomentum=4000;
    double binwidth = (xhi-xlo) / nbins;
    double binwidthAngle=(xlhiAngle-xloAngle) / nbins;
    double binwidthMomentum=(xhiMomentum-xloMomentum)/nbins;
    double resol=0.10;
    
    std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;
    
    //Variabili TH1F
    
    TH1F htruemass("truemass","distribution of the true mass",nbins,xlo,xhi);
    TH1F hmeasmass("measured-mass","distribution of the measured mass",nbins,xlo,xhi);
    TH1F hopeningAngle("openingAngle","distribution of the opening Angle in the LAB frame",nbins,xloAngle,xlhiAngle);
    TH1F hdxPion("hdxPion","distribution of the momentum measured for the pion",nbins,xloMomentum,xhiMomentum);
    TH1F hdxKaon("hdxKaon","distribution of the momentum measured for the kaon",nbins,xloMomentum,xhiMomentum);
    
    
    int nsig=10000;
    
    
    TRandom3*  gen = new TRandom3();
    gen->SetSeed(0);
    
    for(int i=0;i<nsig;++i){
        //decadimento
        
        TwoBodyDecay *eventi= new TwoBodyDecay(Meson, Pion, Kaon);
        eventi->StartDecay();
        //cosa voglio misurare
        double InvariantMass=(Pion+Kaon).M();
        Double_t openingAngle = Pion.Angle(Kaon.Vect());
        
        double p_pi_0=sqrt(Pion.Px()*Pion.Px()+Pion.Py()*Pion.Py()+Pion.Pz()*Pion.Pz());
        double p_K_0=sqrt(Kaon.Px()*Kaon.Px()+Kaon.Py()*Kaon.Py()+Kaon.Pz()*Kaon.Pz());
        double p_pi_meas=gen->Gaus(p_pi_0, p_pi_0*resol); //misura con accuratezza del 3%
        double p_K_meas=gen->Gaus(p_K_0, p_K_0*resol);// misura con accuratezza del 3%
        //Misuro la massa invariante con l'incertezza
        
        double theta_pi_meas=Pion.Theta();
        double phi_pi_meas=Pion.Phi();
        double theta_K_meas=Kaon.Theta();
        double phi_K_meas=Kaon.Phi();
        
        
        TVector3 direction_pi(Pion.Px()/p_pi_0,Pion.Py()/p_pi_0,Pion.Pz()/p_pi_0);
        TVector3 direction_K(Kaon.Px()/p_K_0,Kaon.Py()/p_K_0,Kaon.Pz()/p_K_0);
        TLorentzVector Pion_meas, K_meas;
        Pion_meas.SetPxPyPzE(direction_pi.X()*p_pi_meas,direction_pi.Y()*p_pi_meas,direction_pi.Z()*p_pi_meas,sqrt(p_pi_meas*p_pi_meas+M_PION*M_PION));
        K_meas.SetPxPyPzE(direction_K.X()*p_K_meas,direction_K.Y()*p_K_meas,direction_K.Z()*p_K_meas,sqrt(p_K_meas*p_K_meas+M_K*M_K));
        
        double  InvariantMass_meas=(Pion_meas+K_meas).M();
        
        /*
         **CONTROLLO DA TERMINALE SUI RISULTATI: ELENCO I VARI PRINT**
         
         //cout<<p_pi_0<<endl;
         //cout<<p_K_0<<endl;
         Pion.Print();
         Pion_meas.Print();
         cout<<"True mass: "<<InvariantMass<<"Invariant mass measured : "<<InvariantMass_meas<<endl;
         
         */
        
        
        
       
        
        
        //riempio gli istogrammi
        htruemass.Fill(InvariantMass);
        hopeningAngle.Fill(openingAngle);
        hdxPion.Fill(p_pi_meas);
        hdxKaon.Fill(p_K_meas);
        hmeasmass.Fill(InvariantMass_meas);
        
        delete eventi;
    }
    
    //Plot istogramma per massa
    
    TCanvas canvTrueMass("canvTrueMass","canvas for plotting",1280,1024);
    htruemass.GetXaxis()->SetTitle("Distribution of the Invariant Mass [MeV]");
    htruemass.Draw();
    canvTrueMass.SaveAs("./true_mass.pdf");
    canvTrueMass.SaveAs("./true_mass.jpg");
    
    htruemass.Write();
    
    
    TCanvas canvMeasMass("canvMeasMass","canvas for plotting",1280,1024);
       hmeasmass.GetXaxis()->SetTitle("Distribution of the Invariant Mass measured [MeV]");
       hmeasmass.Draw();
       canvMeasMass.SaveAs("./measured_mass.pdf");
       canvMeasMass.SaveAs("./measured_mass.jpg");
       
       hmeasmass.Write();
    
    TCanvas canvOverlay("canvOverlay","canvas for plotting", 1280, 1024);
     canvOverlay.Divide(1,2);
     canvOverlay.cd(1);
     hmeasmass.Fit("gaus");
     hmeasmass.Draw();
     canvOverlay.cd(2);
     htruemass.Draw();
     canvOverlay.SaveAs("./invariant-mass.pdf");
    
    //plot istogramma per angolo
    TCanvas canvOpeningAngle("canvOpeningAngle","canvas for plotting",1280,1024);
    hopeningAngle.GetXaxis()->SetTitle("Distribution of the opening angle [degree]");
    hopeningAngle.Draw();
    canvOpeningAngle.SaveAs("./opening_angle.pdf");
    canvOpeningAngle.SaveAs("./opening_angle.jpg");
    
    hopeningAngle.Write();
    
    //plot istogramma per dxPion
    TCanvas canvdxPion("canvdxPion","canvas for plotting",1280,1024);
    hdxPion.GetXaxis()->SetTitle("Distribution of the momentum for the Pion  [Mev]");
    hdxPion.Draw();
    canvdxPion.SaveAs("./p_pi_meas.pdf");
    canvdxPion.SaveAs("./p_pi_meas.jpg");
    
    hdxPion.Write();
    
    //plot istogramma per dxKaon
    
    TCanvas canvdxKaon("canvdxKaon","canvas for plotting",1280,1024);
    hdxKaon.GetXaxis()->SetTitle("Distribution of the momentum for the Kaon [Mev]");
    hdxKaon.Draw();
    canvdxKaon.SaveAs("./p_K_meas.pdf");
    canvdxKaon.SaveAs("./p_K_meas.jpg");
    
    hdxKaon.Write();
    
    
    
    
    
    //FIT
    // A simple example of fitting with predefined functions
    // https://root.cern.ch/root/htmldoc/guides/users-guide/FittingHistograms.html
    // * fit histogram of MEASURED values with Gaussian function
    hdxPion.Fit("gaus");
    hdxPion.Draw();
    canvdxPion.SaveAs("./p_pi_meas_fit.pdf");
    canvdxPion.SaveAs("./p_pi_meas_fit.jpg");
    
    hdxKaon.Fit("gaus");
    hdxKaon.Draw();
    canvdxKaon.SaveAs("./p_K_meas_fit.pdf");
    canvdxKaon.SaveAs("./p_K_meas_fit.jpg");
    
    
    
    delete event;

    rfile.Close();
    
    return 0;
    
}

