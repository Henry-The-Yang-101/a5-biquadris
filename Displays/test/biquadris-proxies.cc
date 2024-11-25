#include "biquadris-proxies.h";

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using Grid = vector<vector<char>>;

// DisplayProxy definitions
DisplayProxy::DisplayProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

Grid DisplayProxy::getGrid(int whichBoard) const {
  Grid grid(18, vector<char>(11, ' ')); // 18 rows and 11 columns, filled with spaces

  vector<string> gameState = {
        "           ", // Row 0
        "           ", // Row 1
        "           ", // Row 2
        "           ", // Row 3
        "           ", // Row 4
        "           ", // Row 5
        "           ", // Row 6
        "           ", // Row 7
        "           ", // Row 8
        "           ", // Row 9
        "           ", // Row 10
        "           ", // Row 11
        "           ", // Row 12
        "           ", // Row 13
        "     I  I  ", // Row 14
        "LLL  I  I  ", // Row 15
        "LTSS IOOIOO", // Row 16
        "TTTSSIOOIOO", // Row 17
    };

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (j < gameState[i].size()) {
                grid[i][j] = gameState[i][j];
            } else {
                grid[i][j] = ' ';
            }
        }
    }
  return grid;
}

BlockAttributes DisplayProxy::getCurrentBlockAttributes(int whichBoard) const {
  if (whichBoard == 1) {
    // Mock current block data - a TBlock rotated UP
    BlockCellCoordinates currentBlockCoordinates = {{0, -1}, {1, -1}, {2, -1}, {1, 0}};
    char currentBlockType = 'T'; // Corresponding type for TBlock
    return {currentBlockCoordinates, currentBlockType};
  } else {
    BlockCellCoordinates nextBlockCoordinates = {{2, -1}, {0, 0}, {1, 0}, {2, 0}};
    char nextBlockType = 'L'; // Corresponding type for LBlock
    return {nextBlockCoordinates, nextBlockType};
  }
}
BlockAttributes DisplayProxy::getNextBlockAttributes(int whichBoard) const {
    // Mock next block data - a LBlock rotated UP
    if (whichBoard == 1) {
      BlockCellCoordinates nextBlockCoordinates = {{2, -1}, {0, 0}, {1, 0}, {2, 0}};
      char nextBlockType = 'L'; // Corresponding type for LBlock
      return {nextBlockCoordinates, nextBlockType};
    } else {
      // Mock current block data - a TBlock rotated UP
      BlockCellCoordinates currentBlockCoordinates = {{0, -1}, {1, -1}, {2, -1}, {1, 0}};
      char currentBlockType = 'T'; // Corresponding type for TBlock
      return {currentBlockCoordinates, currentBlockType};
    }
}

BlockAttributes DisplayProxy::getHeldBlockAttributes(int whichBoard) const {
  if (whichBoard == 1) {
    // Mock held block data - an OBlock (no rotation affects its shape)
    BlockCellCoordinates heldBlockCoordinates = {{0, -1}, {1, -1}, {0, 0}, {1, 0}};
    char heldBlockType = 'O'; // Corresponding type for OBlock
    return {heldBlockCoordinates, heldBlockType};
  }
    // Mock current block data - a TBlock rotated UP
    BlockCellCoordinates currentBlockCoordinates = {{0, -1}, {1, -1}, {2, -1}, {1, 0}};
    char currentBlockType = 'T'; // Corresponding type for TBlock
    return {currentBlockCoordinates, currentBlockType};
}

vector<BlockAttributes> DisplayProxy::getBlockAttributesBacklog(int whichBoard) const {
    // Mock backlog data with 5 blocks of different types and rotations
    if (whichBoard == 1) {
    vector<BlockAttributes> backlog;

    // LBlock rotated UP
    backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});

    // JBlock rotated UP
    backlog.push_back({{{0, -1}, {0, 0}, {1, 0}, {2, 0}}, 'J'});

    // SBlock rotated UP
    backlog.push_back({{{1, -1}, {2, -1}, {0, 0}, {1, 0}}, 'S'});
    
    // ZBlock rotated UP
    backlog.push_back({{{0, -1}, {1, -1}, {1, 0}, {2, 0}}, 'Z'});

    // LBlock rotated UP
    backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});

    return backlog;
    }
    vector<BlockAttributes> backlog;
    
    // ZBlock rotated UP
    backlog.push_back({{{0, -1}, {1, -1}, {1, 0}, {2, 0}}, 'Z'});

    // SBlock rotated UP
    backlog.push_back({{{1, -1}, {2, -1}, {0, 0}, {1, 0}}, 'S'});

    // JBlock rotated UP
    backlog.push_back({{{0, -1}, {0, 0}, {1, 0}, {2, 0}}, 'J'});

    // LBlock rotated UP
    backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});

    // LBlock rotated UP
    backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});

    return backlog;
}


int DisplayProxy::getCurrentScore(int whichBoard) const {
  if (whichBoard == 1) {
    return 5;
  }
  return 15;
}

int DisplayProxy::getHighScore(int whichBoard) const {
  if (whichBoard == 1) {
    return 7;
  }
  return 20;
}

int DisplayProxy::getLevel(int whichBoard) const {
  if (whichBoard == 1) {
    return 4;
  }
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
