#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TLegend.h"

#include <vector>

TGraphErrors *principal(std::string name, double distancia)
{
    // Ler
    auto *fin{new TFile(name.c_str())};
    fin->ls();
    // Gardamos
    std::vector<TH1D *> ps;
    for (int p = 0; p < fin->GetListOfKeys()->GetSize() - 1; p++)
        ps.push_back(fin->Get<TH1D>(TString::Format("p%d", p)));
    auto *gother{new TGraphErrors};

    auto *c0{new TCanvas("c0", "Projections")};
    c0->DivideSquare(ps.size());

    for (int i = 0; i < ps.size(); i++)
    {
        c0->cd(i + 1);
        ps[i]->GetXaxis()->SetRangeUser(13, 19);
        ps[i]->Fit("gaus", "Q");
        auto *func{ps[i]->GetFunction("gaus")};
        if (i == 4)
        {
            gPad->SaveAs(TString::Format("/home/daniel/GitHub/Practicas_24/Daniel/Macros/Memoria/Figura/%.f_fit.eps", distancia));
        }
        gother->SetPoint(gother->GetN(), i * 2 + 41, func->GetParameter(2));
        gother->SetPointError(gother->GetN() - 1, 0, func->GetParError(2));
    }

    c0->SaveAs(TString::Format("./Eps_figure_fit/%.f_fit.eps", distancia));
    return gother;
}
void fit()
{
    std::vector<TGraphErrors *> gother_vector;
    for (double i = 0.0; i < 15.5; i += 2)
    {

        double distancia{3 + i}; // cm
        std::string name_aux{TString::Format("simple%.0f", i + 3).Data()};
        std::string name{TString::Format("ps_%s.root", name_aux.c_str()).Data()};

        gother_vector.push_back(principal(name, distancia));
    }

    auto *legend{new TLegend{0.7, 0.7, 0.95, 0.95}};

    auto *mg{new TMultiGraph};
    mg->SetTitle(";E [MeV];#sigma [#circ]");
    // Format
    std::vector<int> ms{};
    std::vector<double> dists{3, 5, 7, 9, 11, 13, 15, 17};
    std::vector<double> mk_style{20, 21, 22, 23, 33, 34, 45, 47};
    int i{0};
    for (auto *g : gother_vector)
    {

        g->SetMarkerStyle(mk_style[i]);
        g->SetMarkerSize(1.3);
        mg->Add(g);
        legend->AddEntry(g, TString::Format("%.0f cm", dists[i]));
        i += 1;
    }

    gStyle->SetPalette(kCool);
    auto *c1{new TCanvas("c1", "sigma_projections")};
    mg->Draw("apl plc pmc");
    legend->Draw();
}
