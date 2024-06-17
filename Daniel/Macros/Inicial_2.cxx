#include <iostream>
#include <string>
#include <vector>

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

auto* gauss {new TH1{"gauss","Gaussiana 1D;nosequesentidotieneseparartitulos",200,-10,10}};
auto* uniforme {new TH1{"uniforme","Uniforme 1D;nosequesentidotieneseparartitulos",200,-10,10}};
auto* arcos {new TH1{"arcos","arcos 1D;nosequesentidotieneseparartitulos",360*5,-180,180}};


// Ahora la cuestión es rellenar los histogramas con valores (y luego representalos). Para generar valores aleatorios crearemos una for que cree un número limitado de 
//    números aleatorios para que así, posteriormente, los podramos rellenar. Para crearlos usamos gRandom. 

for (int i=0,i<100000,i++){
    auto vgauss{gRandom->Gauss(0.5,3)}; // Duda seria: ¿Estamos invocando una clase?¿Pero si la estoy llamando siempre igual?¿Acaso gRandom hace otra cosa?
    auto vuniform{gRandom->Uniform(-9,9)};

    gauss->Fill(vgauss);
    uniforme->Fill(vuniform);
    arcos->Fill(vuniform);
}

// Printeemos los histogramas

// Graficamos las gaussianas

auto* Canvas_gauss {new, TCanvas{"gauss","gauss"}};

gauss->Draw();



// Graficamos las uniformes

auto* Canvas_uniform {new, TCanvas{"uniform","uniform"}}; // En esta vamos a crear 2 pads (2 gráficas?)

Canvas_uniform -> DivideSquare(2);
Canvas_uniform -> cd(1);

uniforme->Draw();
arcos->Draw();






















    
}