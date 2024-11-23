#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Miscellaneous/subject.h"
// include board.h when its ready

using namespace std;
using CellCoords = pair<int, int>;
using BlockAttributes = pair<vector<CellCoords>, char>;
using Grid = vector<vector<char>>;

class BiQuadris : public Subject {
  //Board board1
  //Board board2
  int currentBoardTurn = 1;
  bool devMode;
  bool bonusFeatures;
  bool isGameOver = false;
  bool canUseSpecialAction = false;

  public:
    BiQuadris(string sequenceFile1 = "sequence1.txt", string sequenceFile2 = "sequence2.txt", bool devMode = false, bool bonusFeatures = true, int randomSeed = 0);

    void moveBlockHorizontal(int multiplier);
    void moveBlockDown(int multiplier);
    void rotateBlockClockwise(int multiplier);
    void rotateBlockCounterClockwise(int multiplier);
    void dropBlock(int multiplier);
    void holdBlock();
    void restartBoard();
    void levelUp(int multiplier);
    void levelDown(int multiplier);
    void enableRandom();
    void disableRandom(string blockSequenceFile);
    void replaceCurrentBlock(char blockType);

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
    void setDevMode(bool isOn);
    void gameOver();

    ~BiQuadris();
};

class BiQuadrisProxy {
  protected:
    BiQuadris & gameEngine;
    BiQuadrisProxy(BiQuadris & gameEngine) : gameEngine{gameEngine} {}
    virtual ~BiQuadrisProxy() = default;
};

#endif
