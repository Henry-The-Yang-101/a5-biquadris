#include "../graphics-view.h"
#include "biquadris-proxies.h"
#include "biquadris.h"

using namespace std;

int main() {
    BiQuadris dummyGameEngine;
    DisplayProxy dummyProxy = DisplayProxy{dummyGameEngine};

    // GraphicsView testEnhanced = ConsoleView{dummyProxy, true};
    GraphicsView testNormal = ConsoleView{dummyProxy, false};

    // testEnhanced.render();
    // testNormal.render();
}