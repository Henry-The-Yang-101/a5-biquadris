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
    void endSpecialActionMove();
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
    void restartBoards();
    void heavyEffect();
};

class LevelBlockGenProxy : public BiQuadrisProxy {
  public:
    LevelBlockGenProxy(BiQuadris & gameEngine);

    void levelUp(int multiplier);
    void levelDown(int multiplier);
    void enableRandom();
    void disableRandom();
    void disableRandom(std::string blockSequenceFile);
    void replaceCurrentBlock(char blockType);
    void forceEffect(char blockType);
};

class DisplayProxy : public BiQuadrisProxy {
  public:
    DisplayProxy(BiQuadris & gameEngine);

    int getGridWidth() const;
    int getGridHeight() const;
    int getGridNumReserveRows() const;
    int getCurrentScore(BiQuadris::PlayerTurn whichPlayerTurn) const;
    int getHighScore(BiQuadris::PlayerTurn whichPlayerTurn) const;
    int getLevelNum(BiQuadris::PlayerTurn whichPlayerTurn) const;

    bool getBlindEffectEnabled(BiQuadris::PlayerTurn whichPlayerTurn) const;
    bool getIsGameOver() const;
    bool getCanUseSpecialAction() const;
    bool getBonusFeaturesEnabled() const;

    BiQuadris::PlayerTurn getCurrentPlayerTurn() const;

    CharGrid getCharGrid(BiQuadris::PlayerTurn whichPlayerTurn) const;

    BlockCellCoordinates getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn whichPlayerTurn) const;
    BlockAttributes getCurrentBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const;
    BlockAttributes getNextBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const;
    BlockAttributes getHeldBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const;
    
    std::vector<BlockAttributes> getBlockAttributesBacklog(BiQuadris::PlayerTurn whichPlayerTurn) const;
};

#endif
