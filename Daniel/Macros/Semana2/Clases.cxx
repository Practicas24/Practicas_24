#include <iostream>
#include <utility>


// Vamos a crear nuestra primera clase en c++

// Una clase consta de ciertos atributos, que son variables (pueden ser arraays, enteros, complejos, booleanos...),; y
// métodos que son funciones que trabajan con los
//      atributos. Los atributos pueden ser publicos o privados.

// Nuestra clase sera una reacción, por lo que primero tenemos que pensar que atributos queremos que tenga la reacción.
// Toda reacción esta formada por partículas, por
//      lo  que lo primero es darle nombres y números atómicos/másicos a las partículas que colisionan.


class Particula
{
    double fZ;
    double fA;

public:
    void definir_MZ(double valorM, double valorZ);
    double get_M() { return fA; };
    void Print();
};

void Particula::definir_MZ(double M, double Z)
{
    fA = M;
    fZ = Z;
};

void Particula::Print()
{
    std::cout << "--- Particle ----" << '\n';
    std::cout << "-> Z : " << fZ << '\n';
    std::cout << "-> A : " << fA << '\n';
}


// Una colisión esta caracterizada por la energía del atomo incidente y las partículas que la componen


class Colision
{
    Particula fp1;
    Particula fp2;
    Particula fp3;
    Particula fp4;
    double ftbeam;

public:
    void energia(double valor);
    void introducir_particulas(Particula p1, Particula p2, Particula p3, Particula p4);
    double get_m1() { return fp1.get_M(); };
    double get_m2() { return fp2.get_M(); };
    double get_m3() { return fp3.get_M(); };
    double get_m4() { return fp4.get_M(); };
    double get_tbeam() { return ftbeam; };
    Particula GetParticle1() { return fp1; }
};


void Colision::introducir_particulas(Particula p1, Particula p2, Particula p3, Particula p4)
{
    fp1 = p1;
    fp2 = p2;
    fp3 = p3;
    fp4 = p4;
};

void Colision::energia(double valor)
{
    ftbeam = valor;
}
