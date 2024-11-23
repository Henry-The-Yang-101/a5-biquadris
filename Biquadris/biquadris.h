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
  bool devMode;
  bool bonusFeatures;
  bool gameOver = false;
  bool canUseSpecialAction = false;

  public:
    BiQuadris(bool devMode = false, bool bonusFeatures = true, int randomSeed = 0);

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
    Grid getGrid(int whichBoard) const;
    BlockAttributes getCurrentBlockAttributes(int whichBoard) const;
    BlockAttributes getNextBlockAttributes(int whichBoard) const;
    BlockAttributes getHeldBlockAttributes(int whichBoard) const;
    vector<BlockAttributes> getBlockBacklog(int whichBoard) const;
    int getCurrentScore(int whichBoard) const;
    int getHighScore(int whichBoard) const;
    bool getIsGameOver() const;
    int getCurrentBoardTurn() const;
    bool getCanUseSpecialAction() const;

    // setters
    void setBonusFeatures(bool isOn);
    void setDevFeatures(bool isOn);
    void gameOver();

    ~BiQuadris();
};

class BiQuadrisProxy {
  BiQuadris & gameEngine;
  BiQuadrisProxy(BiQuadris gameEngine) : gameEngine{gameEngine} {}
  ~BiQuadrisProxy() = default;
};
