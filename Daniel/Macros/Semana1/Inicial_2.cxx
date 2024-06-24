#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "ActKinematics.h"

#include "Rtypes.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH1.h" // ¿Por qué tengo que incluirlo aquí?¿No se pueden usar librerías? 
#include "TH2.h"
#include "TRandom.h"

void Inicial_2() {

// En esta macro tengo que representar 3 histogramas. La primera será una gaussiana, la segunda una uniforme y la tercera una arocs de una uniforme
// Como siempre comenzamos definiendo el objeto histograma a partir de la clase histograma

auto* gauss {new TH1D {"gauss","Gaussiana 1D;Eje",200,-10,10}};
auto* uniforme {new TH1D {"uniforme","Uniforme 1D;Eje",200,-1.1,1.1}};
auto* arcos {new TH1D {"arcos","arcos 1D;Eje",100,0,TMath::Pi()}};


// Ahora la cuestión es rellenar los histogramas con valores (y luego representalos). Para generar valores aleatorios crearemos una for que cree un número limitado de 
//    números aleatorios para que así, posteriormente, los podramos rellenar. Para crearlos usamos gRandom. 

for (int i=0;i<100000;i++){
    auto vgauss{gRandom->Gaus(0.5,3)}; // Duda seria: ¿Estamos invocando una clase?¿Pero si la estoy llamando siempre igual?¿Acaso gRandom hace otra cosa?
    auto vuniform{gRandom->Uniform(-1,1)};
    auto theta{TMath::ACos(vuniform)}; // ACso lee automaticamente 
    gauss->Fill(vgauss);
    uniforme->Fill(vuniform);
    arcos->Fill(theta);
}

// Printeemos los histogramas

// Graficamos las gaussianas

auto* Canvas_gauss {new TCanvas{"gauss","gauss"}}; // Sigo sin entender que significa cada cosa

gauss->Draw();

// Graficamos las uniformes

auto* Canvas_uniform {new TCanvas{"uniform","uniform"}}; // En esta vamos a crear 2 pads (2 gráficas?)

Canvas_uniform -> DivideSquare(2);
Canvas_uniform -> cd(1);

uniforme->Draw();
Canvas_uniform -> cd(2);
arcos->Draw();



    
}