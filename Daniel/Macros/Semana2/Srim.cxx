#include "ActSRIM.h"
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


void Srim() {

// En primer lugar tenemos que crear un objeto de la clase SRIM que llamaremos srim
ActPhysics::SRIM srim;

// Esta clase posee una función que puede leer tablas de datos. De hecho puede leer multiples tablas. Para leerlas tenemos que introducir un primer parámetro,
//      que es un String que nos permite identificar cada tabla, y otro que es el archivo que estamos leyendo (hay que indicar el camino).

srim.ReadTable("Litio_11","/home/daniel/GitHub/Practicas_24/SRIM/11Li_mixture_900mbar.txt");
srim.ReadTable("Hidrogeno_2","/home/daniel/GitHub/Practicas_24/SRIM/2H_mixture_900mbar.txt");

// Necesitamos leer la segunda tabla ya que de otra forma no podremos usar srim.Slow()

// Las funciones básicas de esta clase son las siguientes:

// srim.EvalDirect(const std::string& key, double energy)
// srim.slow(const std::string& material, double Tini, double thickness, double angleInRad)

// La primera función coge la tabla y obtiene un rango para una energía dada. Duda: ¿Que significa "obtener un rango"? --> Creo que significa que nos
//      da la distancia máxima reocorrida antes de pararse (de la partícula)

// La segunda función coge la tabla, una energía inicial, y calcula la energía final despues de atravesar una longitud determinada a través
//      del material determinado.

// Problema: en el guion aparecen dos funciones mas pero no me aparece en el autocompletado (EvalInverse y EvalInitialEnergy)

// Tenemos que representar dos gŕáficas : 

auto* perdida_distancia{new TGraph};
auto* perdida_energia{new TGraph};

// Ponemos títulos 
perdida_distancia->SetTitle("Eperdida vs distancia;dist [mm];dE/dx [MeV]");
perdida_energia->SetTitle("Eperdida vs energia;T [MeV];dE/dx [MeV]");

// Elegimos la energía inicial (11*7.5)

double Tinicial{11*7.5};

// La siguiente variable va a representar la energía de la partícula en tras recorrer una distancia determinada. El primer valor debe ser igual al valor inicial,
//      por eso la definimos así. En cada interacción del bucle for verá reducido su valor. 
double Tit{Tinicial};

// Calculamos la longitud máxima que recorre con esta energía inicial:


double Distancia_maxima{srim.EvalDirect("Litio_11",Tinicial)};

// Ahora vamos a aplicar el SLOW para obtener la energía perdida en una distancia. Para esto vamos a usar un for:

double step{Distancia_maxima/1000};
auto* gother1 {new TGraph};
auto* gother1_15 {new TGraph};
auto* gother1_45 {new TGraph};
auto* gother2 {new TGraph};

for(double x=0;x<Distancia_maxima;x += 1){
    
    double Tnew{srim.Slow("Hidrogeno_2", Tit, step, 0*TMath::DegToRad())};
    std::cout << "Tit: " << Tit << " Tnew : " << Tnew << '\n';
    double Tnew_15{srim.Slow("Hidrogeno_2", Tit, step, 15*TMath::DegToRad())};
    double Tnew_45{srim.Slow("Hidrogeno_2", Tit, step, 45*TMath::DegToRad())};

    double diff{Tit-Tnew};
    double diff_15{Tit-Tnew_15};
    double diff_45{Tit-Tnew_45};

    gother1->SetPoint(gother1->GetN(), x, diff);
    gother1_15->SetPoint(gother1_15->GetN(), x, diff_15);
    gother1_45->SetPoint(gother1_45->GetN(), x, diff_45);
    gother2->SetPoint(gother2->GetN(), Tit, diff);

    Tit-=diff;

}


auto* canvas1 {new TCanvas {"canvas1", "Perdida_energia"}};
canvas1->DivideSquare(2);


canvas1->cd(1);
gother1->SetLineColor(kRed);
gother1->SetLineWidth(4);
gother1_15->SetLineColor(kBlue);
gother1_15->SetLineWidth(4);
gother1_45->SetLineColor(kOrange);
gother1_45->SetLineWidth(4);

gother1->SetTitle("Energia perdida vs Distancia;x;E_{perdida}");

gother1->Draw("al");
gother1_15->Draw("l");
gother1_45->Draw("l");

auto* legend1{new TLegend {0.7,0.7,0.95,0.95}};
legend1 -> AddEntry(gother1,"#theta = 0");
legend1 -> AddEntry(gother1_15,"#theta = 15");
legend1 -> AddEntry(gother1_45,"#theta = 45");
legend1 -> Draw();

canvas1->cd(2);
gother2->SetLineColor(kRed);
gother2->SetLineWidth(4);
gother2->SetTitle("Energia perdida vs Energia;E;E_{perdida}");

gother2->Draw("al");


}