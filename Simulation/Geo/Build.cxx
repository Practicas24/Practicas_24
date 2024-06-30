#include "ActGeometry.h"

#include <map>
#include <string>
#include <utility>

void Build(bool draw = true)
{
    // Define parameters
    // Remember that we work with HALF LENGTHS
    // Drift cage for ACTAR
    double driftX {25.6 / 2}; // cm
    double driftY {25.6 / 2};
    double driftZ {25.6 / 2};
    ActSim::DriftChamber actar {driftX, driftY, driftZ};
    // unit silicon size
    double silicon1X {0.15 / 2}; // 1500 um to cm
    double silicon1Y {8. / 2};
    double silicon1Z {5.0 / 2};
    ActSim::SilUnit silUnit {0, silicon1X, silicon1Y, silicon1Z};
    // Set placements
    std::map<int, std::pair<double, double>> l0Placements {{0, {0, 0}}};
    ActSim::SilAssembly l0Assembly {0, silUnit, true, false};
    // Distance from ACTAR's rear
    double dist {10.4}; // cm
    l0Assembly.SetOffsets(dist);
    l0Assembly.SetAssemblyPlacements(l0Placements);

    // BUILD GEOMETRY
    ActSim::Geometry geo {};
    geo.SetDrift(actar);
    geo.AddAssemblyData(l0Assembly);
    geo.Construct();
    geo.Print();

    // Save geometry named simple in this directory
    geo.WriteGeometry("./", "simple");

    // and draw it if necessary
    if(draw)
        geo.Draw();
}
