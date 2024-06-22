#include <iostream>
#include <utility>


// Vamos a crear nuestra primera clase en c++

// Una clase consta de ciertos atributos, que son variables (pueden ser arraays, enteros, complejos, booleanos...),; y métodos que son funciones que trabajan con los 
//      atributos. Los atributos pueden ser publicos o privados. 

// Nuestra clase sera una reacción, por lo que primero tenemos que pensar que atributos queremos que tenga la reacción. Toda reacción esta formada por partículas, por
//      lo  que lo primero es darle nombres y números atómicos/másicos a las partículas que colisionan. 


class Particula {
    double Z;
    double M;

    public:
        void definir_MZ(double valor);
        double get_M(){return M}
};

void Particula::definir_MZ (double M, double Z) {
    M = M;
    Z = Z
};

void Particula::definir_Z (double valor) {
    Z = valor;
};

// Una colisión esta caracterizada por la energía del atomo incidente y las partículas que la componen


class Colision {
    Particula p1;
    Particula p2;
    Particula p3;
    Particula p4;
    double tbeam; 

public: 
    void energia(double valor);
    void introducir_particulas(Particula p1, Particula p2, Particula p3, Particula p4);
    double get_m1(){return p1.get_M() };
    double get_m2(){return p2.get_M() };
    double get_m3(){return p3.get_M() };
    double get_m4(){return p4.get_M() };
    double get_tbeam(){return tbeam};
};


void Colision::introducir_particulas (Particula p1, Particula p2, Particula p3, Particula p4){
    p1 = p1;
    p2 = p2;
    p3 = p3;
    p4 = p4;
};

void Colision::energia (double valor){
    tbeam = valor
}
