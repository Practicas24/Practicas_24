#include <iostream>
#include <string>
#include <vector>

#include "ActKinematics.h"

#include "Rtypes.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

void Inicial_1()
{

// Vamos a crear los 3 objetos que necesitamos, cada uno representara una reacción distinta
// Para definir una función lo que tengo que hacer es determinar el tipo de variable (auto detecta automaticamente la variable introducida)
//   mientras que * se usa para denotar que es un pointer (duda: ¿La memoria en que lugar se guarda?). Por la misma razón debe usarse new. 
//   Denotamos con nombres sencillos a  las reacciones. Lo que estamos haciendo es decir que la variable Li10, Li11 y Li12 es el return de la clase
//   Kinematics para los valores dados (de esto ultimo no estoy seguro, lo que es  seguro es que Kinematics es una clase). 

auto* Li10{new ActPhysics::Kinematics("11Li","d","t","10Li",14*7.5)};

auto* Li11{new ActPhysics::Kinematics("11Li","d","d","11Li",14*7.5)};

auto* Li12{new ActPhysics::Kinematics("11Li","d","p","12Li",14*7.5)};

// Ahora queremos representar la colisión (tanto de la particula pesada como la ligera), cada una en una gráfica diferente (si no?)

auto* g3Li10{Li10 -> GetKinematicLine3()};
auto* g4Li10{Li10 -> GetKinematicLine4()};

auto* g3Li11{Li11-> GetKinematicLine3()};
auto* g4Li11{Li11 -> GetKinematicLine4()};

auto* g3Li12{Li12 -> GetKinematicLine3()};
auto* g4Li12{Li12 -> GetKinematicLine4()};

// Duda: ¿Para que sirve la flecha?
// Dudas serias: ¿Usamos auto* porque no sabemos el tipo de variable?¿Es el interprete ROOT el qeu define que tipo de variable en la memoria?

// TCanvas vuelve a ser una clase (creo)


auto* canvas10{new TCanvas {"Li10","Li10"}};

g3Li10 -> Draw("l");
g4Li10 -> Draw("al");

g3Li10 -> SetLineColor(kRed);
g4Li10 -> SetLineColor(kBlue);

g4Li10->SetTitle("Cinematica para 11Li(p,t);#theta_{lab} [#circ];E_{lab}");  // Dado qeu se lo estoy dandoa a g4Li10,¿Funcionará?¿O es para g3Li10?
// No se como funciona el SetTitle para los ejes



auto* legend10{new TLegend {0.7,0.7,0.95,0.95}}; // Me pregunto que saldra haciendolo asi
legend10 -> AddEntry(g3Li10,"Particula ligera, tritio");
legend10 -> AddEntry(g4Li10,"Particula pesada, 10Li");
legend10 -> Draw();

// En  el eje  y aparece E3 --> Buscar como cambair el nombre de cada eje

// ¿Cual es el exactamente el argugment ode TCAnvas?

// Dado que se puede entender que el resto de gráficas se hace igual metiendo un nombre diferente a canvas (difernete variable?)
// --> Efectivamente, tengo que cambiar el nombre de cada canvas

auto* canvas11{new TCanvas {"Li11","Li11"}};

g3Li11 -> Draw("l");
g4Li11 -> Draw("al");

g3Li11 -> SetLineColor(kRed);
g4Li11 -> SetLineColor(kBlue);

auto* legend11{new TLegend {0.7,0.7,0.95,0.95}}; 
legend11 -> AddEntry(g3Li11,"Particula ligera, deuterio");
legend11 -> AddEntry(g4Li11,"Particula pesada, 11Li");
legend11 -> Draw();


auto* canvas12{new TCanvas {"Li12","Li12"}};

g3Li12 -> Draw("l"); 
g4Li12 -> Draw("al");

g3Li12 -> SetLineColor(kRed);
g4Li12 -> SetLineColor(kBlue);

auto* legend12{new TLegend {0.7,0.7,0.95,0.95}};  
legend12 -> AddEntry(g3Li12,"Particula ligera, hidrogeno");
legend12 -> AddEntry(g4Li12,"Particula pesada, 12Li");
legend12 -> Draw();



}





