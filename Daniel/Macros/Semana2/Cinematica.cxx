#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Clases.cxx"

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
    double m1{colision.get_m1()*938};
    double m2{colision.get_m2()*938};
    double m3{colision.get_m3()*938};
    double m4{colision.get_m4()*938};
    double t1{colision.get_tbeam()};

    double E1{m1+t1};
    double p1{pow(pow(E1,2)-pow(m1,2),0.5)};
    double E2{m2};
    double Etot{E1+m2};
    double Etotp{pow(pow(Etot,2)-pow(p1,2),0.5)};

    double gamma{Etot/Etotp};
    double beta{p1/Etot};
    
    
    double E3p{(Etotp+(pow(m3,2)-pow(m4,2))/Etotp)/2};
    double E4p{(Etotp+(pow(m4,2)-pow(m3,2))/Etotp)/2};

    double p4p{pow(pow(E4p,2)-pow(m4,2),0.5)};

    double E4{gamma*(E4p+beta*p4p*TMath::Cos(theta4p))};

    double T4 {E4-m4};

    return T4;
}

double theta4(Colision colision,double theta4p){    
    double m1{colision.get_m1()*938};
    double m2{colision.get_m2()*938};
    double m3{colision.get_m3()*938};
    double m4{colision.get_m4()*938};
    double t1{colision.get_tbeam()};

    double E1{m1+t1};
    double p1{pow(pow(E1,2)-pow(m1,2),0.5)};
    double E2{m2};
    double Etot{E1+m2};
    double Etotp{pow(pow(Etot,2)-pow(p1,2),0.5)};

    double gamma{Etot/Etotp};
    double beta{p1/Etot};
    
    double E3p{(Etotp+(pow(m3,2)-pow(m4,2))/Etotp)/2};
    double E4p{(Etotp+(pow(m4,2)-pow(m3,2))/Etotp)/2};

    double p4p{pow(pow(E4p,2)-pow(m4,2),0.5)};

    double E4{gamma*(E4p+beta*p4p*TMath::Cos(theta4p))};
    double p4{pow(pow(m4,2)+pow(E4,2),0.5)};
 
    double theta4 {TMath::ACos((gamma/p4)*(p4p*TMath::Cos(theta4p)+beta*E4))};

    return theta4;
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
    colision.energia(7.5*12);

    //

    
auto* Li10{new ActPhysics::Kinematics("11Li","d","t","10Li",12*7.5)};
auto* g3Li10{Li10 -> GetKinematicLine3()};
auto* g4Li10{Li10 -> GetKinematicLine4()};

auto* canvas10{new TCanvas {"canvas10","Li10"}};
auto* gother {new TGraph};

gother->SetPoint(gother->GetN(), 5, 5);
gother->SetPoint(gother->GetN(), 50, 25);
for (int i=0;i<100000;i++){
    auto theta4p{gRandom->Uniform(0,TMath::Pi())};
    auto Theta4{theta4(colision,theta4p)};
    auto T4{t4(colision,theta4p)};
    gother->SetPoint(gother->GetN(), Theta4*180/TMath::Pi(),T4);
}
g3Li10 -> Draw("al");
g4Li10 -> Draw("l");
g4Li10->SetLineColor(kOrange);
g4Li10->SetLineWidth(4);

gother->SetPoint(gother->GetN(), 5, 5);
gother->SetPoint(gother->GetN(), 50, 25);
gother->Draw("pl");
gother->SetLineWidth(2);
gother->SetLineColor(kRed);
gother->SetMarkerStyle(24);
gother->SetMarkerColor(kBlue);


}
