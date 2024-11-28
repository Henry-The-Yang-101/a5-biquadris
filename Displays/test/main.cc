#include "../console-view.h"
#include "../display-observer.h"
#include "biquadris-proxies.h"
#include "biquadris.h"

using namespace std;

int main() {
    BiQuadris dummyGameEngine;
    DisplayProxy dummyProxy = DisplayProxy{dummyGameEngine};

    ConsoleView testEnhanced = ConsoleView{dummyProxy};
    //ConsoleView testNormal = ConsoleView{dummyProxy};

    testEnhanced.notify();
    //testNormal.notify();
}
