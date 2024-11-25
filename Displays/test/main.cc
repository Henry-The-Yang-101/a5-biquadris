#include "../console-view.h"
#include "biquadris-proxies.h"
#include "biquadris.h"

using namespace std;

int main() {
    BiQuadris dummyGameEngine;
    DisplayProxy dummyProxy = DisplayProxy{dummyGameEngine};

    ConsoleView test = ConsoleView{dummyProxy, true};

    test.render();
}