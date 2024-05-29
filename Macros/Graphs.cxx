#include "ActKinematics.h"

#include "Rtypes.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

void Graphs()
{
    // Vamos usar un obxecto que calcula as liñas cinemáticas para representalas nun gráfico:
    // 1-> Crea o obxecto, normalmente de tipo pointer (auto* variable = new Constructor {argumentos})
    auto* kin {new ActPhysics::Kinematics {"11Li", "d", "p", 80}};
    // ActPhysics -> é o módulo (namespace) no que está a clase
    // Kinematics -> clase que fai operacións de cinemática;
    // Os argumentos son varios
    // {"beam", "target", "lixeiro", enerxia do feixe}
    // Aquí simulamos a reacción 11Li(d,p). Por conservación de números Z e A a partícula que falta é 12Li (compútese
    // automaticamente) d = deuterio, 2H p = protón, 1H Enerxía do 11Li inicial de 80 MeV

    // Para representar a curva Elab vs thetaLab, usamos a función:
    auto* gkin {kin->GetKinematicLine3()};
    // gkin é de tipo TGraph*, un pointer a un obxecto TGraph. Podes consultalo na web de ROOT

    // Para debuxar algo, usamos un canvas
    auto* canvas {
        new TCanvas {"canvas", "Canvas para graficos"}}; // 2 argumentos: nome da variable como string e título
    gkin->Draw("al");
    // As opcións do anterior comando son:
    // a = debuxa os eixos (só o tes que poñer unha vez)
    // l = debuxa unha liña entre os puntos
    // p = debuxa o marcador sobre cada punto
    // Podes combinar varias: apl, al, ap...

    // Podes facer moitas cousas
    // 1-> Cambiar o título do gráfico
    gkin->SetTitle("Cinematica para 11Li(d,p);#theta_{Lab} [#circ];E_{Lab}");
    // A orde do anterior comando é:
    //"Título do gráfico;Título eixo X;Título eixo Y" <-- Nota que usamos ; para separar os títulos
    // 2-> Cambiar de cor
    gkin->SetLineColor(kOrange); // Ou código numérico, consulta TColor
    // 3-> Ou anchura da liña: 1, 2 (defecto aquí), 3, 4,...
    gkin->SetLineWidth(5);

    // Finalmente... que pasa se queres debuxar outro gráfico sobre este?
    // 1-> Vamos crear un gráfico moi simple con dous puntos:
    auto* gother {new TGraph}; // sen argumentos
    // 2 -> Metemos dous puntos
    gother->SetPoint(gother->GetN(), 5, 5);
    // A estrutura do comando anterior é: (idx, x, y). Con GetN() podemos calcualar auto o índice sen especificalo nós
    gother->SetPoint(gother->GetN(), 50, 25);
    // 3-> Poñémolo bonito
    gother->SetLineWidth(2);
    gother->SetLineColor(kRed);
    // E podes especificar un marker: mira TAttMarker. Eu normalmente uso os indexados 24, 25, 26...
    gother->SetMarkerStyle(24);
    gother->SetMarkerColor(kBlue);

    // 4-> E debuxamos sobre o anterior así
    gother->Draw("pl"); // moi importate: para debuxar por enriba NON usas a opción "a"; iso resetearía o plot

    // E podes crear unha lenda
    auto* legend {new TLegend {0.7, 0.7, 0.9, 0.9}};
    // Os argumentos son as posicións esquerda inf e dereita sup sobre o canvas, de 0 a 1
    legend->AddEntry(gkin, "Kinematics");
    legend->AddEntry(gother, "Raw graph");

    // E para debuxar
    legend->Draw(); // non require argumentos
}
