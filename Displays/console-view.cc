#include <iostream>
#include <string>
#include "console-view.h"

using namespace std;

ConsoleView::ConsoleView(DisplayProxy &displayProxy, bool enhanced): displayProxy{displayProxy}, enhanced{enhanced}  {
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
                p1HoldGrid[r].emplace_back(' ');
            }
        }

        //retrieve held blocks from game engine
        BlockAttributes p1HoldBlock = displayProxy.getHeldBlockAttributes(1);
        BlockAttributes p2HoldBlock = displayProxy.getHeldBlockAttributes(2);

        //add held blocks to hold grid
        for (int i = 0; i < p1HoldBlock.first.size(); i++) {
            p1HoldGrid[p1HoldBlock.first[i].first][p1HoldBlock.first[i].second] = p1HoldBlock.second;
        }
        for (int i = 0; i < p2HoldBlock.first.size(); i++) {
            p2HoldGrid[p2HoldBlock.first[i].first][p2HoldBlock.first[i].second] = p2HoldBlock.second;
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
        vector<BlockAttributes> p1NextQueue= displayProxy.getBlockBacklog(1);
        vector<BlockAttributes> p2NextQueue = displayProxy.getBlockBacklog(2);

        //add blocks in queue to the next grid
        int rowShift = 0;
        for (int i = 0; i < p1NextQueue.size(); i++) {
            BlockAttributes nextBlock = p1NextQueue[i];
            for (int j = 0; j < nextBlock.first.size(); j++) {
                p1NextGrid[nextBlock.first[j].first + rowShift][nextBlock.first[j].second] = nextBlock.second;
            }
            rowShift ++;
        }

        for (int i = 0; i < p2NextQueue.size(); i++) {
            BlockAttributes nextBlock = p2NextQueue[i];
            for (int j = 0; j < nextBlock.first.size(); j++) {
                p2NextGrid[nextBlock.first[j].first + rowShift][nextBlock.first[j].second] = nextBlock.second;
            }
            rowShift ++;
        }

    } else {
        
        //intialize next grid with empty spaces
        for (int r = 0; r < nextGridRows; r++) {
            vector<char> temp1;
            vector<char> temp2;
            p1NextGrid.emplace_back(temp1);
            p1NextGrid.emplace_back(temp2);
            for (int c = 0; c < nextGridCols; c++) {
                p1NextGrid[r].emplace_back(' ');
                p1NextGrid[r].emplace_back(' ');
            }
        }

        //retrieve next blocks from game engine
        BlockAttributes p1NextBlock = displayProxy.getNextBlockAttributes(1);
        BlockAttributes p2NextBlock = displayProxy.getNextBlockAttributes(2);

        //add next blocks to next grid
        for (int i = 0; i < p1NextBlock.first.size(); i++) {
            p1NextGrid[p1NextBlock.first[i].first][p1NextBlock.first[i].second] = p1NextBlock.second;
        }
        for (int i = 0; i < p2NextBlock.first.size(); i++) {
            p2NextGrid[p2NextBlock.first[i].first][p2NextBlock.first[i].second] = p2NextBlock.second;
        }

    }


}

void ConsoleView::notify() {
    this->render();
}

void ConsoleView::render() {
    if (enhanced) {
        
        //printing player and top padding of board
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        if (displayProxy.getCurrentBoardTurn() == 1) {
            cout << "   -->  Player 1  <--  ";
        } else {
            cout << "        Player 1       ";
        }
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding + holdContainerWidth; i++) cout << " ";
        if (displayProxy.getCurrentBoardTurn() == 2) {
            cout << "   -->  Player 2  <--  ";
        } else {
            cout << "        Player 2       ";
        }
        cout << endl;
        for (int i = 0; i < holdContainerWidth + gameContainerWidth + nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < holdContainerWidth + gameContainerWidth + nextContainerWidth + rightInteriorPadding; i++) cout << " ";
        cout << endl;

        //printing top border of game area
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        for (int i = 0; i < gameContainerWidth; i++) cout << "_";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding + holdContainerWidth; i++) cout << " ";
        for (int i = 0; i < gameContainerWidth; i++) cout << "_";
        cout << endl;

        //printing level text
        string p1LevelText = "Level: " + to_string(displayProxy.getLevel(1));
        string p2LevelText = "Level: " + to_string(displayProxy.getLevel(2));
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "| " << p1LevelText;
        for (int i = 0; i < gameContainerWidth - 3 - p1LevelText.length(); i++)  cout << " ";
        cout << "|";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < holdContainerWidth + rightInteriorPadding; i++) cout << " ";
        cout << "| " << p2LevelText;
        for (int i = 0; i < gameContainerWidth - 3 - p2LevelText.length(); i++)  cout << " ";
        cout << "|";
        cout << endl;

        //printing high score text
        string p1HighScoreText = "High Score: " + to_string(displayProxy.getHighScore(1));
        string p2HighScoreText = "High Score: " + to_string(displayProxy.getHighScore(2));
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "| " << p1HighScoreText;
        for (int i = 0; i < gameContainerWidth - 3 - p1HighScoreText.length(); i++)  cout << " ";
        cout << "|";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < holdContainerWidth + rightInteriorPadding; i++) cout << " ";
        cout << "| " << p2HighScoreText;
        for (int i = 0; i < gameContainerWidth - 3 - p2HighScoreText.length(); i++)  cout << " ";
        cout << "|";
        cout << endl; 

        //printing score text
        string p1ScoreText = "Score: " + to_string(displayProxy.getCurrentScore(1));
        string p2ScoreText = "Score: " + to_string(displayProxy.getCurrentScore(2));
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "| " << p1ScoreText;
        for (int i = 0; i < gameContainerWidth - 3 - p1ScoreText.length(); i++)  cout << " ";
        cout << "|";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < holdContainerWidth + rightInteriorPadding; i++) cout << " ";
        cout << "| " << p2ScoreText;
        for (int i = 0; i < gameContainerWidth - 3 - p2ScoreText.length(); i++)  cout << " ";
        cout << "|";
        cout << endl;        

        //printing game area lid
        for (int i = 0; i < holdContainerWidth; i++) cout << "_";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "_";
        cout << "|";
        for (int i = 0; i < nextContainerWidth; i++) cout << "_";
        for (int i = 0; i < leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding; i++) cout << " ";
        for (int i = 0; i < holdContainerWidth; i++) cout << "_";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "_";
        cout << "|";
        for (int i = 0; i < nextContainerWidth; i++) cout << "_";
        cout << endl;

        //printing game area
        for (int r = 0; r < gameGridRows; r++) {

        }

    } else {

    }
}