#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "ActKinematics.h"

#include "Rtypes.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h" 
#include "TH2.h"
#include "TRandom.h"


// Vamos a crear las funciones que usaremos despues para obtener los  resultados

double t4(Colision colision,double theta4p){
    double m1{colision.get_m1()};
    double m2{colision.get_m2()};
    double m3{colision.get_m3()};
    double m4{colision.get_m4()};
    double t1{colision.get_tbeam()};

    double p1{t1/TMath::C()};
    double E1{pow(TMath::C(),2)*m1+t1};
    double E2{pow(TMath::C(),2)*m2};
    double Etot{E1+m1*TMath::C()};
    double Etotp{pow(pow(Etot,2)-pow(TMath::C()*p1,2),0.5)};

    double gamma{Etot/Etotp};
    double beta{p1/Etotp};
    
    double E3p{(Etotp+(pow(m3*pow(TMath::C(),2),2)-pow(m4*pow(TMath::C(),2),2))/Etotp)/2};
    double E4p{(Etotp+(pow(m4*pow(TMath::C(),2),2)-pow(m3*pow(TMath::C(),2),2))/Etotp)/2};

    double p4p{pow(pow(E/TMath::C(),2)-pow(m4*pow(TMath::C(),2),2),0.5)};

    double E4{gamma*(E3p+beta*p4p*TMath::ACos(theta4p)*TMath::C())};

    double T4 {E4-pow(TMath::C(),2)*pow(m4,1)};

    return T4
}

double theta4cm(Colision colision, double theta4cm){
    return 2;
}

// Función principal

void Cinematica(){
    // Definimos las partículas
    Particula li11;
    Particula li12;
    Particula d;
    Particula p;
    
    // Detallamos las partículas
    li11.definir_MZ(11,3);
    li12.definir_MZ(12,3);
    d.definir_MZ(2,1);
    p.definir_MZ(1,1);

    // Definimos la colisión y la detallamos
    Colision colision{};
    colision.introducir_particulas(li11,d,p,li12);
    colision.energia(7.5*12*);

    //

    
auto* Li10{new ActPhysics::Kinematics("11Li","d","t","10Li",12*7.5)};
auto* g3Li10{Li10 -> GetKinematicLine3()};
auto* g4Li10{Li10 -> GetKinematicLine4()};

auto* canvas10{new TCanvas {"Li10","Li10"}};
auto* T4 {new TGraph}; // sen argumentos

g3Li10 -> Draw("al");
g4Li10 -> Draw("l");

for (int i=0;i<100000;i++){
    auto theta4p{gRandom->Uniform(-TMath::Pi(),TMath::Pi())};


    gother->SetPoint(gother->GetN(), theta4p, t4(colision,theta4p));

}

gother->Draw("pl")

};
