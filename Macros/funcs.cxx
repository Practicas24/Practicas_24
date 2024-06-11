#include <iostream>
#include <utility>

std::pair<double, double> returnPair(double a, double b, bool boo = false)
{
    // Só podes devolver dous valores do tipo que especifiques no std::pair
    auto c {a + b};
    auto d {a - b};
    return {c, d}; // devolves dous valores entre chanves
}

void returnReference(double a, double b, double& ret1, double& ret2)
{
    // Os argumentos en C++ se se pasan como double a, int k,... son copias das variables que pases como argumentos
    // Polo tanto, se as modificas dentro non se van enterar
    // máis info: https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/
    // Non obstante, se as pasas como referencia (double&, int&, TGraph&,...) SI
    ret1 = a + b;
    ret2 = a * b;
}

// Ou podes crear unha clase sinxela para almacenar as variables
class KinematicsData
{
public: // se fas os membros da clase públicos, podes acceder directamente a eles
    double fT4 {};
    double fTheta4 {};
    double fThetaCM {};
    double fPhiCM {};
    // ...
};

KinematicsData returnClass(double a, double b)
{
    // Defines a variable
    KinematicsData data {};
    // E asignas cando queiras gardas as variables
    data.fT4 = a + b;
    data.fTheta4 = a / b;
    data.fPhiCM = b;
    data.fThetaCM = a;
    // E devolves
    return data;
}

void funcs()
{
    // Este é o macro que se vai executar e que vai chamar a diferentes funcións
    double a {4};
    double b {10};
    // 1-> Devolve un par
    auto [p1, p2] {returnPair(a, b)};

    // 2-> Devolver por referencia.
    // Tes que definir as variables antes e inicializalas
    double r1 {};
    double r2 {};
    returnReference(a, b, r1, r2);

    // 3-> Por clase
    auto data {returnClass(a, b)};
    // E accedes a eles asi
    std::cout << "Data.fT4 : " << data.fT4 << '\n';

    // Para poder utilizar esta clas noutro macro, terás que facer un o seguinte:
    // #include "NomeDoFicheiroOndeEstaDefinidaAClase.cxx" para poder utilizala
    // É a que che recomendo pois acaba sendo a máis sinxela
    // Así podes devolver as variables de T4, theta4, pero tamén T3, theta3, ...
}
