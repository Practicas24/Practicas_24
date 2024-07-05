#include "ActGeometry.h"
#include "ActSRIM.h"
#include "ActKinematics.h"

#include "Math/Point3D.h"
#include "Math/Vector3D.h"

#include "Rtypes.h"
#include "TStyle.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"
#include "Math/Point3D.h"
#include "Math/Vector3D.h"

#include "../Semana2/Clases.cxx"


double ApplyStraggling(ActPhysics::SRIM* srim, std::string which, double Tini, double dist){

double Rini{srim->EvalRange(which,Tini)};
double uini{srim->EvalLongStraggling(which,Rini)};

double Rleft{Rini-dist};
double uleft{srim->EvalLongStraggling(which,Rleft)};

double udist{TMath::Sqrt(TMath::Power(uini,2)-TMath::Power(uleft,2))};

double d{gRandom->Gaus(dist,udist)};

double Rleftnew{Rini-d};

double Tnew{srim->EvalEnergy(which,Rleftnew)};

return Tnew;
}

double ApplyResolution(double dE){
return gRandom->Gaus(dE,(0.0213*TMath::Sqrt(dE))/(2.35));
}


void Simulacion_2()
{

    ActPhysics::SRIM srim;  // &srim -> asi se ''hace'' un pointer

    srim.ReadTable("beam", "/home/daniel/GitHub/Practicas_24/SRIM/11Li_mixture_900mbar.txt");
    srim.ReadTable("heavy", "/home/daniel/GitHub/Practicas_24/SRIM/12Li_mixture_900mbar.txt");
    srim.ReadTable("heavySil", "/home/daniel/GitHub/Practicas_24/SRIM/12Li_silicon.txt");

    // Hay inconsistencias entre diferentes valores en el main.pdf (10 cm, luego 10.4 cm; 255 cm para Z, luego 256 cm)

    // Una vez creado la geometria (simple.root) en la carpeta de Geometria, podemos calcular nuestra simulacion.
    // Primero creamos la variable geo que nos permite leer el archivo que guarda la geometría

    auto *geo{new ActSim::Geometry};

    // Lemos o ficheiro de configuración
    // Tras crealo previamente
    geo->ReadGeometry("Geometria/", "simple");

    // Ahora tengo que implementar las variables aleatorias que cree (y verifique) en el macro Simulacion_1.cxx. En ese caso:

    // Detallamos las partículas

    Particula li11;
    Particula li10;
    Particula li12;
    Particula t;
    Particula d;
    Particula p;

    li12.definir_AZ(12, 3, 12);
    li11.definir_AZ(11, 3, 11.0437236);
    li10.definir_AZ(10, 3, 10.035483);
    d.definir_AZ(2, 1, 2.01410177784);
    t.definir_AZ(3, 1, 3.01604928132);
    p.definir_AZ(1, 1, 1);

    // Tamaños de la caja
    double xACTAR{256}; // Esta en mm
    double yACTAR{256}; // Esta en mm
    double zACTAR{255}; // Esta en mm

    // Grosor del detector

    double zSil{1.5}; // Esta en mm

    // Energía inicial
    double Tbeam{11 * 7.5};

    // Definimos las variables histogramas. La primera -> energía de entrada al detector; La segunda -> energía perdida en el detector
    auto *histo_T{new TH2D{"histo_T", "T_{4} vs #theta;#theta_{4};T;Contas", 220, 0, 60, 220, 0, 100}};
    auto *histo_DT{new TH2D{"histo_DT", "#Delta T_{4} vs #theta;#theta_{4};#Delta T;Contas", 150, 0, 60, 220, 0, 100}};
    auto *hSilDist{new TH1D{"hSilDist", "SilDist Histograma ;SilDist [mm]", 150, 0, 500}};
    auto *hT1{new TH1D{"hT1", "T1 vertice; T_{1} [MeV]", 70, 70, 90}};
    auto *hT4c{new TH2D{"hT4c", "T_{4} vertice vs #theta;#theta_{4};T_{4};Contas", 150, 0, 30, 220, 0, 100}};
    // Definimos la normal
    ROOT::Math::XYZVector normal{1, 0, 0};

    for (int i = 0; i < 200000; i += 1)
    {

        ROOT::Math::XYZPoint verticeCentrado{
            gRandom->Uniform(-xACTAR / 2, xACTAR / 2) * 0.1,
            gRandom->Gaus(0, 5) * 0.1,
            gRandom->Gaus(0, 5) * 0.1
        };

        ROOT::Math::XYZPoint verticeUsual{verticeCentrado.X() * 10 + xACTAR / 2,
                                          verticeCentrado.Y() * 10 + yACTAR / 2,
                                          verticeCentrado.Z() * 10 + zACTAR / 2};

        auto r{verticeUsual.X()};

        // auto theta{TMath::ATan(r/x_uniform)*TMath::RadToDeg()};
        // auto phi{TMath::ATan(y_gauss/z_gauss)*TMath::RadToDeg()};

        auto theta4_cm{gRandom->Uniform(0, 2 * TMath::Pi())};
        auto phi{gRandom->Uniform(0, 2 * TMath::Pi())};

        //  std::cout << phi << "\n";

        // Calculamos la energia

        auto T1new{srim.Slow("beam", Tbeam, r, 0 * TMath::DegToRad())};

        hT1->Fill(T1new);

        auto [T4, theta4_lab]{valores4(li11, d, t, li10, T1new, theta4_cm)};
        // std::cout << "Theta4: " << Theta4 << " T4 : " << T4 << '\n';
        if (!(std::isfinite(theta4_lab) && std::isfinite(T4)))
            continue;

        // 2-> Creamos los angulos
        ROOT::Math::XYZVector direccion{TMath::Cos(theta4_lab), TMath::Sin(theta4_lab) * TMath::Sin(phi), TMath::Sin(theta4_lab) * TMath::Cos(phi)};

        bool SilLado{};                  // No se que es esto (??)
        double SilDist{};                // Distancia desde el vertice hasta el punto de impacto
        int SilTipo{};                   // TIpo de silicio
        int SilIndice{};                 // Indice del silicio
        ROOT::Math::XYZPoint SilPunto{}; // Punto de impacto

        geo->PropagateTrackToSiliconArray(verticeCentrado, direccion, 0, SilLado, SilDist, SilTipo, SilIndice, SilPunto);

        SilDist *= 10; // Convertimos la distancai de cm a mm
        if (SilIndice != -1)
        {
            hSilDist->Fill(SilDist);
            // std::cout <<T4<<"\n";
            double thetaSi{TMath::ACos(direccion.Dot(normal))};

            double T4in0{srim.Slow("heavy", T4, SilDist, 0 * TMath::DegToRad())};
            double T4in1{ApplyStraggling(&srim, "heavy",T4in0,SilDist)};

            if (T4in1 == 0.0)
            {
                std::cout << SilDist << "\n";
            }
            double T4out{srim.Slow("heavySil", T4in1, zSil, thetaSi * TMath::DegToRad())};
            histo_T->Fill(thetaSi*TMath::RadToDeg(), T4in1);
            double dT{ApplyResolution(T4in1 - T4out)};
            histo_DT->Fill(thetaSi*TMath::RadToDeg(),dT);
            double T4vertix{srim.EvalInitialEnergy("heavy",dT,SilDist)};
            hT4c->Fill(thetaSi*TMath::RadToDeg(),T4vertix);
        }
    }

    std::cout <<      srim.Slow("beam", Tbeam, xACTAR/2, 0 * TMath::DegToRad()) << "\n";
    auto* Li10 {new ActPhysics::Kinematics("11Li", "d", "t", srim.Slow("beam", Tbeam, xACTAR*2/3, 0 * TMath::DegToRad()))}; // para que coincida debemos cambiar el 2/3 a un valor mas grande, ya que las particulas que llegan a impartar se encuentran muy proximas al silicio. 
    auto* g4Li10 {Li10->GetKinematicLine4()};


    gStyle->SetPalette(kCool);
    auto *c0{new TCanvas{"c0", "T4_vs_theta"}};
    c0->DivideSquare(6);
    c0->cd(1);
    histo_T->Draw("colz");
    c0->cd(2);
    histo_DT->Draw("colz");
    c0->cd(3);
    hT1->Draw("colz");
    c0->cd(4);
    hSilDist->Draw();
    c0->cd(5);
    g4Li10->SetLineColor(kOrange);
    g4Li10->SetLineWidth(4);
    hT4c->Draw("colz");
    g4Li10->Draw("l");
    // Problema: Se va la energía a cero ¿Es normal?
}