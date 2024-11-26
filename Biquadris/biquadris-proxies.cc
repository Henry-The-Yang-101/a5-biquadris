#include "biquadris-proxies.h"

using CellCoordinate = std::pair<int, int>;
using BlockAttributes = std::pair<std::vector<CellCoordinate>, char>;
using CharGrid = std::vector<std::vector<char>>;

// InformGameStateProxy definitions

InformGameStateProxy::InformGameStateProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void InformGameStateProxy::informCurrentBoardPlacedBlock(int rowsCleared) {
  this->gameEngine.informCurrentBoardPlacedBlock(rowsCleared);
}

void InformGameStateProxy::informGameOver() {
  this->gameEngine.informGameOver();
}

// ManageGameStateProxy definitions
ManageGameStateProxy::ManageGameStateProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void ManageGameStateProxy::setBonusFeatures(bool isOn) {
  this->gameEngine.setBonusFeatures(isOn);
}

void ManageGameStateProxy::setDevMode(bool isOn) {
  this->gameEngine.setDevMode(isOn);
}

void ManageGameStateProxy::endSpecialActionMove() {
  this->gameEngine.endSpecialActionMove();
}

// VisualEffectProxy definitions
VisualEffectProxy::VisualEffectProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void VisualEffectProxy::blindEffect() {
  this->gameEngine.blindEffect();
}

// BoardActionProxy definitions
BoardActionProxy::BoardActionProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

void BoardActionProxy::moveBlockLeft(int multiplier) {
  this->gameEngine.moveBlockLeft(multiplier);
}

void BoardActionProxy::moveBlockRight(int multiplier) {
  this->gameEngine.moveBlockRight(multiplier);
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

void BoardActionProxy::restartBoards() {
  this->gameEngine.restartBoards();
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

void LevelBlockGenProxy::disableRandom() {
  this->gameEngine.disableRandom();
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

int DisplayProxy::getGridWidth() const {
  return this->gameEngine.getGridWidth();
}

int DisplayProxy::getGridHeight() const {
  return this->gameEngine.getGridHeight();
}

int DisplayProxy::getGridNumReserveRows() const {
  return this->gameEngine.getGridNumReserveRows();
}

int DisplayProxy::getCurrentScore(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getCurrentScore(whichPlayerTurn);
}

int DisplayProxy::getHighScore(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getHighScore(whichPlayerTurn);
}

int DisplayProxy::getLevelNum(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getLevelNum(whichPlayerTurn);
}

bool DisplayProxy::getBlindEffectEnabled(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getBlindEffectEnabled(whichPlayerTurn);
}

bool DisplayProxy::getIsGameOver() const {
  return this->gameEngine.getIsGameOver();
}

bool DisplayProxy::getCanUseSpecialAction() const {
  return this->gameEngine.getCanUseSpecialAction();
}

bool DisplayProxy::getBonusFeaturesEnabled() const {
  return this->gameEngine.getBonusFeaturesEnabled();
}

BiQuadris::PlayerTurn DisplayProxy::getCurrentPlayerTurn() const {
  return this->gameEngine.getCurrentPlayerTurn();
}

CharGrid DisplayProxy::getCharGrid(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getCharGrid(whichPlayerTurn);
}

BlockCellCoordinates DisplayProxy::getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getCurrentBlockDropPreviewCellCoordinates(whichPlayerTurn);
}

BlockAttributes DisplayProxy::getCurrentBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getCurrentBlockAttributes(whichPlayerTurn);
}

BlockAttributes DisplayProxy::getNextBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getNextBlockAttributes(whichPlayerTurn);
}

BlockAttributes DisplayProxy::getHeldBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getHeldBlockAttributes(whichPlayerTurn);
}

std::vector<BlockAttributes> DisplayProxy::getBlockAttributesBacklog(BiQuadris::PlayerTurn whichPlayerTurn) const {
  return this->gameEngine.getBlockAttributesBacklog(whichPlayerTurn);
}
