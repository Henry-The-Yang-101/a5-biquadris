#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H
#include "display-observer.h"

using namespace std;

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using CharGrid = vector<vector<char>>;

class ConsoleView: public DisplayObserver {
    
    //constants defining spacing for various elements of the board
    const int displayHeight = 26;
    const int rightInteriorPadding = 10;
    const int leftInteriorPadding = 10;

    const int holdContainerWidth = 8;
    const int gameContainerWidth = 23;
    const int nextContainerWidth = 8;
    const int holdContainerHeight = 5;
    const int gameContainerHeight = 19;
    const int nextContainerHeight = 17;

    void render() override;

    public:
        ConsoleView(const DisplayProxy & displayProxy);
};

#endif
