#include "board.h"
#include "./Level/level.h"

Board::Board(ManageGameStateProxy game, std::unique_ptr<Level> level, int width, int height, const std::string blockSequenceFileName) : 
    boardProxy{*this}, game{game}, currentLevel{std::move(level)}, width{width}, height{height}, currentScore{0}, highScore{0}, 
    numBlocksPlacedWithoutClearing{0}, allowedToHold{false}, currentBlockHeavyEffect{false}, grid{}, blockSequenceFileName{blockSequenceFileName} {}

Board::~Board() {}

bool Board::cellAvailable(int x, int y) {
    return (x < 0 || x >= width || y < 0 || y >= height) && (grid[y][x] == nullptr);
}

void Board::insertBlockCell(int x, int y, std::shared_ptr<BlockCell> cell) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x] = cell;
    }
}

void Board::moveBlockHorizontal(int multiplier) {

    while (multiplier > 0 && this->currentBlock->moveRight()) {
        multiplier--;
    }
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
        this->currentBlock = std::move(this->nextBlock);
        this->nextBlock = std::move(this->currentLevel->cycleBlock());
    }
}

void Board::holdBlock() {

    if (this->allowedToHold) {

        std::swap(this->currentBlock, this->blockOnHold);

        if (this->currentBlock == nullptr) {
            this->currentBlock = std::move(this->nextBlock);
            this->nextBlock = std::move(this->currentLevel->cycleBlock());
        } 

    }

}
std::vector<std::pair<int, int>> Board::getBlockDropPreview() {
    return this->currentBlock->getCellCoordinates();
}

void Board::restart() {

    this->currentScore = 0;
    this->numBlocksPlacedWithoutClearing = 0;

    // this->currentBlockHeavyEffect = false;
    // this->allowedToHold = false;

    this->grid.clear();
    this->grid.resize(this->height, std::vector<std::shared_ptr<BlockCell>>{this->width, nullptr});

}
void Board::levelUp(int multiplier) {
    int newLevel = currentLevel->getLevelNum() + multiplier;
    this->currentLevel = std::make_unique<Level>(newLevel, this->currentBlockHeavyEffect, this->boardProxy, this->blockSequenceFileName);
}
void Board::levelDown(int multiplier) {
    int newLevel = currentLevel->getLevelNum() - multiplier;
    this->currentLevel = std::make_unique<Level>(newLevel, this->currentBlockHeavyEffect, this->boardProxy, this->blockSequenceFileName);
}
void Board::increaseScore(int points) {
    this->currentScore += points;
}

void Board::setHeavyEffect() {
    this->currentBlockHeavyEffect = true;
}
