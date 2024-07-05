#include "ActGeometry.h"

#include <map>
#include <string>
#include <utility>

void Geometria(bool draw=true){

// Aquí voy a crear la geometria 
// Definimos los tamaños de las cajas (las distancias se leen como mitades)

double ladoX {25.6 / 2}; // cm
double ladoY {25.6 / 2};
double ladoZ {25.5 / 2};
ActSim::DriftChamber actar {ladoX, ladoY, ladoZ};

//Definimos el tamaño del detectpr de silicio

double SiX {0.15 / 2}; // 1500 um to cm
double SiY {8. / 2};
double SiZ {5.0 / 2};
ActSim::SilUnit silUnit {0, SiX, SiY, SiZ}; // el cero significa que solo hay un detector

// Definimos el punto de partida (creo?)

std::map<int, std::pair<double, double>> l0Placements {{0, {0, 0}}};
ActSim::SilAssembly l0Assembly {0, silUnit, true, false};

// Definimos la distancia entre el detector de silicio y el pad plane (no se que es exactamente)

double distancia {10}; // cm
l0Assembly.SetOffsets(distancia);
l0Assembly.SetAssemblyPlacements(l0Placements);

// Creamos finalmente la variable 

ActSim::Geometry geo {};
geo.SetDrift(actar);
geo.AddAssemblyData(l0Assembly);
geo.Construct();
geo.Print();

// Guardamos la geometría en un archivo root que necesitaremos leer con el macro Simulacion_2.cxx (muy importante)

geo.WriteGeometry("./", "simple");

// Dibujamos
if(draw) 
    geo.Draw();


// Este archivo solo se ejecuta una vez (a no ser que haga cambios en la geometría), ya que el archivo root (simple.root) se crea una vez y ya se lee para siempre

}
