#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Miscellaneous/subject.h"
// include board.h when its ready
#include "./Board/board.h"

using namespace std;
using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using Grid = vector<vector<char>>;

class BiQuadris : public Subject {
  
  int currentBoardTurn = 1;
  bool devMode;
  bool bonusFeatures;
  bool isGameOver = false;
  bool canUseSpecialAction = false;

  ManageGameStateProxy game;
  VisualEffectProxy visualEffectProxy;
  BoardActionProxy boardActionProxy;
  LevelBlockGenProxy levelBlockGenProxy;
  DisplayProxy displayProxy;

  Board board1;
  Board board2;

  public:
    BiQuadris(string sequenceFile1 = "sequence1.txt", string sequenceFile2 = "sequence2.txt", bool devMode = false, bool bonusFeatures = true, int randomSeed = 0, int board1Lvl, int board2Lvl);

    void moveBlockLeft(int multiplier);
    void moveBlockRight(int multiplier);
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
    vector<BlockAttributes> getBlockAttributesBacklog(int whichBoard) const;
    int getCurrentScore(int whichBoard) const;
    int getHighScore(int whichBoard) const;
    int getLevel(int whichBoard) const;
    bool getIsGameOver() const;
    int getCurrentBoardTurn() const;
    bool getCanUseSpecialAction() const;

    // setters
    void setBonusFeatures(bool isOn);
    void setDevMode(bool isOn);
    void informCurrentBoardPlacedBlock(int rowsCleared);
    void informGameOver();

    ~BiQuadris();
};

class BiQuadrisProxy {
  protected:
    BiQuadris & gameEngine;
    BiQuadrisProxy(BiQuadris & gameEngine) : gameEngine{gameEngine} {}
    virtual ~BiQuadrisProxy() = default;
};

#endif
