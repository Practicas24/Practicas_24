#include "ActSRIM.h"

#include "TGraph.h"

void srim()
{
    // Creas a variable
    ActPhysics::SRIM srim;
    // Les as táboas
    srim.ReadTable("beam", "../SRIM/11Li_mixture_900mbar.txt");
    srim.ReadTable("light", "../SRIM/3H_mixture_900mbar.txt");
    // A función anterior funciona do seguinte xeito:
    // O primeiro arg é unha key, unha label, do xeito que podes identificar cada táboa facilmente
    // O segundo é o ficheiro producido por SRIM. Podes botarlle un ollo, aínda que xa chos calculei eu par que non o
    // fagas ti

    // E aquí como se usan as funcións, tal e como tes no guión:
    srim.EvalDirect("beam", 56);
    srim.Slow("light", 20, 86);
    // As unidades son as seguintes:
    // As enerxías son sempre CINÉTICAS e en MeV
    // As distancias sempre en mm
    // Os ángulos sempre en rad

    // O que che pido que fagas é :
    auto* gl {new TGraph};
    gl->SetTitle("Eloss vs distance;dist [mm];dE/dx [MeV]");
    gl->SetMarkerStyle(6);
    auto* gt {new TGraph};
    gt->SetTitle("Eloss vs energy;T [MeV];dE/dx [MeV]");

    // Enerxía inicial
    double Tini {80}; // MeV
    double Tit {Tini};

    // Rango inicial
    double Rini {srim.EvalDirect("beam", Tini)}; // escolle a partícula (táboa) que queiras
    double rstep {0.1};                            // Definimos un step de 1 mm

    for(double r = 0; r < Rini; r += rstep)
    {
        // 1-> Aplicas a función slow no step con Tit
        auto Taux {srim.Slow("beam", Tit, rstep)};
        // 2-> Calcuals a diff do resultado respeito a Tit
        auto diff {Tit - Taux};
        // 3-> Enches os gráficos
        gl->SetPoint(gl->GetN(), r, diff);
        // 4-> Actualizas Tit co valor slowed
        Tit = Taux;
    }
    srim.Draw("inverse");

    // Representas graficamente nun TCanvas con dous pads
    // gl->Draw("alp");
}
