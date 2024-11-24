#ifndef CONSOLEVIEW_H
#define CONSOLVEVIEW_H
#include "../Miscellaneous/observer.h"
#include "../Biquadris/biquadris-proxies.h"

using namespace std;

using CellCoords = pair<int, int>;
using BlockAttributes = pair<vector<CellCoords>, char>;
using Grid = vector<vector<char>>;

class ConsoleView: public Observer{
    DisplayProxy &displayProxy;

    bool enhanced;
    
    //constants defining spacing for various elements of the board
    const int 
              displayHeight = 26,
              rightInteriorPadding = 5, 
              leftInteriorPadding = 5, 

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
              gameGridCols = 11;
    
    Grid p1GameGrid;
    Grid p1HoldGrid;
    Grid p1NextGrid;

    Grid p2GameGrid;
    Grid p2HoldGrid;
    Grid p2NextGrid;

    public:
        ConsoleView(DisplayProxy &displayProxy, bool enhanced);
        void notify();
        void render();
};

#endif