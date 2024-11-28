#include <iostream>
#include <string>
#include "display-observer.h"

using namespace std;

DisplayObserver::DisplayObserver(const DisplayProxy & displayProxy)
    : displayProxy{displayProxy} {
    p1GameGrid = displayProxy.getCharGrid(BiQuadris::PlayerTurn::PLAYER1);
    p2GameGrid = displayProxy.getCharGrid(BiQuadris::PlayerTurn::PLAYER2);

    //get current blocks from display proxy
    BlockAttributes p1CurBlock = displayProxy.getCurrentBlockAttributes(BiQuadris::PlayerTurn::PLAYER1);
    BlockAttributes p2CurBlock = displayProxy.getCurrentBlockAttributes(BiQuadris::PlayerTurn::PLAYER2);

    for (int i = 0; i < p1CurBlock.first.size(); i++) {
        p1GameGrid[p1CurBlock.first[i].second + reserveRowHeight][p1CurBlock.first[i].first] = p1CurBlock.second;
    }

    for (int i = 0; i < p2CurBlock.first.size(); i++) {
        p2GameGrid[p2CurBlock.first[i].second + reserveRowHeight][p2CurBlock.first[i].first] = p2CurBlock.second;
    }

    if (displayProxy.getBlindEffectEnabled(BiQuadris::PlayerTurn::PLAYER1)) {
        for (int r = blindRowStart; r <= blindRowEnd; r++) {
            for (int c = blindColStart; c <= blindColEnd; c++) {
                p1GameGrid[r][c] = blindEffectChar;
            }
        }
    }

    if (displayProxy.getBlindEffectEnabled(BiQuadris::PlayerTurn::PLAYER2)) {
        for (int r = blindRowStart; r <= blindRowEnd; r++) {
            for (int c = blindColStart; c <= blindColEnd; c++) {
                p2GameGrid[r][c] = blindEffectChar;
            }
        }
    }


    if (displayProxy.getBonusFeaturesEnabled()) {
        //get preivew block coordinates
        BlockCellCoordinates p1PreviewBlock = displayProxy.getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn::PLAYER1);
        BlockCellCoordinates p2PreviewBlock = displayProxy.getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn::PLAYER2);

        for (int i = 0; i < p1PreviewBlock.size(); i++) {
            p1GameGrid[p1PreviewBlock[i].second + reserveRowHeight][p1PreviewBlock[i].first] = blockPreviewChar;
        }

        for (int i = 0; i < p2PreviewBlock.size(); i++) {
            p2GameGrid[p2PreviewBlock[i].second + reserveRowHeight][p2PreviewBlock[i].first] = blockPreviewChar;
        }

        // initialize hold grid with empty space characters
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

        // retrieve held blocks from game engine
        BlockAttributes p1HoldBlock = displayProxy.getHeldBlockAttributes(BiQuadris::PlayerTurn::PLAYER1);
        BlockAttributes p2HoldBlock = displayProxy.getHeldBlockAttributes(BiQuadris::PlayerTurn::PLAYER2);

        // add held blocks to hold grid
        for (int i = 0; i < p1HoldBlock.first.size(); i++) {
            p1HoldGrid[p1HoldBlock.first[i].second + blockCoordAdjustment][p1HoldBlock.first[i].first] = p1HoldBlock.second;
        }
        for (int i = 0; i < p2HoldBlock.first.size(); i++) {
            p2HoldGrid[p2HoldBlock.first[i].second + blockCoordAdjustment][p2HoldBlock.first[i].first] = p2HoldBlock.second;
        }

        // initialize next grid with empty spaces
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

        // retrieve block queue from game engine
        vector<BlockAttributes> p1NextQueue = displayProxy.getBlockAttributesBacklog(BiQuadris::PlayerTurn::PLAYER1);
        vector<BlockAttributes> p2NextQueue = displayProxy.getBlockAttributesBacklog(BiQuadris::PlayerTurn::PLAYER2);

        // add blocks in queue to the next grid
        int rowShift = 0;
        for (const auto &nextBlock : p1NextQueue) {
            for (const auto &coord : nextBlock.first) {
                p1NextGrid[coord.second + blockCoordAdjustment + rowShift][coord.first] = nextBlock.second;
            }
            rowShift += 3;
        }

        rowShift = 0;
        for (const auto &nextBlock : p2NextQueue) {
            for (const auto &coord : nextBlock.first) {
                p2NextGrid[coord.second + blockCoordAdjustment + rowShift][coord.first] = nextBlock.second;
            }
            rowShift += 3;
        }

    } else {
        // initialize next grid with empty spaces
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

        // retrieve next blocks from game engine
        BlockAttributes p1NextBlock = displayProxy.getNextBlockAttributes(BiQuadris::PlayerTurn::PLAYER1);
        BlockAttributes p2NextBlock = displayProxy.getNextBlockAttributes(BiQuadris::PlayerTurn::PLAYER2);

        // add next blocks to next grid
        for (const auto &coord : p1NextBlock.first) {
            p1NextGrid[coord.second + blockCoordAdjustment][coord.first] = p1NextBlock.second;
        }
        for (const auto &coord : p2NextBlock.first) {
            p2NextGrid[coord.second + blockCoordAdjustment][coord.first] = p2NextBlock.second;
        }
    }
}

void DisplayObserver::notify() {
    this->render();
}
