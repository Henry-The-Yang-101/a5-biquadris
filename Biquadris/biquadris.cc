#include <iostream>
#include <stdexcept>
#include "biquadris.h"
#include "./biquadris-proxies.h"

using CellCoordinate = std::pair<int, int>;
using BlockAttributes = std::pair<std::vector<CellCoordinate>, char>;
using CharGrid = std::vector<std::vector<char>>;

BiQuadris::BiQuadris(std::string sequenceFile1, std::string sequenceFile2, bool devMode, bool bonusFeatures, int initLevelNum) :
    devMode{devMode}, bonusFeatures{bonusFeatures}, informGameStateProxy{*this}, 
    player1Board{this->informGameStateProxy, initLevelNum, sequenceFile1}, player2Board{this->informGameStateProxy, initLevelNum, sequenceFile2} {}


BiQuadris::PlayerTurn BiQuadris::getOpponentTurn(PlayerTurn whichPlayerTurn) {
    return (whichPlayerTurn == PlayerTurn::PLAYER1) ? PlayerTurn::PLAYER2 : PlayerTurn::PLAYER1;
}

const Board & BiQuadris::getPlayerBoard(PlayerTurn whichPlayerTurn) const {
    return (whichPlayerTurn == PlayerTurn::PLAYER1) ? this->player1Board : this->player2Board;
}

Board & BiQuadris::getPlayerBoard(PlayerTurn whichPlayerTurn) {
    return (whichPlayerTurn == PlayerTurn::PLAYER1) ? this->player1Board : this->player2Board;
}

Board & BiQuadris::getCurrentPlayerBoard() {
    return this->getPlayerBoard(this->currentPlayerTurn);
}

Board & BiQuadris::getCurrentPlayerOpponentBoard() {
    return this->getPlayerBoard(getOpponentTurn(this->currentPlayerTurn));
}

void BiQuadris::assertNotGameOver() const {
    if (this->isGameOver) {
        throw std::runtime_error("Command invalid; game is over!");
    }
}

void BiQuadris::assertBonusFeaturesOn() const {
    if (!this->bonusFeatures) {
        throw std::runtime_error("Command invalid; bonus features are DISABLED. To turn on bonus features, use 'bonuson' command!");
    }
}

void BiQuadris::assertDevModeOn() const {
    if (!this->devMode) {
        throw std::runtime_error("Command invalid; dev mode is off, thus only gameplay commands are enabled!");
    }
}

void BiQuadris::assertBoardActionMove() const {
    this->assertNotGameOver();
    if (this->canUseSpecialAction) {
        throw std::runtime_error("Command invalid; pick a special action (or use 'spare' command to not cast a special action)!");
    }
}

void BiQuadris::assertSpecialActionMove() const {
    this->assertNotGameOver();
    if (!this->canUseSpecialAction) {
        throw std::runtime_error("Command invalid; cannot use special action at this time!");
    }
}

void BiQuadris::updateGameStateAfterBlockAction() {
    if (this->currentBoardPlacedBlockThisMove) {
        this->currentBoardPlacedBlockThisMove = false;
        this->getCurrentPlayerBoard().setBlindEffect(false);

        if (this->currentBoardNumRowsClearedThisMove >= MIN_REQUIRED_ROWS_CLEARED_TO_TRIGGER_SPECIAL_ACTION) {
            canUseSpecialAction = true;
        } else {
            this->currentPlayerTurn = getOpponentTurn(this->currentPlayerTurn);
        }
    }
}

void BiQuadris::moveBlockLeft(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().moveBlockLeft(multiplier);

    this->updateGameStateAfterBlockAction();
}

void BiQuadris::moveBlockRight(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().moveBlockRight(multiplier);

    this->updateGameStateAfterBlockAction();
}

void BiQuadris::moveBlockDown(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().moveBlockDown(multiplier);

    this->updateGameStateAfterBlockAction();
}

void BiQuadris::rotateBlockClockwise(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().rotateBlockClockwise(multiplier);

    this->updateGameStateAfterBlockAction();
}

void BiQuadris::rotateBlockCounterClockwise(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().rotateBlockCounterClockwise(multiplier);

    this->updateGameStateAfterBlockAction();
}

void BiQuadris::dropBlock(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().dropBlock(multiplier);

    this->updateGameStateAfterBlockAction();
}

void BiQuadris::holdBlock() {
    this->assertBonusFeaturesOn();
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().holdBlock();
    this->updateGameStateAfterBlockAction();
}

void BiQuadris::restartBoards() {
    this->currentPlayerTurn = PlayerTurn::PLAYER1;
    this->isGameOver = false;
    this->canUseSpecialAction = false;
    this->currentBoardPlacedBlockThisMove = false;

    this->player1Board.restart();
    this->player2Board.restart();
}

void BiQuadris::levelUp(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().levelUp(multiplier);
}

void BiQuadris::levelDown(int multiplier) {
    this->assertBoardActionMove();

    this->getCurrentPlayerBoard().levelDown(multiplier);
}

void BiQuadris::replaceCurrentBlock(char blockType) {
    this->assertBoardActionMove();
    this->assertDevModeOn();

    this->getCurrentPlayerBoard().replaceCurrentBlock(blockType);
}

void BiQuadris::blindEffect() {
    this->assertSpecialActionMove();

    this->getCurrentPlayerOpponentBoard().setBlindEffect(true);

    this->endSpecialActionMove();
}

void BiQuadris::heavyEffect() {
    this->assertSpecialActionMove();

    this->getCurrentPlayerOpponentBoard().setHeavyEffect();

    this->endSpecialActionMove();
}

void BiQuadris::forceEffect(char blockType) {
    this->assertSpecialActionMove();

    this->getCurrentPlayerOpponentBoard().replaceCurrentBlock(blockType);

    this->endSpecialActionMove();
}

void BiQuadris::enableRandom() {
    this->assertBoardActionMove();
    this->assertDevModeOn();

    this->getCurrentPlayerBoard().setLevelRandomEnabled(true);
}

void BiQuadris::disableRandom() {
    this->assertBoardActionMove();
    this->assertDevModeOn();

    this->getCurrentPlayerBoard().setLevelRandomEnabled(false);
}

void BiQuadris::disableRandom(std::string & blockSequenceFile) {
    this->disableRandom();
    this->getCurrentPlayerBoard().setBlockSequenceFile(blockSequenceFile);
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

std::vector<BlockAttributes> BiQuadris::getBlockAttributesBacklog(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getBlockAttributesBacklog();
}

int BiQuadris::getCurrentScore(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getCurrentScore();
}

int BiQuadris::getHighScore(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getHighScore();
}

int BiQuadris::getLevelNum(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getLevelNum();
}

bool BiQuadris::getBlindEffectEnabled(PlayerTurn whichPlayerTurn) const {
    return this->getPlayerBoard(whichPlayerTurn).getBlindEffectEnabled();
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

// mutators
void BiQuadris::setBonusFeatures(bool isOn) {
    this->bonusFeatures = isOn;
}

void BiQuadris::setDevMode(bool isOn) {
    this->assertBonusFeaturesOn();

    this->devMode = isOn;
}

void BiQuadris::informCurrentBoardPlacedBlock(int rowsCleared) {
    this->currentBoardPlacedBlockThisMove = true;
    this->currentBoardNumRowsClearedThisMove = rowsCleared;
}

void BiQuadris::informGameOver() {
    this->isGameOver = true;
}

void BiQuadris::endSpecialActionMove() {
    this->assertSpecialActionMove();

    this->canUseSpecialAction = false;
    this->currentPlayerTurn = getOpponentTurn(this->currentPlayerTurn);
}
