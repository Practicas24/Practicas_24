#include "ActKinematics.h"

#include "Rtypes.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "Clases.cxx"



// Función principal

void Cinematica()
{
    // Definimos las partículas
    Particula li11;
    Particula li10;
    Particula d;
    Particula t;

    // Detallamos las partículas
    li11.definir_AZ(11, 3,11.0437236);
    li10.definir_AZ(10, 3,10.035483);
    d.definir_AZ(2, 1,2.01410177784);
    t.definir_AZ(3, 1,3.01604928132);

    // Definimos la colisión y la detallamos
    Colision colision {};
    colision.set_particulas(li11, d, t, li10);
    colision.set_energia(7.5*12);

    // colision.GetParticle1().Print();


    auto* Li10 {new ActPhysics::Kinematics("11Li", "d", "t", 12 * 7.5)};
    auto* g3Li10 {Li10->GetKinematicLine3()};
    auto* g4Li10 {Li10->GetKinematicLine4()};

    auto* gother10 {new TGraph};
    auto* gother3 {new TGraph};


    for(double thetaCM = 0; thetaCM <= 180; thetaCM += 1)
    {   
        auto [T3,Theta3] {valores3(li11, d, t, li10, 7.5 * 12,thetaCM * TMath::DegToRad())};
        auto [T4,Theta4] {valores4(li11, d, t, li10, 7.5 * 12,thetaCM * TMath::DegToRad())};
        // std::cout << "Theta4: " << Theta4 << " T4 : " << T4 << '\n';
        if(std::isfinite(Theta4) && std::isfinite(T4))
            gother10->SetPoint(gother10->GetN(), Theta4 * TMath::RadToDeg(), T4);
        if(std::isfinite(Theta3) && std::isfinite(T3))
            gother3->SetPoint(gother3->GetN(), Theta3 * TMath::RadToDeg(), T3);
    }
    // g3Li10 -> Draw("al");
    auto* canvas10 {new TCanvas {"canvas10", "Li10"}};
    canvas10->DivideSquare(4);
    canvas10->cd(1);
    g4Li10->SetLineColor(kOrange);
    g4Li10->SetLineWidth(4);
    g4Li10->SetTitle("Cinematica para 11Li(d,t);#theta_{4Lab} [#circ];E_{4Lab}");
    g4Li10->Draw("al");

    canvas10->cd(2);
    gother10->SetLineWidth(4);
    gother10->SetLineColor(kRed);
    gother10->SetTitle("Cinematica para 11Li(d,t);#theta_{4Lab} [#circ];E_{4Lab}");
    gother10->Draw("al");

    gPad->SaveAs(TString::Format("/home/daniel/GitHub/Practicas_24/Daniel/Macros/Memoria/Figura/Cinematica11Li.eps"));



    canvas10->cd(3);
    g3Li10->SetLineColor(kOrange);
    g3Li10->SetLineWidth(4);
    g3Li10->SetTitle("Cinematica para 11Li(d,t);#theta_{3Lab} [#circ];E_{3Lab}");
    g3Li10->Draw("al");

    canvas10->cd(4);
    gother3->SetLineWidth(4);
    gother3->SetLineColor(kRed);
    gother3->SetTitle("Cinematica para 11Li(d,t);#theta_{3Lab} [#circ];E_{3Lab}");
    gother3->Draw("al");

    gPad->SaveAs(TString::Format("/home/daniel/GitHub/Practicas_24/Daniel/Macros/Memoria/Figura/CinematicaH.eps"));

}

