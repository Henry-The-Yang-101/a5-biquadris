#include <stdexcept>
#include "board.h"
#include "./Level/level.h"
#include "./Level/all-levels.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using BlockAttributes = std::pair<BlockCellCoordinates, char>;

Board::Board(ManageGameStateProxy & gameProxy, int initLevelNum, std::string blockSequenceFileName) : 
    initLevelNum{initLevelNum}, boardProxy{*this}, gameProxy{gameProxy}, blockSequenceFileName{blockSequenceFileName} {

    this->setUpEmptyGrid();
    this->setCurrentLevel(initLevelNum);
    this->currentBlock = std::move(this->currentLevel->cycleBlock());
    this->nextBlock = std::move(this->currentLevel->cycleBlock());
}

void Board::setUpEmptyGrid() {
    this->grid = std::vector<std::vector<std::shared_ptr<BlockCell>>>{HEIGHT + NUM_RESERVE_ROWS, std::vector<std::shared_ptr<BlockCell>>{WIDTH, nullptr}};
}

void Board::setCurrentLevel(int levelNum) {
    if (levelNum == 0) {
        this->currentLevel = std::make_unique<LevelZero>(this->boardProxy, this->blockSequenceFileName);
    } else if (levelNum == 1) {
        this->currentLevel = std::make_unique<LevelOne>(this->boardProxy, this->blockSequenceFileName);
    } else if (levelNum == 2) {
        this->currentLevel = std::make_unique<LevelTwo>(this->boardProxy, this->blockSequenceFileName);
    } else if (levelNum == 3) {
        this->currentLevel = std::make_unique<LevelThree>(this->boardProxy, this->blockSequenceFileName);
    } else if (levelNum == 4) {
        this->currentLevel = std::make_unique<LevelFour>(this->boardProxy, this->blockSequenceFileName);
    } else {
        throw std::runtime_error("Invalid Level");
    }
}

const int MAX_POSSIBLE_CLEARED_ROWS = 4;

int Board::countAndClearFilledRows() {
    int clearedRows = 0;
    int currentRowIndex = 0;
    int firstClearedRowIndex;

    for (auto row = this->grid.begin(); row != this->grid.end();) {
        bool isFilled = true;
        for (size_t i = 0; i < this->grid.size(); ++i) {
            if ((*row)[i] == nullptr) {
                isFilled = false;
                break;
            }
        }
        if (isFilled) {
            row = this->grid.erase(row);
            ++clearedRows;

            if (clearedRows == 1) {
                firstClearedRowIndex = currentRowIndex;
            } else if (firstClearedRowIndex + MAX_POSSIBLE_CLEARED_ROWS - 1 == currentRowIndex) {
                break;
            }
        } else {
            ++row;
        }
        ++currentRowIndex;
    }
    for (int i = 0; i < clearedRows; ++i) {
        this->grid.emplace_back(WIDTH, nullptr);
    }
    return clearedRows;
}

int Board::calculateScoreIncrease(int linesCleared) {
    return (this->currentLevel->getLevelNum() + linesCleared) * (this->currentLevel->getLevelNum() + linesCleared);
}

bool Board::cellAvailable(int column, int row) {
    row += this->NUM_RESERVE_ROWS;
    return this->grid[row][column] == nullptr;
}

void Board::applyLevelHeaviness() {
    if (this->currentLevel->getHeavy()) {
        this->currentBlock->down();
    }
}

void Board::applyHeavyEffect() {
    if (this->currentBlockHeavyEffect) {
        if (!this->currentBlock->down() || !this->currentBlock->down()) {
            this->dropBlock(1);
        }
    }
}

void Board::insertBlockCell(int column, int row, std::shared_ptr<BlockCell> cell) {
    this->grid[row][column] = cell;
}

void Board::moveBlockLeft(int multiplier) {
    while (multiplier > 0 && this->currentBlock->moveLeft()) {
        multiplier--;
    }
    this->applyLevelHeaviness();
    this->applyHeavyEffect();
}

void Board::moveBlockRight(int multiplier) {
    while (multiplier > 0 && this->currentBlock->moveRight()) {
        multiplier--;
    }
    this->applyLevelHeaviness();
    this->applyHeavyEffect();
}

void Board::moveBlockDown(int multiplier) {
    while (multiplier > 0 && this->currentBlock->down()) {
        multiplier--;
    }
    this->applyLevelHeaviness();
}

void Board::rotateBlockClockwise(int multiplier) {
    while (multiplier > 0 && this->currentBlock->rotateClockwise()) {
        multiplier--;
    }
    this->applyLevelHeaviness();
}

void Board::rotateBlockCounterClockwise(int multiplier) {
    while (multiplier > 0 && this->currentBlock->rotateCounterClockwise()) {
        multiplier--;
    }
    this->applyLevelHeaviness();
}

void Board::dropBlock(int multiplier) {
    int totalClearedRows = 0;
    while (multiplier > 0) {
        this->currentBlock->drop();
        int currentClearedRows = this->countAndClearFilledRows();
        totalClearedRows += currentClearedRows;

        if (currentClearedRows > 0) {
            this->numBlocksPlacedWithoutClearing = 0;
        } else {
            this->numBlocksPlacedWithoutClearing++;
        }

        // replace current and next block
        this->currentBlock = std::move(this->nextBlock);
        this->nextBlock = std::move(this->currentLevel->cycleBlock());
        
        if (!this->currentBlock->isValidPosition()) {
            this->gameProxy.informGameOver();
            break;
        }
        multiplier--;
    }
    if (this->currentLevel->checkCustomRuleCondition()) {
        if (this->currentLevel->executeCustomRuleAction()) {
            this->gameProxy.informGameOver();
        }
        totalClearedRows += this->countAndClearFilledRows();
    }
    this->allowedToHold = true;
    this->currentBlockHeavyEffect = false;
    this->currentScore += this->calculateScoreIncrease(totalClearedRows);
    this->gameProxy.informCurrentBoardPlacedBlock(totalClearedRows);
}

void Board::holdBlock() {
    if (this->allowedToHold) {

        std::swap(this->currentBlock, this->blockOnHold);

        // replace current block with nextblock if initially no block on hold
        if (this->currentBlock == nullptr) {
            this->currentBlock = std::move(this->nextBlock);
            this->nextBlock = std::move(this->currentLevel->cycleBlock());
        } 
        this->allowedToHold = false;
    } else {
        throw std::runtime_error("Can't take back the piece!");
    }
}

void Board::restart() {
    if (this->currentScore > this->highScore) {
        this->highScore = this->currentScore;
    }
    this->numBlocksPlacedWithoutClearing = 0;
    this->currentBlockHeavyEffect = false;
    this->allowedToHold = true;
    this->setUpEmptyGrid();
    this->setCurrentLevel(this->initLevelNum);
    this->currentBlock = this->currentLevel->cycleBlock();
    this->nextBlock = this->currentLevel->cycleBlock();
    this->blockOnHold = nullptr;
    this->currentScore = 0;
}

void Board::levelUp(int multiplier) {
    this->setCurrentLevel(this->currentLevel->getLevelNum() + multiplier);
}

void Board::levelDown(int multiplier) {
    this->setCurrentLevel(this->currentLevel->getLevelNum() - multiplier);
}

void Board::increaseScore(int points) {
    this->currentScore += points;
}

void Board::setHeavyEffect() {
    this->currentBlockHeavyEffect = true;
}

int Board::getHeight() {
    return this->HEIGHT + this->NUM_RESERVE_ROWS;
}

int Board::getWidth() {
    return this->WIDTH;
}

int Board::getNumBlocksPlacedWithoutClearing() {
    return this->numBlocksPlacedWithoutClearing;
}

BlockCellCoordinates Board::getCurrentBlockDropPreviewCellCoordinates() {
    return this->currentBlock->getDropPreviewCellCoordinates();
}

BlockAttributes Board::getCurrentBlockAttributes() {

    return std::pair{this->currentBlock->getCellCoordinates(), this->currentBlock};
}

BlockAttributes getNextBlockAttributes();
BlockAttributes getNextBlockAttributes();


