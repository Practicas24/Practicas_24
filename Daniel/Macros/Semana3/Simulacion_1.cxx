#include "ActSRIM.h"
#include "ActKinematics.h"
#include "ActGeometry.h"

#include "Math/Point3D.h"
#include "Math/Vector3D.h"

#include "Rtypes.h"
#include "../Semana2/Clases.cxx"

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

//#include "Math/Vector"

void Simulacion_1() {
double xACTAR{256}; // Esta en mm
double yACTAR{256}; // Esta en mm
double zACTAR{255}; // Esta en mm

auto* histo_xy {new TH2D {"XY","Histo 2D;X;Y;Contas",256,-xACTAR/2,xACTAR/2,256,-yACTAR/2,yACTAR/2}};
auto* histo_zy {new TH2D {"ZY","Histo 2D;Z;Y;Contas",255,-zACTAR/2,zACTAR/2,256,-yACTAR/2,yACTAR/2}};

auto* histo_theta4cm {new TH1D {"theta4cm","Histo 1D",180,-180,180}};
auto* histo_phi4cm {new TH1D {"phi4cm","Histo 1D",180,-180,180}};

auto* histo_T4{new TH2D{"T4", "Histo 2D; #theta_4; #T_4",100,0,0.5,100,0,100}};

Particula li11;
Particula li10;
Particula d;
Particula t;

// Detallamos las partículas
li11.definir_AZ(11, 3,11.0437236);
li10.definir_AZ(10, 3,10.035483);
d.definir_AZ(2, 1,2.01410177784);
t.definir_AZ(3, 1,3.01604928132);

double interacciones{10000}; // Definimos el número de interaccioens para el for posterior


for (int i=0; i<interacciones; i++){
    auto x_uniform{gRandom->Uniform(-xACTAR/2,xACTAR/2)};
    auto y_gauss{gRandom->Gaus(0,5)};
    auto z_gauss{gRandom->Gaus(0,5)};

    auto r{TMath::Sqrt(TMath::Power(y_gauss,2)+TMath::Power(z_gauss,2))};
    auto uniforme_1{gRandom->Uniform(-1,1)};
    auto uniforme_2{gRandom->Uniform(-1,1)};
    auto theta{TMath::ACos(uniforme_1)};
    auto phi{TMath::ACos(uniforme_2)};
    
    histo_xy->Fill(x_uniform,y_gauss);
    histo_zy->Fill(z_gauss,y_gauss);
    histo_phi4cm->Fill(phi);
    histo_theta4cm->Fill(theta);

   // auto [T3,Theta3] {valores3(li11, d, t, li10, 7.5 * 12,thetaCM * TMath::DegToRad())};
    auto [T4,Theta4] {valores4(li11, d, t, li10, 7.5 * 12,theta)};
        // std::cout << "Theta4: " << Theta4 << " T4 : " << T4 << '\n';
    if(std::isfinite(Theta4) && std::isfinite(T4))
       histo_T4->Fill(Theta4,T4);
   // if(std::isfinite(Theta3) && std::isfinite(T3))
   //    gother3->SetPoint(gother3->GetN(), Theta3 * TMath::RadToDeg(), T3);

}

auto* canvas_xyz {new TCanvas {"canvas_xyz", "XY"}};

canvas_xyz -> DivideSquare(2);
canvas_xyz -> cd(1);
histo_xy->Draw("colz");
canvas_xyz -> cd(2);
histo_zy->Draw("colz");

auto* canvas_thetaphi {new TCanvas {"canvas_thetaphi", "angulos"}};

canvas_thetaphi -> DivideSquare(2);
canvas_thetaphi -> cd(1);
histo_phi4cm->Draw("colz");
canvas_thetaphi -> cd(2);
histo_theta4cm->Draw("colz");

auto*  canvas_T4 {new TCanvas{"canvas_T4", "T4"}};
histo_T4->Draw("kcool");


}