#include "biquadris-proxies.h"

using CellCoordinate = pair<int, int>;
using BlockAttributes = pair<vector<CellCoordinate>, char>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using Grid = vector<vector<char>>;

// DisplayProxy definitions
DisplayProxy::DisplayProxy(BiQuadris & gameEngine) : BiQuadrisProxy{gameEngine} {}

Grid DisplayProxy::getCharGrid(BiQuadris::PlayerTurn whichPlayerTurn) const {
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

BlockAttributes DisplayProxy::getCurrentBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const {
    if (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) {
        BlockCellCoordinates currentBlockCoordinates = {{0, -1}, {1, -1}, {2, -1}, {1, 0}};
        char currentBlockType = 'T'; // Corresponding type for TBlock
        return {currentBlockCoordinates, currentBlockType};
    } else {
        BlockCellCoordinates nextBlockCoordinates = {{2, -1}, {0, 0}, {1, 0}, {2, 0}};
        char nextBlockType = 'L'; // Corresponding type for LBlock
        return {nextBlockCoordinates, nextBlockType};
    }
}

BlockCellCoordinates DisplayProxy::getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn whichPlayerTurn) const {
    if (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) {
        BlockCellCoordinates currentBlockCoordinates = {{0, 10}, {1, 10}, {2, 10}, {1, 11}};
        char currentBlockType = 'T'; // Corresponding type for TBlock
        return currentBlockCoordinates;
    } else {
        BlockCellCoordinates nextBlockCoordinates = {{2, 10}, {0, 11}, {1, 11}, {2, 11}};
        char nextBlockType = 'L'; // Corresponding type for LBlock
        return nextBlockCoordinates;
    }
}

BlockAttributes DisplayProxy::getNextBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const {
    if (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) {
        BlockCellCoordinates nextBlockCoordinates = {{2, -1}, {0, 0}, {1, 0}, {2, 0}};
        char nextBlockType = 'L'; // Corresponding type for LBlock
        return {nextBlockCoordinates, nextBlockType};
    } else {
        BlockCellCoordinates currentBlockCoordinates = {{0, -1}, {1, -1}, {2, -1}, {1, 0}};
        char currentBlockType = 'T'; // Corresponding type for TBlock
        return {currentBlockCoordinates, currentBlockType};
    }
}

BlockAttributes DisplayProxy::getHeldBlockAttributes(BiQuadris::PlayerTurn whichPlayerTurn) const {
    if (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) {
        BlockCellCoordinates heldBlockCoordinates = {{0, -1}, {1, -1}, {0, 0}, {1, 0}};
        char heldBlockType = 'O'; // Corresponding type for OBlock
        return {heldBlockCoordinates, heldBlockType};
    }
    BlockCellCoordinates currentBlockCoordinates = {{0, -1}, {1, -1}, {2, -1}, {1, 0}};
    char currentBlockType = 'T'; // Corresponding type for TBlock
    return {currentBlockCoordinates, currentBlockType};
}

vector<BlockAttributes> DisplayProxy::getBlockAttributesBacklog(BiQuadris::PlayerTurn whichPlayerTurn) const {
    vector<BlockAttributes> backlog;
    if (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) {
        backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});
        backlog.push_back({{{0, -1}, {0, 0}, {1, 0}, {2, 0}}, 'J'});
        backlog.push_back({{{1, -1}, {2, -1}, {0, 0}, {1, 0}}, 'S'});
        backlog.push_back({{{0, -1}, {1, -1}, {1, 0}, {2, 0}}, 'Z'});
        backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});
    } else {
        backlog.push_back({{{0, -1}, {1, -1}, {1, 0}, {2, 0}}, 'Z'});
        backlog.push_back({{{1, -1}, {2, -1}, {0, 0}, {1, 0}}, 'S'});
        backlog.push_back({{{0, -1}, {0, 0}, {1, 0}, {2, 0}}, 'J'});
        backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});
        backlog.push_back({{{2, -1}, {0, 0}, {1, 0}, {2, 0}}, 'L'});
    }
    return backlog;
}

int DisplayProxy::getCurrentScore(BiQuadris::PlayerTurn whichPlayerTurn) const {
    return (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) ? 5 : 15;
}

int DisplayProxy::getHighScore(BiQuadris::PlayerTurn whichPlayerTurn) const {
    return (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) ? 7 : 20;
}

int DisplayProxy::getLevelNum(BiQuadris::PlayerTurn whichPlayerTurn) const {
    return (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) ? 4 : 2;
}

bool DisplayProxy::getIsGameOver() const {
    return false;
}

BiQuadris::PlayerTurn DisplayProxy::getCurrentPlayerTurn() const {
    return BiQuadris::PlayerTurn::PLAYER1; // Mock current player turn
}

bool DisplayProxy::getCanUseSpecialAction() const {
    return false;
}

bool DisplayProxy::getBonusFeaturesEnabled() const {
  return true;
}
bool DisplayProxy::getBlindEffectEnabled(BiQuadris::PlayerTurn whichPlayerTurn) const {
    if (whichPlayerTurn == BiQuadris::PlayerTurn::PLAYER1) {
        return true;
    }
    return false;
}