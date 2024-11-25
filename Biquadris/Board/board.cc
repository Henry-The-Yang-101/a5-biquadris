#include "board.h"
#include "./Level/level.h"

Board::Board(ManageGameStateProxy gameProxy, std::unique_ptr<Level> level, std::string blockSequenceFileName, bool allowedToHold) : 
    boardProxy{*this}, gameProxy{gameProxy}, currentLevel{std::move(level)}, allowedToHold{allowedToHold}, blockSequenceFileName{blockSequenceFileName}, 
    grid{HEIGHT + NUM_RESERVE_ROWS, std::vector<std::shared_ptr<BlockCell>>{WIDTH, nullptr}} {
}

void Board::refillRows() {
    while (this->grid.size() < HEIGHT + NUM_RESERVE_ROWS) {
        this->grid.emplace_back(WIDTH, nullptr);
    }
}

bool Board::cellAvailable(int column, int row) {
    row += this->NUM_RESERVE_ROWS;
    // check within board boundaries and coordinate is nullptr (no block in cell)
    if (!(column >= 0 && column < this->WIDTH && row >= 0 && row < this->HEIGHT)) return false; // redundant?
    return this->grid[row][column] == nullptr;
}

void Board::insertBlockCell(int column, int row, std::shared_ptr<BlockCell> cell) {
    this->grid[row][column] = cell;
}

void Board::moveBlockLeft(int multiplier) {
    while (multiplier > 0 && this->currentBlock->moveLeft()) {
        multiplier--;
    }
}

void Board::moveBlockRight(int multiplier) {
    while (multiplier > 0 && this->currentBlock->moveRight()) {
        multiplier--;
    }
}


void Board::moveBlockDown(int multiplier) {
    while (multiplier > 0 && this->currentBlock->down()) {
        multiplier--;
    }
}

void Board::rotateBlockClockwise(int multiplier) {
    while (multiplier > 0 && this->currentBlock->rotateClockwise()) {
        multiplier--;
    }
}

void Board::rotateBlockCounterClockwise(int multiplier) {
    while(multiplier > 0 && this->currentBlock->rotateCounterClockwise()) {
        multiplier--;
    }
}

void Board::dropBlock(int multiplier) {
    while (multiplier > 0) {
        this->currentBlock->drop();

        // replace current and next block
        this->currentBlock = std::move(this->nextBlock);
        this->nextBlock = std::move(this->currentLevel->cycleBlock());
    }
}

void Board::holdBlock() {

    if (this->allowedToHold) {

        std::swap(this->currentBlock, this->blockOnHold);

        // replace current block with nextblock if initially no block on hold
        if (this->currentBlock == nullptr) {
            this->currentBlock = std::move(this->nextBlock);
            this->nextBlock = std::move(this->currentLevel->cycleBlock());
        } 

    }

}
std::vector<CellCoordinate> Board::getBlockDropPreview() {
    return this->currentBlock->getCellCoordinates();
}

void Board::restart() {

    this->currentScore = 0;
    this->numBlocksPlacedWithoutClearing = 0;

    // this->currentBlockHeavyEffect = false;
    // this->allowedToHold = false;

    this->grid.clear();
    this->grid.resize(this->HEIGHT, std::vector<std::shared_ptr<BlockCell>>{this->WIDTH, nullptr});

}
void Board::levelUp(int multiplier) {
    int newLevel = this->currentLevel->getLevelNum() + multiplier;
    this->currentLevel = std::make_unique<Level>(newLevel, this->currentBlockHeavyEffect, this->boardProxy, this->blockSequenceFileName);
}
void Board::levelDown(int multiplier) {
    int newLevel = this->currentLevel->getLevelNum() - multiplier;
    this->currentLevel = std::make_unique<Level>(newLevel, this->currentBlockHeavyEffect, this->boardProxy, this->blockSequenceFileName);
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
