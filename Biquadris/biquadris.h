#ifndef BIQUADRIS_H
#define BIQUADRIS_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "../Miscellaneous/subject.h"
#include "./Board/board.h"

using CellCoordinate = std::pair<int, int>;
using BlockAttributes = std::pair<std::vector<CellCoordinate>, char>;

class BiQuadris : public Subject {
  public:
    BiQuadris(std::string sequenceFile1 = "sequence1.txt", std::string sequenceFile2 = "sequence2.txt", bool devMode = false, bool bonusFeatures = true, int initLevelNum = 0);
    enum class PlayerTurn {PLAYER1, PLAYER2};

    void moveBlockLeft(int multiplier);
    void moveBlockRight(int multiplier);
    void moveBlockDown(int multiplier);
    void rotateBlockClockwise(int multiplier);
    void rotateBlockCounterClockwise(int multiplier);
    void dropBlock(int multiplier);
    void holdBlock();
    void restartBoards();
    void levelUp(int multiplier);
    void levelDown(int multiplier);
    void enableRandom();
    void disableRandom();
    void disableRandom(std::string & blockSequenceFile);
    void replaceCurrentBlock(char blockType);

    // effects
    void blindEffect();
    void heavyEffect();
    void forceEffect(char blockType);

    // getters
    BlockCellCoordinates getCurrentBlockDropPreviewCellCoordinates(PlayerTurn whichPlayerTurn) const;
    BlockAttributes getCurrentBlockAttributes(PlayerTurn whichPlayerTurn) const;
    BlockAttributes getNextBlockAttributes(PlayerTurn whichPlayerTurn) const;
    BlockAttributes getHeldBlockAttributes(PlayerTurn whichPlayerTurn) const;
    std::vector<BlockAttributes> getBlockAttributesBacklog(PlayerTurn whichPlayerTurn) const;
    int getCurrentScore(PlayerTurn whichPlayerTurn) const;
    int getHighScore(PlayerTurn whichPlayerTurn) const;
    int getLevelNum(PlayerTurn whichPlayerTurn) const;
    bool getBlindEffectEnabled(PlayerTurn whichPlayerTurn) const;
    bool getIsGameOver() const;
    PlayerTurn getCurrentPlayerTurn() const;
    bool getCanUseSpecialAction() const;

    // mutators
    void setBonusFeatures(bool isOn);
    void setDevMode(bool isOn);
    void informCurrentBoardPlacedBlock(int rowsCleared);
    void informGameOver();
    void endSpecialActionMove();

    ~BiQuadris();
  
  private:
    static const int MIN_REQUIRED_ROWS_CLEARED_TO_TRIGGER_SPECIAL_ACTION = 2;

    InformGameStateProxy informGameStateProxy;

    Board player1Board;
    Board player2Board;

    // Game State variables
    PlayerTurn currentPlayerTurn = PlayerTurn::PLAYER1;
    bool devMode = true;
    bool bonusFeatures = true;
    bool isGameOver = false;
    bool canUseSpecialAction = false;
    bool currentBoardPlacedBlockThisMove = false;
    int currentBoardNumRowsClearedThisMove;

    // Helper methods:
    static PlayerTurn getOpponentTurn(PlayerTurn whichPlayerTurn);
    const Board & getPlayerBoard(PlayerTurn whichPlayerTurn) const;
    Board & getPlayerBoard(PlayerTurn whichPlayerTurn);
    Board & getCurrentPlayerBoard();
    Board & getCurrentPlayerOpponentBoard();

    // Game State assertions
    void assertNotGameOver() const;
    void assertBonusFeaturesOn() const;
    void assertDevModeOn() const;
    void assertBoardActionMove() const;
    void assertSpecialActionMove() const;

    void updateGameStateAfterBlockAction();
};

class BiQuadrisProxy {
  protected:
    BiQuadris & gameEngine;
    BiQuadrisProxy(BiQuadris & gameEngine) : gameEngine{gameEngine} {}
    virtual ~BiQuadrisProxy() = default;
};

#endif
