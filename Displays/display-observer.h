#ifndef DISPLAYOBSERVER
#define DISPLAYOBSERVER
#include "../Miscellaneous/observer.h"
#include "./test/biquadris-proxies.h"

using namespace std;

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using CharGrid = vector<vector<char>>;
using BlockCellCoordinates = std::vector<CellCoordinate>;

class DisplayObserver: public Observer {
    
    protected:
        const DisplayProxy &displayProxy;

        const int holdGridRows = 2; 
        const int holdGridCols = 4; 
        const int enhancedNextGridRows = 14; 
        const int enhancedNextGridCols = 4; 
        const int nextGridRows = 2;
        const int nextGridCols = 4;
        const int gameGridRows = 18;
        const int gameGridCols = 11;
        const int blockCoordAdjustment = 1;
        const int reserveRowHeight = 3;

        const int blindRowStart = 2 + reserveRowHeight;
        const int blindRowEnd = 11 + reserveRowHeight;
        const int blindColStart = 2;
        const int blindColEnd = 8;

        const char blockPreviewChar = '*';
        const char blindEffectChar = '?';
        
        CharGrid p1GameGrid;
        CharGrid p1HoldGrid;
        CharGrid p1NextGrid;

        CharGrid p2GameGrid;
        CharGrid p2HoldGrid;
        CharGrid p2NextGrid;

        virtual void render() = 0;
    public:
        DisplayObserver(const DisplayProxy & displayProxy);
        void notify();
};

#endif
