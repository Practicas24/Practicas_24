
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include <vector>

TEfficiency *principal(std::string name, double distancia)
{
    // Ler
    auto *fin{new TFile(name.c_str())};
    fin->ls();
    // Gardamos
    TEfficiency *ps{fin->Get<TEfficiency>(TString{"eff"})};

    return ps;
}
void Eff()
{   

    // Creamos el vector effs para guardar las eficiencias que luego graficaremos
    std::vector<TEfficiency *> effs;
    for (double i = 0.0; i < 15.5; i += 2)
    {
        double distancia{3 + i}; // cm
        std::string name_aux{TString::Format("simple%.0f", i + 3).Data()};
        std::string name{TString::Format("ps_%s.root", name_aux.c_str()).Data()};

        effs.push_back(principal(name, distancia));
    }

    double distancia{50.0}; // cm
    std::string name_aux{TString::Format("simple%.0f", 50.0).Data()};
    std::string name{TString::Format("ps_%s.root", name_aux.c_str()).Data()};

    effs.push_back(principal(name, distancia));

    // Graficamos
    auto* legend{new TLegend {0.7,0.7,0.95,0.95}};  

    auto* mg {new TMultiGraph};
    mg->SetTitle(";#theta_{CM} [#circ]; #varepsilon");

    std::vector<int> ms {};
    std::vector<double> dists {3.0,5.0,7.0,9.0,11.0,13.0,15.0,17.0,50.0};
    std::vector<double> mk_style {20,21,22,23,33,34,45,47,29};

    double i{0};
    for (auto *eff : effs)
    {
        TGraphAsymmErrors *g{eff->CreateGraph()};

        g->SetMarkerStyle(mk_style[i]);
        g->SetMarkerSize(1.1);
        mg->Add(g);
        legend -> AddEntry(g,TString::Format("%.0f cm",dists[i]));
        i++;
    }

    auto *c0{new TCanvas};
    mg->Draw("apl plc pmc");
    legend->Draw();
}