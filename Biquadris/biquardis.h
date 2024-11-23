#include <iostream>
#include <vector>
#include <string>
#include "../Miscellaneous/subject.h"
// include board

using namespace std;
using CellCoords = pair<int, int>;
using BlockAttributes = pair<vector<CellCoords>, char>;
using Grid = vector<vector<char>>;

class BiQuadris : Subject {
  //Board board1
  //Board board2
  int currentBoardTurn = 1;
  bool devMode = false;
  bool bonusFeatures = true;
  bool gameOver = false;
  bool canUseSpecialAction = false;

  public:
    void moveBlockHorizontal(int);
    void moveBlockDown(int);
    void rotateBlockClockwise(int);
    void rotateBlockCounterClockwise(int);
    void dropBlock(int);
    void holdBlock();
    void restartBoard();
    void levelUp(int);
    void levelDown(int);
    void enableRandom();
    void disableRandom(string blockSequenceFile);
    void replaceCurrentBlock(char);

    // effects
    void blindEffect();
    void heavyEffect();
    void forceEffect(char blockType);

    // getters
    Grid getGrid(int whichBoard);
    BlockAttributes getCurrentBlockAttributes(int whichBoard);
    BlockAttributes getNextBlockAttributes(int whichBoard);
    BlockAttributes getHeldBlockAttributes(int whichBoard);
    vector<BlockAttributes> getBlockBacklog(int whichBoard);
    int getCurrentScore(int whichBoard);
    int getHighScore(int whichBoard);
    bool getIsGameOver();
    int getCurrentBoardTurn();
    bool getCanUseSpecialAction();

    // setters
    void setBonusFeatures(bool isOn);
    void setDevFeatures(bool isOn);
    void gameOver();

    ~BiQuadris();
};
