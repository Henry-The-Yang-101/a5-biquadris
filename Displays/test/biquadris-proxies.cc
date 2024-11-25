#include "biquadris-proxies.h";

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using Grid = vector<vector<char>>;

// DisplayProxy definitions
DisplayProxy::DisplayProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

Grid DisplayProxy::getGrid(int whichBoard) const {
  Grid temp;
  return temp;
}

BlockAttributes DisplayProxy::getCurrentBlockAttributes(int whichBoard) const {
  BlockAttributes temp;
  return temp;
}

BlockAttributes DisplayProxy::getNextBlockAttributes(int whichBoard) const {
  BlockAttributes temp;
  return temp;
}

BlockAttributes DisplayProxy::getHeldBlockAttributes(int whichBoard) const {
  BlockAttributes temp;
  return temp;
}

vector<BlockAttributes> DisplayProxy::getBlockBacklog(int whichBoard) const {
  vector<BlockAttributes> temp;
  return temp;
}

int DisplayProxy::getCurrentScore(int whichBoard) const {
  return 15;
}

int DisplayProxy::getHighScore(int whichBoard) const {
  return 20;
}

int DisplayProxy::getLevel(int whichBoard) const {
  return 2;
}

bool DisplayProxy::getIsGameOver() const {
  return false;
}

int DisplayProxy::getCurrentBoardTurn() const {
  return 1;
}

bool DisplayProxy::getCanUseSpecialAction() const {
  return false;
}
