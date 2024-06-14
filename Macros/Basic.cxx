#include <iostream>
#include <string>
#include <vector>

// Esto es una línea de codigo de prueba

// Esta é unha función que imos usar máis adiante no código
// Debe constar sempre de:
// TIPO DE RETURN nome(TIPO ARG1 arg1, TIPO ARG2 arg2, ...)
double add(double a, double b)
{
    return a + b;
}

// Podes ter varias funcións que se chamen igual e devolvan o mesmo tipo de variable
// sempre e cando os argumentos sexan distintos

double add(int i)
{
    return i + 1.;
}

void nada()
{
    std::cout << "Función que non devolve nada" << '\n';
}

void Basic()
{
    // Todas as variables en C++ defínense cun tipo:
    int var = 4;
    double a = 3.1415;
    // Declarar unha variable:
    int foo;
    // Asignar unha variable:
    foo = 8;
    // Facer todo nun paso:
    int bar = 8;
    // Diferentes métodos:
    double d1 = 98; // O que máis se parece a python
    double d2(98);
    double d3 {98}; // Eu utilizo este, é o máis recomendado a día de hoxe

    // Algúns tipos básicos:
    int i {4};         // enteiro
    double d {3.1415}; // un "float" un pouco máis grande en C++
    bool b {true};     // ou false
    std::string s {"unha cadea de caracteres"};
    // a string é particularmente interesante
    // é como un mini-vector; podes saber o número de elementos:
    s.size();
    // coller o caracter na posición 4
    s[4];
    // ou unha substring
    s.substr(0, 4); // no elemento 0 ata o 4 pos máis adiante
    char c {'\n'};  // un caracter; non o usaremos apenas
    // Un útil é void
    // Por exemplo, a función nada printea algo en pantalla pero non devolve nada:
    // -> o seu return type é void
    nada();

    // En C++ hai un tipo de variables especiais: os pointers
    //  Almacenan a posición en memoria de obxectos de longa duración
    //  Créasense coa keyword new e o tipo resultante é TIPO* (nota o *)
    int* ptr {new int {7}};
    // Estes obxectos NON se eliminan automaticamente ao acabar o programa;
    // débense eliminar manualmente con:
    delete ptr;
    // Non obstante, ROOT vaise "ocupar" de facelo por nós

    // C++ pode deducir os tipos automaticamente:
    auto aud {3.14};                   // auto = double aqui
    auto aui {1};                      // auto = int
    auto* auptr {new double {3.1415}}; // auto* = double*
    // É recomendable utilizalo, aínda que con coidado!

    // Vectores
    // Debes especificar o tipo de obxecto que almacenan:
    std::vector<int> vi {1, 2, 3};
    // Podes engadir elementos ao final con:
    vi.push_back(4);
    // E accedes aos elementos con:
    vi[0];
    // O número de elementos é:
    vi.size();

    // Como imprimir á terminal?
    // É máis complexo que en python:
    // Hai que usar std::cout e redirixir (<<) o que queremos:
    std::cout << "Ola mundo" << '\n'; // tes que definir ti explicitamente o final de liña co caracter '\n'
    // E para concatenar varias cousas
    std::cout << "Teño un vector de tamaño : " << vi.size() << '\n';

    // Un bucle for:
    std::vector<std::string> vs {"A", "B", "C", "D", "E", "F"};
    for(int i = 0; i < vs.size(); i++) // i++ é equivalente a i = i +1
    {
        std::cout << vs[i] << '\n';
    }
    std::cout << "------------------------------" << '\n';
    // Se non necesitas un índice, podes facer algo parecido a python:
    // equivalente ao for str in vs. con const auto& non tes que especificar ti o tipo de obxecto sobre o que iteras
    for(const auto& str : vs)
        std::cout << str << '\n';

    std::cout << "------------------------------" << '\n';
    // E as condicións if else son:
    std::vector<std::string> vss {"Vector", "de", "strings", "", "", "sen", "espazos", "en", "branco"};
    // Vamos imprimir en pantalla todos os elementos non nulos:
    for(const auto& str : vss)
    {
        if(str.size() == 0)
            continue;
        std::cout << str << '\n';
    }
    // Os operadores booleanos son:
    // == igualdade
    // != non igualdade
    // && é o AND
    // || é or OR
    // ! é o complementario: !false = true

    // E finalmente as funcións
    // Defínense antes do macro sempre
    auto suma {add(89., 6500)}; // Chama a add(double, double)
    auto suma1 {add(d1, d2)};   // O mesmo
    auto sumai {add(i)};        // Chama a add(int)
}
