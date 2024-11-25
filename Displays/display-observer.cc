#include <iostream>
#include <string>
#include "display-observer.h"

using namespace std;

DisplayObserver::DisplayObserver(DisplayProxy &displayProxy, bool enhanced): displayProxy{displayProxy}, enhanced{enhanced}  {
    p1GameGrid = displayProxy.getGrid(1);
    p2GameGrid = displayProxy.getGrid(2);

    if (enhanced) {
        //initialize hold grid with empty space characters
        for (int r = 0; r < holdGridRows; r++) {
            vector<char> temp1;
            vector<char> temp2;
            p1HoldGrid.emplace_back(temp1);
            p2HoldGrid.emplace_back(temp2);
            for (int c = 0; c < holdGridCols; c++) {
                p1HoldGrid[r].emplace_back(' ');
                p2HoldGrid[r].emplace_back(' ');
            }
        }

        //retrieve held blocks from game engine
        BlockAttributes p1HoldBlock = displayProxy.getHeldBlockAttributes(1);
        BlockAttributes p2HoldBlock = displayProxy.getHeldBlockAttributes(2);

        //add held blocks to hold grid
        for (int i = 0; i < p1HoldBlock.first.size(); i++) {
            p1HoldGrid[p1HoldBlock.first[i].second + blockCoordAdjustment][p1HoldBlock.first[i].first] = p1HoldBlock.second;
        }
        for (int i = 0; i < p2HoldBlock.first.size(); i++) {
            p2HoldGrid[p2HoldBlock.first[i].second + blockCoordAdjustment][p2HoldBlock.first[i].first] = p2HoldBlock.second;
        }

        //intialize next grid with empty spaces
        for (int r = 0; r < enhancedNextGridRows; r++) {
            vector<char> temp1;
            vector<char> temp2;
            p1NextGrid.emplace_back(temp1);
            p2NextGrid.emplace_back(temp2);
            for (int c = 0; c < enhancedNextGridCols; c++) {
                if (r == 2) {
                    p1NextGrid[r].emplace_back('_');
                    p2NextGrid[r].emplace_back('_');
                } else {
                    p1NextGrid[r].emplace_back(' ');
                    p2NextGrid[r].emplace_back(' ');                    
                }
            }
        }

        //retrieve block queue from game engine
        vector<BlockAttributes> p1NextQueue= displayProxy.getBlockAttributesBacklog(1);
        vector<BlockAttributes> p2NextQueue = displayProxy.getBlockAttributesBacklog(2);

        //add blocks in queue to the next grid
        int rowShift = 0;
        for (int i = 0; i < p1NextQueue.size(); i++) {
            BlockAttributes nextBlock = p1NextQueue[i];
            for (int j = 0; j < nextBlock.first.size(); j++) {
                p1NextGrid[nextBlock.first[j].second + blockCoordAdjustment + rowShift][nextBlock.first[j].first] = nextBlock.second;
            }
            rowShift +=3;
        }

        rowShift = 0;
        for (int i = 0; i < p2NextQueue.size(); i++) {
            BlockAttributes nextBlock = p2NextQueue[i];
            for (int j = 0; j < nextBlock.first.size(); j++) {
                p2NextGrid[nextBlock.first[j].second + blockCoordAdjustment + rowShift][nextBlock.first[j].first] = nextBlock.second;
            }
            rowShift +=3;
        }

    } else {
        
        //intialize next grid with empty spaces
        for (int r = 0; r < nextGridRows; r++) {
            vector<char> temp1;
            vector<char> temp2;
            p1NextGrid.emplace_back(temp1);
            p2NextGrid.emplace_back(temp2);
            for (int c = 0; c < nextGridCols; c++) {
                p1NextGrid[r].emplace_back(' ');
                p2NextGrid[r].emplace_back(' ');
            }
        }

        //retrieve next blocks from game engine
        BlockAttributes p1NextBlock = displayProxy.getNextBlockAttributes(1);
        BlockAttributes p2NextBlock = displayProxy.getNextBlockAttributes(2);

        //add next blocks to next grid
        for (int i = 0; i < p1NextBlock.first.size(); i++) {
            p1NextGrid[p1NextBlock.first[i].second + blockCoordAdjustment][p1NextBlock.first[i].first] = p1NextBlock.second;
        }
        for (int i = 0; i < p2NextBlock.first.size(); i++) {
            p2NextGrid[p2NextBlock.first[i].second + blockCoordAdjustment][p2NextBlock.first[i].first] = p2NextBlock.second;
        }

    }

}

void DisplayObserver::render() {}

void DisplayObserver::notify() {
    this->render();
}