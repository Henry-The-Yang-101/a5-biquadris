#ifndef CONSOLEVIEW_H
#define CONSOLVEVIEW_H
#include "../Miscellaneous/observer.h"
#include "./test/biquadris-proxies.h"

using namespace std;

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using CharGrid = vector<vector<char>>;

class ConsoleView: public Observer{
    DisplayProxy &displayProxy;

    bool enhanced;
    
    //constants defining spacing for various elements of the board
    const int 
              displayHeight = 26,
              rightInteriorPadding = 10, 
              leftInteriorPadding = 10, 

              holdContainerWidth = 8, 
              gameContainerWidth = 23, 
              nextContainerWidth = 8, 
              holdContainerHeight = 5, 
              gameContainerHeight = 19, 
              nextContainerHeight = 17,

              holdGridRows = 2, 
              holdGridCols = 4, 
              enhancedNextGridRows = 14, 
              enhancedNextGridCols = 4, 
              nextGridRows = 2,
              nextGridCols = 4,
              gameGridRows = 18, 
              gameGridCols = 11,

              blockCoordAdjustment = 1;
    
    CharGrid p1GameGrid;
    CharGrid p1HoldGrid;
    CharGrid p1NextGrid;

    CharGrid p2GameGrid;
    CharGrid p2HoldGrid;
    CharGrid p2NextGrid;

    public:
        ConsoleView(DisplayProxy &displayProxy, bool enhanced);
        void notify();
        void render();
};

#endif
