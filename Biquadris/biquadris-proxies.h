#ifndef BIQUADRIS_PROXIES_H
#define BIQUADRIS_PROXIES_H

#include "biquadris.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using BlockAttributes = std::pair<BlockCellCoordinates, char>;
using CharGrid = std::vector<std::vector<char>>;

class ManageGameStateProxy : public BiQuadrisProxy {
  public:
    ManageGameStateProxy(BiQuadris & gameEngine);

    void setBonusFeatures(bool isOn);
    void setDevMode(bool isOn);
    void informCurrentBoardPlacedBlock(int rowsCleared);
    void informGameOver();
};

class VisualEffectProxy : public BiQuadrisProxy {
  public:
    VisualEffectProxy(BiQuadris & gameEngine);

    void blindEffect();
};

class BoardActionProxy : public BiQuadrisProxy {
  public:
    BoardActionProxy(BiQuadris & gameEngine);

    void moveBlockLeft(int multiplier);
    void moveBlockRight(int multiplier);
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

    CharGrid getGrid(int whichBoard) const;
    BlockAttributes getCurrentBlockAttributes(int whichBoard) const;
    BlockAttributes getCurrentBlockDropPreviewAttributes(int whichBoard) const;
    BlockAttributes getNextBlockAttributes(int whichBoard) const;
    BlockAttributes getHeldBlockAttributes(int whichBoard) const;
    
    std::vector<BlockAttributes> getBlockAttributesBacklog(int whichBoard) const;
    int getCurrentScore(int whichBoard) const;
    int getHighScore(int whichBoard) const;
    int getLevel(int whichBoard) const;
    bool getIsGameOver() const;
    int getCurrentBoardTurn() const;
    bool getCanUseSpecialAction() const;
};

#endif
