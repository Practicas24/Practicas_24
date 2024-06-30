#include "ActGeometry.h"

#include "Math/Point3D.h"
#include "Math/Vector3D.h"
void geo()
{
    // Declaramos a variable, neste caso como un pointer
    auto* geo {new ActSim::Geometry};
    // Lemos o ficheiro de configuración
    // Tras crealo previamente
    geo->ReadGeometry("../Simulation/Geo/", "simple");

    // E xa podes operar. Por exemplo, para cada iteración
    for(int i = 0; i < 10; i++)
    {
        // 1-> O vértice (obv utiliza o que sampleas)
        ROOT::Math::XYZPoint vertex {0, 0, 0};

        // 2-> A dirección (obv utiliza os valores theta4, phi4 correctos)
        ROOT::Math::XYZVector direction {1, 0, 0};

        // 3-> Declaramos as variables que se van devolver na función
        bool silSide {};
        double silDist {};
        int silType {};
        int silIndex {};
        ROOT::Math::XYZPoint silPoint {};

        // 4-> E chamamos á función
        geo->PropagateTrackToSiliconArray(vertex, direction, 0, silSide, silDist, silType, silIndex, silPoint);
        // A distacia é a distancia real, tendo en conta os ángulos
        // Polo tanto, cando chames a SRIM, non necesitarás especificar o ángulo porque xa está implicitamente
        // considerado Iso si, convertes a distancia de cm ( é o que devolve a función ) a mm ( o que necesita SRIM e
        // como usualmente traballamos)
        silDist *= 10;

        // 5-> Se a partícula impacta XEOMETRICAMENTE
        if(silIndex != -1)
        {
            // Facemos operacións, como reducir a enerxía T4 unha distancia silDist
            // O ángulo theta4 xa estará implicitamente considerado nesa distancia
        }
    }
}
