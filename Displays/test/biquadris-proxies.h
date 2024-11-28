#ifndef BIQUADRIS_PROXIES_H
#define BIQUADRIS_PROXIES_H

#include "biquadris.h"

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using CharGrid = vector<vector<char>>;


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
