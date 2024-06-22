#include <iostream>
#include <utility>
#include "Clases.cxx" 

// Vamos a crear las funciones que usaremos despues para obtener los  resultados

double t4(Colision colision){
    double m1{colision.get_m1()};
    double m2{colision.get_m2()};
    double m3{colision.get_m3()};
    double m4{colision.get_m4()};
    return 1;
}

double theta4cm(Colision colision, double theta4cm){
    return 2;
}

// Función principal

void Cinematica(){
    // Definimos las partiulcas
    Particula li11{};
    Particula li12{};
    Particula d{};
    Particula p{};
    
    // Detallamos las partículas
    li11.definir_MZ(11,3);
    li12.definir_MZ(12,3);
    d.definir_MZ(2,1);
    p.definir_MZ(1,1);


    Colision colision{};
    colision.introducir_particulas(li11,d,p,li12);
    colision.energia(7.5*12);


};
