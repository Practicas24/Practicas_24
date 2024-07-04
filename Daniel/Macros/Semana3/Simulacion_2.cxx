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

ActPhysics::SRIM srim;

srim.ReadTable("beam","/home/daniel/GitHub/Practicas_24/SRIM/11Li_mixture_900mbar.txt");
srim.ReadTable("heavy","/home/daniel/GitHub/Practicas_24/SRIM/12Li_mixture_900mbar.txt");
srim.ReadTable("heavySil","/home/daniel/GitHub/Practicas_24/SRIM/12Li_silicon.txt");


// Hay inconsistencias entre diferentes valores en el main.pdf (10 cm, luego 10.4 cm; 255 cm para Z, luego 256 cm)

// Una vez creado la geometria (simple.root) en la carpeta de Geometria, podemos calcular nuestra simulacion. 
// Primero creamos la variable geo que nos permite leer el archivo que guarda la geometría

auto* geo {new ActSim::Geometry};

// Lemos o ficheiro de configuración
// Tras crealo previamente
geo->ReadGeometry("Geometria/", "simple");

//Ahora tengo que implementar las variables aleatorias que cree (y verifique) en el macro Simulacion_1.cxx. En ese caso:


// Detallamos las partículas


Particula li11;
Particula li10;
Particula d;
Particula t;

li11.definir_AZ(11, 3,11.0437236);
li10.definir_AZ(10, 3,10.035483);
d.definir_AZ(2, 1,2.01410177784);
t.definir_AZ(3, 1,3.01604928132);

// Tamaños de la caja
double xACTAR{256}; // Esta en mm
double yACTAR{256}; // Esta en mm
double zACTAR{255}; // Esta en mm

// Grosor del detector

double zSil{1.5}; // Esta en mm

// Energía inicial
double Tbeam{11*7.5};

// Definimos las variables histogramas. La primera -> energía de entrada al detector; La segunda -> energía perdida en el detector
auto* histo_T {new TH2D {"T_theta","Histo 2D;#theta_{4};T;Contas",150,0,2*TMath::Pi()/16,250,0,100}};
auto* histo_DT {new TH2D {"DT_theta","Histo 2D;#theta_{4};#Delta T;Contas",150,0,TMath::Pi()/8,250,0,100}};

// Definimos la normal

ROOT::Math::XYZVector normal{1, 0, 0};


for(int i=0; i<1000000; i+=1){
    

    auto x_uniform{gRandom->Uniform(-xACTAR/2,xACTAR/2)};
    auto y_gauss{gRandom->Gaus(0,5)};
    auto z_gauss{gRandom->Gaus(0,5)};

    auto r{TMath::Sqrt(TMath::Power(x_uniform,2)+TMath::Power(y_gauss,2)+TMath::Power(z_gauss,2))};

   // auto theta{TMath::ATan(r/x_uniform)*TMath::RadToDeg()};
   // auto phi{TMath::ATan(y_gauss/z_gauss)*TMath::RadToDeg()};

    auto theta4_cm{gRandom->Uniform(0,2*TMath::Pi())};
    auto phi{gRandom->Uniform(0,2*TMath::Pi())}; 

   //  std::cout << phi << "\n";

    // Calculamos la energia

    auto T1new{srim.Slow("beam", Tbeam, zSil, 0*TMath::DegToRad())}; 

    auto [T4,theta4_lab] {valores4(li11, d, t, li10, T1new,theta4_cm)};
        // std::cout << "Theta4: " << Theta4 << " T4 : " << T4 << '\n';
    if(!(std::isfinite(theta4_lab) && std::isfinite(T4)))
       continue;

    // 1-> Creamos el vertice- a partir de (x,y,z) aleatorios
    ROOT::Math::XYZPoint vertice {x_uniform , y_gauss, z_gauss};

    // 2-> Creamos los angulos 
    ROOT::Math::XYZVector direccion {TMath::Cos(theta4_lab), TMath::Sin(theta4_lab)*TMath::Sin(phi), TMath::Sin(theta4_lab)*TMath::Sin(phi)};

    bool SilLado{}; // No se que es esto (??)
    double SilDist{}; // Distancia desde el vertice hasta el punto de impacto
    int SilTipo{}; // TIpo de silicio
    int SilIndice{}; // Indice del silicio 
    ROOT::Math::XYZPoint SilPunto {}; //Punto de impacto

    
    geo->PropagateTrackToSiliconArray(vertice,direccion,0, SilLado,SilDist,SilTipo,SilIndice,SilPunto);

    SilDist*=10; // Convertimos la distancai de mm a cm
    if(SilIndice != -1){

        double thetaSi{TMath::ACos(direccion.Dot(normal))};

        double T4in{srim.Slow("heavy", T4, SilDist, 0*TMath::DegToRad())}; 

        double T4out{srim.Slow("heavySil", T4in, zSil, thetaSi*TMath::DegToRad())}; 
        
        histo_T->Fill(thetaSi,T4in);
        histo_DT->Fill(thetaSi,T4in-T4out);


    }
    
    }


auto*  canvas_T {new TCanvas{"canvas_T", "T4_vs_theta"}};
histo_T->Draw("kcool");
auto*  canvas_DT {new TCanvas{"canvas_DT", "DT4_vs_theta"}};
histo_DT->Draw("kcool");
// Dudas: ¿Debo usar hidrogeno_2?¿Debo usar EvalInverse para calcular T4new?¿Los angulso theta4 y phi4 son aleatorios?
// Dudas: No entiendo exactamente el punto 6. ¿Qué es perder la energía de los silicios?

}