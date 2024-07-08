#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"

#include <vector>

TGraphErrors *principal(std::string name, double distancia)
{
    // Ler
    auto *fin{new TFile("projections.root")};
    // Gardamos
    std::vector<TH1D *> ps;
    for (int p = 0; p < fin->GetListOfKeys()->GetSize(); p++)
        ps.push_back(fin->Get<TH1D>(name));

    auto *gother{new TGraphErrors};

    // auto *c0{new TCanvas("c0", "Projections")};
    // c0->DivideSquare(ps.size());

    for (int i = 0; i < ps.size(); i++)
    {
        //   c0->cd(i + 1);
        ps[i]->Fit("gaus", "Q", "N");
        auto *func{ps[i]->GetFunction("gaus")};
        gother->SetPoint(gother->GetN(), i + 1, func->GetParameter(2));
        gother->SetPointError(gother->GetN() - 1, 0, func->GetParError(2));
    }
    gother->SetMarkerStyle(24);
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

    auto *c1{new TCanvas("c1", "sigma_projections")};

    gother_vector[0]->draw("ap");
    for (int p = 1; p < gother_vector.size(); p++)
    {
        gother_vector[p]->draw("p");
    }
}
