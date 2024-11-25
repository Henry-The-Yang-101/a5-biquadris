#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H
#include "display-observer.h"

using namespace std;

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using CharGrid = vector<vector<char>>;

class ConsoleView: public DisplayObserver{
    
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
              nextContainerHeight = 17;
    public:
        ConsoleView(DisplayProxy &displayProxy, bool enhanced);
        void render();
};

#endif
