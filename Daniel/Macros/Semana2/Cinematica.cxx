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


// Vamos a crear las funciones que usaremos despues para obtener los  resultados

double t4(Colision colision, double theta4p)
{
    double m1 {colision.get_m1() * 938};
    double m2 {colision.get_m2() * 938};
    double m3 {colision.get_m3() * 938};
    double m4 {colision.get_m4() * 938};
    double t1 {colision.get_tbeam()};

    double E1 {m1 + t1};
    double p1 {pow(pow(E1, 2) - pow(m1, 2), 0.5)};
    double E2 {m2};
    double Etot {E1 + m2};
    double Etotp {pow(pow(Etot, 2) - pow(p1, 2), 0.5)};

    double gamma {Etot / Etotp};
    double beta {p1 / Etot};


    double E3p {(Etotp + (pow(m3, 2) - pow(m4, 2)) / Etotp) / 2};
    double E4p {(Etotp + (pow(m4, 2) - pow(m3, 2)) / Etotp) / 2};

    double p4p {pow(pow(E4p, 2) - pow(m4, 2), 0.5)};

    double E4 {gamma * (E4p + beta * p4p * TMath::Cos(theta4p))};

    double T4 {E4 - m4};

    return T4;
}

double theta4(Colision colision, double theta4p)
{
    double m1 {colision.get_m1() * 931.494};
    double m2 {colision.get_m2() * 931.494};
    double m3 {colision.get_m3() * 931.494};
    double m4 {colision.get_m4() * 931.494};
    double t1 {colision.get_tbeam()};
    // std::cout << "m4 : " << m4 << '\n';

    double E1 {m1 + t1};
    double p1 {pow(pow(E1, 2) - pow(m1, 2), 0.5)};
    // std::cout << "E1 : " << E1 << '\n';
    // std::cout << "p1 : " << p1 << '\n';
    double E2 {m2};
    double Etot {E1 + m2};
    double Etotp {pow(pow(Etot, 2) - pow(p1, 2), 0.5)};

    double gamma {Etot / Etotp};
    double beta {p1 / Etot};
    // std::cout << "Beta : " << beta << '\n';
    // std::cout << "Gamma : " << gamma << '\n';

    // double E3p {(Etotp + (pow(m3, 2) - pow(m4, 2)) / Etotp) / 2};
    double E4p {(Etotp + (pow(m4, 2) - pow(m3, 2)) / Etotp) / 2};

    double p4p {pow(pow(E4p, 2) - pow(m4, 2), 0.5)};

    double E4 {gamma * (E4p + beta * p4p * TMath::Cos(theta4p))};
    double p4 {pow(-pow(m4, 2) + pow(E4, 2), 0.5)};
    // std::cout << "p4 : " << p4 << '\n';
    // std::cout << "E4 : " << E4 << '\n';
    // std::cout << "diff : " << E4 - p4 << '\n';

    double theta4 {TMath::ACos((gamma / p4) * (p4p * TMath::Cos(theta4p) + beta * E4p))};
    // std::cout << "theta4 : " << theta4 << '\n';

    return theta4;
}

double theta4cm(Colision colision, double theta4cm)
{
    return 2;
}

// Función principal

void Cinematica()
{
    // Definimos las partículas
    Particula li11;
    Particula li12;
    Particula d;
    Particula p;

    // Detallamos las partículas
    li11.definir_MZ(11, 3);
    li11.Print();
    li12.definir_MZ(12, 3);
    d.definir_MZ(2, 1);
    p.definir_MZ(1, 1);

    // Definimos la colisión y la detallamos
    Colision colision {};
    colision.introducir_particulas(li11, d, p, li12);
    colision.energia(7.5 * 12);

    colision.GetParticle1().Print();


    auto* Li12 {new ActPhysics::Kinematics("11Li", "d", "p", 12 * 7.5)};
    auto* g3Li12 {Li12->GetKinematicLine3()};
    auto* g4Li12 {Li12->GetKinematicLine4()};

    auto* gother {new TGraph};

    for(double thetaCM = 0; thetaCM <= 180; thetaCM += 1)
    {
        auto Theta4 {theta4(colision, thetaCM * TMath::DegToRad())};
        auto T4 {t4(colision, thetaCM * TMath::DegToRad())};
        // std::cout << "Theta4: " << Theta4 << " T4 : " << T4 << '\n';
        if(std::isfinite(Theta4) && std::isfinite(T4))
            gother->SetPoint(gother->GetN(), Theta4 * TMath::RadToDeg(), T4);
    }
    // g3Li10 -> Draw("al");
    auto* canvas12 {new TCanvas {"canvas10", "Li10"}};
    canvas12->DivideSquare(2);
    canvas12->cd(1);
    g4Li12->SetLineColor(kOrange);
    g4Li12->SetLineWidth(4);
    g4Li12->Draw("al");

    canvas12->cd(2);
    gother->SetLineWidth(2);
    gother->SetLineColor(kRed);
    gother->SetMarkerStyle(24);
    gother->SetMarkerColor(kBlue);
    gother->Draw("apl");
}
