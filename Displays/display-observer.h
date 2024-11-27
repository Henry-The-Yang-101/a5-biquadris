#ifndef DISPLAYOBSERVER
#define DISPLAYOBSERVER
#include "../Miscellaneous/observer.h"
#include "./test-graphics/biquadris-proxies.h"

using namespace std;

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using CharGrid = vector<vector<char>>;
using BlockCellCoordinates = std::vector<CellCoordinate>;

class DisplayObserver: public Observer{
    
    protected:
        DisplayProxy &displayProxy;

        const int holdGridRows = 2, 
                holdGridCols = 4, 
                enhancedNextGridRows = 14, 
                enhancedNextGridCols = 4, 
                nextGridRows = 2,
                nextGridCols = 4,
                gameGridRows = 18, 
                gameGridCols = 11,

                blockCoordAdjustment = 1;

        bool enhanced;
        
        CharGrid p1GameGrid;
        CharGrid p1HoldGrid;
        CharGrid p1NextGrid;

        CharGrid p2GameGrid;
        CharGrid p2HoldGrid;
        CharGrid p2NextGrid;

    public:
        DisplayObserver(DisplayProxy &displayProxy, bool enhanced);
        void notify();
        void render();
};

#endif
