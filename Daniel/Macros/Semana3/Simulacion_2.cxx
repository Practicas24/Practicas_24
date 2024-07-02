#include "ActGeometry.h"
#include "ActSRIM.h"
#include "ActKinematics.h"

#include "Math/Point3D.h"
#include "Math/Vector3D.h"

#include "Rtypes.h"

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

void Simulacion_2(){

// Hay inconsistencias entre diferentes valores en el main.pdf (10 cm, luego 10.4 cm; 255 cm para Z, luego 256 cm)

// Una vez creado la geometria (simple.root) en la carpeta de Geometria, podemos calcular nuestra simulacion. 
// Primero creamos la variable geo que nos permite leer el archivo que guarda la geometría

auto* geo {new ActSim::Geometry};

// Lemos o ficheiro de configuración
// Tras crealo previamente
geo->ReadGeometry("Geometria/", "simple");

//Ahora tengo que implementar las variables aleatorias que cree (y verifique) en el macro Simulacion_1.cxx. En ese caso:


// Detallamos las partículas
li11.definir_AZ(11, 3,11.0437236);
li10.definir_AZ(10, 3,10.035483);
d.definir_AZ(2, 1,2.01410177784);
t.definir_AZ(3, 1,3.01604928132);

for(int i; i<10000; i+=1){

    auto x_uniform{gRandom->Uniform(-xACTAR/2,xACTAR/2)};
    auto y_gauss{gRandom->Gaus(0,5)};
    auto z_gauss{gRandom->Gaus(0,5)};

    auto r{TMath::Sqrt(TMath::Power(y_gauss,2)+TMath::Power(z_gauss,2))};

    auto theta{TMath::ATan(r/x_uniform)*TMath::RadToDeg()};
    auto phi{TMath::ATan(y_gauss/z_gauss)*TMath::RadToDeg()};

    auto [T4,Theta4] {valores4(li11, d, t, li10, 7.5 * 12,theta)};
        // std::cout << "Theta4: " << Theta4 << " T4 : " << T4 << '\n';
    if(std::isfinite(Theta4) && std::isfinite(T4))
       histo_T4->Fill(Theta4,T4);


    // 1-> Creamos el vertice- a partir de (x,y,z) aleatorios
    ROOT::Math::XYZPoint vertice {x_uniform , y_gauss, z_gauss};

    // 2-> Creamos los angulos 
    ROOT::Math::XYZVector direccion {TMath::Cos(Theta4), TMath::Sin(Theta4)*TMath::Sin(phi), TMath::Sin(Theta4)*TMath::Sin(phi)};

    bool SilLado{}; // No se que es esto (??)
    double SilDist{}; // Distancia desde el vertice hasta el punto de impacto
    int SilTipo{}; // TIpo de silicio
    int SilIndice{}; // Indice del silicio 
    ROOT::Math::XYZPoint SilPunto {}; //Punto de impacto

    geo->PropagateTrackToSiliconArray(vertice,direccion,SilLado,SilDist,SilTipo,SilIndice,SilPunto) 

    SilDist*=10 // Convertimos la distancai de mm a cm


}












}