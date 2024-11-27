#include <iostream>
#include <string>
#include "console-view.h"

using namespace std;

ConsoleView::ConsoleView(const DisplayProxy & displayProxy, bool enhanced): 
    DisplayObserver{displayProxy, enhanced} {}

void ConsoleView::render() {

    if (enhanced) {
        
        //printing player and top padding of board
        cout << endl;
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        if (displayProxy.getCurrentBoardTurn() == 1) {
            for (int i = 0; i < (gameContainerWidth - 18)/2; i++) cout << " ";
            cout << "-->  Player 1  <--";
            for (int i = 0; i < (gameContainerWidth - 18)/2 + 1; i++) cout << " ";
        } else {
            for (int i = 0; i < (gameContainerWidth - 8)/2; i++) cout << " ";
            cout << "Player 1";
            for (int i = 0; i < (gameContainerWidth - 8)/2 + 1; i++) cout << " ";
        }
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding + holdContainerWidth; i++) cout << " ";
        if (displayProxy.getCurrentBoardTurn() == 2) {
            for (int i = 0; i < (gameContainerWidth - 18)/2; i++) cout << " ";
            cout << "-->  Player 2  <--";
            for (int i = 0; i < (gameContainerWidth - 18)/2 + 1; i++) cout << " ";
        } else {
            for (int i = 0; i < (gameContainerWidth - 8)/2; i++) cout << " ";
            cout << "Player 2";
            for (int i = 0; i < (gameContainerWidth - 8)/2 + 1; i++) cout << " ";
        }
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

            //player 1
            
            //hold container
            if (r == 0) {
                cout << "|";
                for (int i = 0; i < (holdContainerWidth-6)/2; i++) cout << " ";
                cout << "Hold:";
                for (int i = 0; i < (holdContainerWidth-6)/2; i++) cout << " ";
            } else if (r == 1) {
                cout << "|";
                for (int i = 0; i < holdContainerWidth-1; i++) cout << " ";
            } else if ( r >= 2 && r <= 3) {
                cout << "|";
                for (int i = 0; i < (holdContainerWidth-4)/2; i++) cout << " ";
                for (int c = 0; c < holdGridCols; c++) {
                    cout << p1HoldGrid[r-2][c];
                }
                for (int i = 0; i < (holdContainerWidth-4)/2 - 1; i++) cout << " ";
            } else if (r == 4) {
                cout << "|";
                for (int i = 0; i < holdContainerWidth-1; i++) {
                    cout << "_";
                }
            } else {
                for (int i = 0; i < holdContainerWidth; i++) cout << " ";
            }

            //main game board
            cout << "|";
            for (int c = 0; c < gameGridCols; c++) {
                cout << p1GameGrid[r][c];
                if (c != gameGridCols - 1) {
                    cout << " ";
                }
            }
            cout << "|";

            //next container
             if (r == 0) {
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "Next:";
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "|";
            } else if (r == 1) {
                for (int i = 0; i < nextContainerWidth-1; i++) cout << " ";
                cout << "|";
            } else if (r == 4) {
                for (int i = 0; i < nextContainerWidth-1; i++) {
                    cout << "―";
                }
                cout << "|";   
            } else if ( r >= 2 && r <= 15) {
                for (int i = 0; i < (nextContainerWidth-4)/2; i++) cout << " ";
                for (int c = 0; c < nextGridCols; c++) {
                    cout << p1NextGrid[r-2][c];
                }
                for (int i = 0; i < (nextContainerWidth-4)/2 - 1; i++) cout << " ";
                cout << "|";
            } else if (r == 16) {
                for (int i = 0; i < nextContainerWidth-1; i++) {
                    cout << "_";
                }
                cout << "|";
            } else {
                for (int i = 0; i < holdContainerWidth; i++) cout << " ";
            }


            for (int i = 0; i < leftInteriorPadding; i++) cout << " ";
            cout << "|";


            //player 2

            for (int i = 0; i < rightInteriorPadding; i++) cout << " ";

            //hold container
            if (r == 0) {
                cout << "|";
                for (int i = 0; i < (holdContainerWidth-6)/2; i++) cout << " ";
                cout << "Hold:";
                for (int i = 0; i < (holdContainerWidth-6)/2; i++) cout << " ";
            } else if (r == 1) {
                cout << "|";
                for (int i = 0; i < holdContainerWidth-1; i++) cout << " ";
            } else if ( r >= 2 && r <= 3) {
                cout << "|";
                for (int i = 0; i < (holdContainerWidth-4)/2; i++) cout << " ";
                for (int c = 0; c < holdGridCols; c++) {
                    cout << p2HoldGrid[r-2][c];
                }
                for (int i = 0; i < (holdContainerWidth-4)/2 - 1; i++) cout << " ";
            } else if (r == 4) {
                cout << "|";
                for (int i = 0; i < holdContainerWidth-1; i++) {
                    cout << "_";
                }
            } else {
                for (int i = 0; i < holdContainerWidth; i++) cout << " ";
            }

            //main game board
            cout << "|";
            for (int c = 0; c < gameGridCols; c++) {
                cout << p2GameGrid[r][c];
                if (c != gameGridCols - 1) {
                    // change to space later, using | for readability
                    cout << " ";
                }
            }
            cout << "|";

            //next container
             if (r == 0) {
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "Next:";
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "|";
            } else if (r == 1) {
                for (int i = 0; i < nextContainerWidth-1; i++) cout << " ";
                cout << "|";
            } else if (r == 4) {
                for (int i = 0; i < nextContainerWidth-1; i++) {
                    cout << "―";
                }
                cout << "|";   
            } else if ( r >= 2 && r <= 15) {
                for (int i = 0; i < (nextContainerWidth-4)/2; i++) cout << " ";
                for (int c = 0; c < nextGridCols; c++) {
                    cout << p2NextGrid[r-2][c];
                }
                for (int i = 0; i < (nextContainerWidth-4)/2 - 1; i++) cout << " ";
                cout << "|";
            } else if (r == 16) {
                for (int i = 0; i < nextContainerWidth-1; i++) {
                    cout << "_";
                }
                cout << "|";
            } else {
                for (int i = 0; i < holdContainerWidth; i++) cout << " ";
            }
            cout << endl;

        }

        //printing bottom
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "―";
        cout << "|";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding + holdContainerWidth; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "―";
        cout << "|";
        cout << endl;

        cout << endl;
        for (int i = 0; i < (holdContainerWidth + gameContainerWidth + nextContainerWidth) * 2 + leftInteriorPadding + rightInteriorPadding + 1; i ++) {
            cout << "―";
        }
        cout << endl;

    } else {

        //printing player and top padding of board
        cout << endl;
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        for (int i = 0; i < (gameContainerWidth - 8)/2; i++) cout << " ";
        cout << "Player 1";
        for (int i = 0; i < (gameContainerWidth - 8)/2 + 1; i++) cout << " ";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding + holdContainerWidth; i++) cout << " ";
        for (int i = 0; i < (gameContainerWidth - 8)/2; i++) cout << " ";
        cout << "Player 2";
        for (int i = 0; i < (gameContainerWidth - 8)/2 + 1; i++) cout << " ";
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
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "_";
        cout << "|";
        for (int i = 0; i < nextContainerWidth; i++) cout << "_";
        for (int i = 0; i < leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding; i++) cout << " ";
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "_";
        cout << "|";
        for (int i = 0; i < nextContainerWidth; i++) cout << "_";
        cout << endl;

        //printing game area
        for (int r = 0; r < gameGridRows; r++) {

            //player 1
            
            //hold container
            for (int i = 0; i < holdContainerWidth; i++) cout << " ";

            //main game board
            cout << "|";
            for (int c = 0; c < gameGridCols; c++) {
                cout << p1GameGrid[r][c];
                if (c != gameGridCols - 1) {
                    cout << " ";
                }
            }
            cout << "|";

            //next container
             if (r == 0) {
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "Next:";
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "|";
            } else if (r == 1) {
                for (int i = 0; i < nextContainerWidth-1; i++) cout << " ";
                cout << "|";
            } else if (r == 4) {
                for (int i = 0; i < nextContainerWidth-1; i++) {
                    cout << "_";
                }
                cout << "|";   
            } else if ( r >= 2 && r <= 3) {
                for (int i = 0; i < (nextContainerWidth-4)/2; i++) cout << " ";
                for (int c = 0; c < nextGridCols; c++) {
                    cout << p1NextGrid[r-2][c];
                }
                for (int i = 0; i < (nextContainerWidth-4)/2 - 1; i++) cout << " ";
                cout << "|";
            } else {
                for (int i = 0; i < holdContainerWidth; i++) cout << " ";
            }


            for (int i = 0; i < leftInteriorPadding; i++) cout << " ";
            cout << "|";


            //player 2

            for (int i = 0; i < rightInteriorPadding; i++) cout << " ";

            //hold container
            for (int i = 0; i < holdContainerWidth; i++) cout << " ";

            //main game board
            cout << "|";
            for (int c = 0; c < gameGridCols; c++) {
                cout << p2GameGrid[r][c];
                if (c != gameGridCols - 1) {
                    // change to space later, using | for readability
                    cout << " ";
                }
            }
            cout << "|";

            //next container
             if (r == 0) {
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "Next:";
                for (int i = 0; i < (nextContainerWidth-6)/2; i++) cout << " ";
                cout << "|";
            } else if (r == 1) {
                for (int i = 0; i < nextContainerWidth-1; i++) cout << " ";
                cout << "|";
            } else if (r == 4) {
                for (int i = 0; i < nextContainerWidth-1; i++) {
                    cout << "_";
                }
                cout << "|";   
            } else if ( r >= 2 && r <= 3) {
                for (int i = 0; i < (nextContainerWidth-4)/2; i++) cout << " ";
                for (int c = 0; c < nextGridCols; c++) {
                    cout << p2NextGrid[r-2][c];
                }
                for (int i = 0; i < (nextContainerWidth-4)/2 - 1; i++) cout << " ";
                cout << "|";
            } else {
                for (int i = 0; i < holdContainerWidth; i++) cout << " ";
            }
            cout << endl;

        }

        //printing bottom
        for (int i = 0; i < holdContainerWidth; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "―";
        cout << "|";
        for (int i = 0; i < nextContainerWidth + leftInteriorPadding; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < rightInteriorPadding + holdContainerWidth; i++) cout << " ";
        cout << "|";
        for (int i = 0; i < gameContainerWidth-2; i++) cout << "―";
        cout << "|";
        cout << endl;

        cout << endl;
        for (int i = 0; i < (holdContainerWidth + gameContainerWidth + nextContainerWidth) * 2 + leftInteriorPadding + rightInteriorPadding + 1; i ++) {
            cout << "―";
        }
        cout << endl;

    }
}