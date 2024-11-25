#include "biquadris.h"
#include "./biquadris-proxies.h"

using CellCoordinate = std::pair<int, int>;
using BlockAttributes = std::pair<std::vector<CellCoordinate>, char>;
using CharGrid = std::vector<std::vector<char>>;

BiQuadris::BiQuadris(std::string sequenceFile1, std::string sequenceFile2, bool devMode, bool bonusFeatures, int initLevelNum) :
    devMode{devMode}, bonusFeatures{bonusFeatures}, gameStateProxy{*this}, visualEffectProxy{*this}, boardActionProxy{*this}, levelBlockGenProxy{*this}, displayProxy{*this}, 
    player1Board{this->gameStateProxy, initLevelNum, sequenceFile1}, player2Board{this->gameStateProxy, initLevelNum, sequenceFile2} {}



Board & BiQuadris::getPlayerBoard(PlayerTurn whichPlayerTurn) {
    return (whichPlayerTurn == PlayerTurn::PLAYER1) ? this->player1Board : this->player2Board;
}

Board & BiQuadris::getCurrentPlayerBoard() {
    return this->getPlayerBoard(this->currentPlayerTurn);
}

Board & BiQuadris::getCurrentPlayerOpponentBoard() {
    return this->getPlayerBoard((this->currentPlayerTurn == PlayerTurn::PLAYER1) ? PlayerTurn::PLAYER2 : PlayerTurn::PLAYER1);
}

// LOGIC NOT DONE YET
void BiQuadris::moveBlockLeft(int multiplier) {
    this->getCurrentPlayerBoard().moveBlockLeft(multiplier);
}

void BiQuadris::moveBlockRight(int multiplier) {
    this->getCurrentPlayerBoard().moveBlockRight(multiplier);
}

void BiQuadris::moveBlockDown(int multiplier) {
    this->getCurrentPlayerBoard().moveBlockDown(multiplier);
}

void BiQuadris::rotateBlockClockwise(int multiplier) {
    this->getCurrentPlayerBoard().rotateBlockClockwise(multiplier);
}

void BiQuadris::rotateBlockCounterClockwise(int multiplier) {
    this->getCurrentPlayerBoard().rotateBlockCounterClockwise(multiplier);
}
void BiQuadris::dropBlock(int multiplier) {
    this->getCurrentPlayerBoard().dropBlock(multiplier);
}

void BiQuadris::holdBlock() {
    this->getCurrentPlayerBoard().holdBlock();
}

void BiQuadris::restartBoards() {
    this->player1Board.restart();
    this->player2Board.restart();
}

void BiQuadris::levelUp(int multiplier) {
    this->getCurrentPlayerBoard().levelUp(multiplier);
}

void BiQuadris::levelDown(int multiplier) {
    this->getCurrentPlayerBoard().levelDown(multiplier);
}

void BiQuadris::replaceCurrentBlock(char blockType) {
    this->getCurrentPlayerBoard().replaceCurrentBlock(blockType);
}

void BiQuadris::enableRandom() {
    this->getCurrentPlayerBoard().setLevelRandomEnabled(true);
}

void BiQuadris::disableRandom(std::string blockSequenceFile) {
    this->getCurrentPlayerBoard().setLevelRandomEnabled(false);
    // come back later
}

BlockAttributes BiQuadris::getCurrentBlockAttributes(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getCurrentBlockAttributes();
}

BlockAttributes BiQuadris::getNextBlockAttributes(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getNextBlockAttributes();
}

BlockAttributes BiQuadris::getHeldBlockAttributes(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getHeldBlockAttributes();
}

// vector<BlockAttributes> BiQuadris::getBlockBacklog(int whichBoard) const {
    
// }

int BiQuadris::getCurrentScore(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getCurrentScore();
}

int BiQuadris::getHighScore(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getHighScore();
}

int BiQuadris::getLevelNum(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getLevelNum();
}

bool BiQuadris::getIsGameOver() const {
    return this->isGameOver;
}

BiQuadris::PlayerTurn BiQuadris::getCurrentPlayerTurn() const {
    return this->currentPlayerTurn;
}

bool BiQuadris::getCanUseSpecialAction() const {
    return this->canUseSpecialAction;
}


// setters
void BiQuadris::setBonusFeatures(bool isOn) {
    this->bonusFeatures = isOn;
}

void BiQuadris::setDevMode(bool isOn) {
    this->devMode = isOn;
}

// void BiQuadris::blindEffect() {
//     if (this->currentBoardTurn == 1) {
//         this->board1.setBlindEffect();
//     } else {
//         this->board2.setBlindEffect();
//     }
// }

void BiQuadris::heavyEffect() {
    this->getCurrentPlayerOpponentBoard().setHeavyEffect();
}

// void BiQuadris::forceEffect(char blockType) {

// }


