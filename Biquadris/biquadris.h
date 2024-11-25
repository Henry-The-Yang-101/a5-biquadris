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
    void disableRandom(std::string blockSequenceFile);
    void replaceCurrentBlock(char blockType);

    // effects
    void blindEffect();
    void heavyEffect();
    void forceEffect(char blockType);

    // getters
    BlockAttributes getCurrentBlockAttributes(PlayerTurn whichPlayerTurn) const;
    BlockAttributes getNextBlockAttributes(PlayerTurn whichPlayerTurn) const;
    BlockAttributes getHeldBlockAttributes(PlayerTurn whichPlayerTurn) const;
    std::vector<BlockAttributes> getBlockAttributesBacklog(PlayerTurn whichPlayerTurn) const;
    int getCurrentScore(PlayerTurn whichPlayerTurn) const;
    int getHighScore(PlayerTurn whichPlayerTurn) const;
    int getLevelNum(PlayerTurn whichPlayerTurn) const;
    bool getIsGameOver() const;
    PlayerTurn getCurrentPlayerTurn() const;
    bool getCanUseSpecialAction() const;

    // setters
    void setBonusFeatures(bool isOn);
    void setDevMode(bool isOn);
    void informCurrentBoardPlacedBlock(int rowsCleared);
    void informGameOver();

    ~BiQuadris();
  
  private:
    PlayerTurn currentPlayerTurn = PlayerTurn::PLAYER1;
    bool devMode;
    bool bonusFeatures;
    bool isGameOver = false;
    bool canUseSpecialAction = false;

    ManageGameStateProxy gameStateProxy;
    VisualEffectProxy visualEffectProxy;
    BoardActionProxy boardActionProxy;
    LevelBlockGenProxy levelBlockGenProxy;
    DisplayProxy displayProxy;

    Board player1Board;
    Board player2Board;

    Board & getPlayerBoard(PlayerTurn whichPlayerTurn);
    Board & getCurrentPlayerBoard();
    Board & getCurrentPlayerOpponentBoard();
};

class BiQuadrisProxy {
  protected:
    BiQuadris & gameEngine;
    BiQuadrisProxy(BiQuadris & gameEngine) : gameEngine{gameEngine} {}
    virtual ~BiQuadrisProxy() = default;
};

#endif
