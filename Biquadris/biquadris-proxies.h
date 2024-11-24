#ifndef BIQUADRIS_PROXIES_H
#define BIQUADRIS_PROXIES_H

#include "biquadris.h"

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using Grid = vector<vector<char>>;

class ManageGameStateProxy : public BiQuadrisProxy {
  public:
    ManageGameStateProxy(BiQuadris & gameEngine);

    void setBonusFeatures(bool isOn);
    void setDevMode(bool isOn);
    void gameOver();
};

class VisualEffectProxy : public BiQuadrisProxy {
  public:
    VisualEffectProxy(BiQuadris & gameEngine);

    void blindEffect();
};

class BoardActionProxy : public BiQuadrisProxy {
  public:
    BoardActionProxy(BiQuadris & gameEngine);

    void moveBlockHorizontal(int multiplier);
    void moveBlockDown(int multiplier);
    void rotateBlockClockwise(int multiplier);
    void rotateBlockCounterClockwise(int multiplier);
    void dropBlock(int multiplier);
    void holdBlock();
    void restartBoard();
    void heavyEffect();
};

class LevelBlockGenProxy : public BiQuadrisProxy {
  public:
    LevelBlockGenProxy(BiQuadris & gameEngine);

    void levelUp(int multiplier);
    void levelDown(int multiplier);
    void enableRandom();
    void disableRandom(std::string blockSequenceFile);
    void replaceCurrentBlock(char blockType);
    void forceEffect(char blockType);
};


class DisplayProxy : public BiQuadrisProxy {
  public:
    DisplayProxy(BiQuadris & gameEngine);

    Grid getGrid(int whichBoard) const;
    BlockAttributes getCurrentBlockAttributes(int whichBoard) const;
    BlockAttributes getNextBlockAttributes(int whichBoard) const;
    BlockAttributes getHeldBlockAttributes(int whichBoard) const;
    vector<BlockAttributes> getBlockBacklog(int whichBoard) const;
    int getCurrentScore(int whichBoard) const;
    int getHighScore(int whichBoard) const;
    int getLevel(int whichBoard) const;
    bool getIsGameOver() const;
    int getCurrentBoardTurn() const;
    bool getCanUseSpecialAction() const;
};

#endif
