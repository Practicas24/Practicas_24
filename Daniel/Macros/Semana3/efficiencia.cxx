
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
    for (int p = 0; p < fin->GetListOfKeys()->GetSize(); p++)
        ps.push_back(fin->Get<TH1D>(TString::Format("p%d",p)));

    auto *gother{new TGraphErrors};

    auto *c0{new TCanvas("c0", "Projections")};
    c0->DivideSquare(ps.size());

    for (int i = 0; i < ps.size(); i++)
    {
        c0->cd(i + 1);
        ps[i]->Fit("gaus", "Q");
        auto *func{ps[i]->GetFunction("gaus")};
        gother->SetPoint(gother->GetN(), i*2+41, func->GetParameter(2));
        gother->SetPointError(gother->GetN() - 1, 0, func->GetParError(2));
    }
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
}