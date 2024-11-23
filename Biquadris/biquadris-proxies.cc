#include "biquadris-proxies.h"

using CellCoords = pair<int, int>;
using BlockAttributes = pair<vector<CellCoords>, char>;
using Grid = vector<vector<char>>;

// ManageGameStateProxy definitions
ManageGameStateProxy::ManageGameStateProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void ManageGameStateProxy::setBonusFeatures(bool isOn) {
  this->gameEngine.setBonusFeatures(isOn);
}

void ManageGameStateProxy::setDevMode(bool isOn) {
  this->gameEngine.setDevMode(isOn);
}

void ManageGameStateProxy::gameOver() {
  this->gameEngine.gameOver();
}

// VisualEffectProxy definitions
VisualEffectProxy::VisualEffectProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void VisualEffectProxy::blindEffect() {
  this->gameEngine.blindEffect();
}

// BoardActionProxy definitions
BoardActionProxy::BoardActionProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void BoardActionProxy::moveBlockHorizontal(int multiplier) {
  this->gameEngine.moveBlockHorizontal(multiplier);
}

void BoardActionProxy::moveBlockDown(int multiplier) {
  this->gameEngine.moveBlockDown(multiplier);
}

void BoardActionProxy::rotateBlockClockwise(int multiplier) {
  this->gameEngine.rotateBlockClockwise(multiplier);
}

void BoardActionProxy::rotateBlockCounterClockwise(int multiplier) {
  this->gameEngine.rotateBlockCounterClockwise(multiplier);
}

void BoardActionProxy::dropBlock(int multiplier) {
  this->gameEngine.dropBlock(multiplier);
}

void BoardActionProxy::holdBlock() {
  this->gameEngine.holdBlock();
}

void BoardActionProxy::restartBoard() {
  this->gameEngine.restartBoard();
}

void BoardActionProxy::heavyEffect() {
  this->gameEngine.heavyEffect();
}

// LevelBlockGenProxy definitions
LevelBlockGenProxy::LevelBlockGenProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void LevelBlockGenProxy::levelUp(int multiplier) {
  this->gameEngine.levelUp(multiplier);
}

void LevelBlockGenProxy::levelDown(int multiplier) {
  this->gameEngine.levelDown(multiplier);
}

void LevelBlockGenProxy::enableRandom() {
  this->gameEngine.enableRandom();
}

void LevelBlockGenProxy::disableRandom(std::string blockSequenceFile) {
  this->gameEngine.disableRandom(blockSequenceFile);
}

void LevelBlockGenProxy::replaceCurrentBlock(char blockType) {
  this->gameEngine.replaceCurrentBlock(blockType);
}

void LevelBlockGenProxy::forceEffect(char blockType) {
  this->gameEngine.forceEffect(blockType);
}

// DisplayProxy definitions
DisplayProxy::DisplayProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

Grid DisplayProxy::getGrid(int whichBoard) const {
  this->gameEngine.getGrid(whichBoard);
}

BlockAttributes DisplayProxy::getCurrentBlockAttributes(int whichBoard) const {
  this->gameEngine.getCurrentBlockAttributes(whichBoard);
}

BlockAttributes DisplayProxy::getNextBlockAttributes(int whichBoard) const {
  this->gameEngine.getNextBlockAttributes(whichBoard);
}

BlockAttributes DisplayProxy::getHeldBlockAttributes(int whichBoard) const {
  this->gameEngine.getHeldBlockAttributes(whichBoard);
}

vector<BlockAttributes> DisplayProxy::getBlockBacklog(int whichBoard) const {
  this->gameEngine.getBlockBacklog(whichBoard);
}

int DisplayProxy::getCurrentScore(int whichBoard) const {
  this->gameEngine.getCurrentScore(whichBoard);
}

int DisplayProxy::getHighScore(int whichBoard) const {
  this->gameEngine.getHighScore(whichBoard);
}

bool DisplayProxy::getIsGameOver() const {
  this->gameEngine.getIsGameOver();
}

int DisplayProxy::getCurrentBoardTurn() const {
  this->gameEngine.getCurrentBoardTurn();
}

bool DisplayProxy::getCanUseSpecialAction() const {
  this->gameEngine.getCanUseSpecialAction();
}
