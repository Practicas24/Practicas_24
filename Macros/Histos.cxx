#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"

void Histos()
{
    // Un histograma permite discretizar variables continuas en bins
    // Son moi utilizados en física pola imposibilidade de tratar evento a evento
    // situacións con alta estatística

    // Poden ser 1D
    // Debes construílos como:
    // 1: Nome da variable como string
    // 2: Título, co mesmo método das ; para separar diferentes eixos
    // 3: Número de bins, neste caso 100
    // 4: Xmin: -5
    // 5: Xmax: 5
    // Isto quere dicir que vamos ter 100 bins cunha separación entre
    // eles de (5 - (-5)) / 100 = 0.1
    //[-5, -4.9), [-4.9, -4.8), [-4.8, -4.7), ...., [4.9, 5)
    auto* h1d {new TH1D {"h1d", "Histo 1D;Variable X;Contas", 100, -5, 5}};

    // E tamén 2D
    // Agora debes especificar o binning para o eixo Y en 3 argumentos extra;
    // aquí: nbinsy = 200, ymin = -10; ymax = 10
    auto* h2d {new TH2D {"h2d", "Histo 2D;X;Y;Contas", 100, -5, 5, 200, -10, 10}};

    // Vamos encher estes histogramas con números aleatorios e representalos.
    // En ROOT podes xerar números aleatorios coa variable GLOBAL gRandom

    // 1-> Definimos o número de iteracións
    int iter {100000};
    // 2-> Bucle for
    for(int i = 0; i < iter; i++)
    {
        // Vamos xerar en X un número alearorio que siga unha distribución gaussiana
        auto rx {gRandom->Gaus(0, 1)}; // mean = 0, sigma = 1
        // Podes consular a doc aquí:
        // https://root.cern.ch/doc/master/classTRandom.html#a0e445e213eae1343b3d22086ecb87314
        // E en Y un uniforme entre os límites en Y do histograma
        auto ry {gRandom->Uniform(-10, 10)};

        // Enchemos os histogramas:
        h1d->Fill(rx);
        h2d->Fill(rx, ry);
    }

    // Representámolos cun TCanvas
    auto* canvas {new TCanvas {"canvas", "Histo canvas"}};
    // E vamos dividilos en 2 PADS: subdivisións nun TCanvas
    canvas->DivideSquare(2); // creamos 2 pads
    // Accedemos ao primeiro pad
    canvas->cd(1);
    h1d->Draw();
    // Ao segundo
    canvas->cd(2);
    h2d->Draw("colz"); // "colz" mete unha escala de cores
    // O valor de z é o número de contas en cada rectángulo que é cada bin!

    // Se quixeras debuxar un histograma sobre outro,
    // h->Draw("same"); // a opción a usar é same
}
