#include "board.h"
#include "./Level/level.h"

Board::Board(ManageGameStateProxy game, std::unique_ptr<Level> level, const std::string blockSequenceFileName) : 
    boardProxy{*this}, game{game}, currentLevel{std::move(level)}, currentScore{0}, highScore{0}, 
    numBlocksPlacedWithoutClearing{0}, allowedToHold{false}, currentBlockHeavyEffect{false}, grid{}, blockSequenceFileName{blockSequenceFileName} {}

Board::~Board() {}

bool Board::cellAvailable(int x, int y) {

    y += this->NUM_RESERVE_ROWS;
    // check within board boundaries and coordinate is nullptr (no block in cell)
    return (x >= 0 && x < this->WIDTH && y >= 0 && y < this->HEIGHT) && (this->grid[y][x] == nullptr);
}

void Board::insertBlockCell(int x, int y, std::shared_ptr<BlockCell> cell) {
    this->grid[y][x] = cell;
}

void Board::moveBlockHorizontal(int multiplier) {

    // move right if mulitiplier is positive
    while (multiplier > 0 && this->currentBlock->moveRight()) {
        multiplier--;
    }

    // move left if multiplier is negative
    while (multiplier < 0 && this->currentBlock->moveLeft()) {
        multiplier++;
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
