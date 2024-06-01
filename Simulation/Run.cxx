#include "ActGeometry.h"
#include "ActSRIM.h"

#include "TCanvas.h"

#include <string>

// Aquí podes escribir as funcións auxiliares que necesites

void Run()
{
    // Configuración das partículas a simular
    std::string beam {"11Li"};
    std::string target {"d"};
    std::string light {"t"};
    std::string heavy {"10Li"};

    // Número de iteracións
    int iter {10000};

    // Táboas de SRIM
    ActPhysics::SRIM srim {};

    // Xeometría
    ActSim::Geometry geo {};
    geo.ReadGeometry("./Geo/", "simple");

    // Creación de histogramas e gráficos

    // Bucle for
    for(int it = 0; it < iter; it++)
    {
        // Executa os sampleados para cada evento
    }

    // Representación no TCanvas
    auto* c0 {new TCanvas {"c0", "Canvas 0"}};
}
