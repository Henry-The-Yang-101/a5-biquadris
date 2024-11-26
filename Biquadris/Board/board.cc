#include <stdexcept>
#include "board.h"
#include "./Level/level.h"
#include "./Level/all-levels.h"
#include "./Block/block-types.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using BlockAttributes = std::pair<BlockCellCoordinates, char>;

Board::Board(InformGameStateProxy & informGameStateProxy, int initLevelNum, std::string blockSequenceFileName) : 
    initLevelNum{initLevelNum}, boardProxy{*this}, informGameStateProxy{informGameStateProxy}, blockSequenceFileName{blockSequenceFileName} {

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
        this->grid.emplace(this->grid.begin(), WIDTH, nullptr);
    }
    return clearedRows;
}

int Board::calculateScoreIncrease(int linesCleared) {
    return (this->currentLevel->getLevelNum() + linesCleared) * (this->currentLevel->getLevelNum() + linesCleared);
}

bool Board::cellAvailable(int column, int row) const {
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
            this->informGameStateProxy.informGameOver();
            break;
        }
        multiplier--;
    }
    if (this->currentLevel->checkCustomRuleCondition()) {
        this->currentLevel->executeCustomRuleAction();
        totalClearedRows += this->countAndClearFilledRows();
    }
    this->allowedToHold = true;
    this->currentBlockHeavyEffect = false;
    this->currentScore += this->calculateScoreIncrease(totalClearedRows);
    this->informGameStateProxy.informCurrentBoardPlacedBlock(totalClearedRows);
}

void Board::holdBlock() {
    if (this->allowedToHold) {

        std::swap(this->currentBlock, this->heldBlock);

        // replace current block with nextblock if initially no block on hold
        if (this->currentBlock == nullptr) {
            this->currentBlock = std::move(this->nextBlock);
            this->nextBlock = std::move(this->currentLevel->cycleBlock());
        } 
        this->allowedToHold = false;

        if (!this->currentBlock->isValidPosition()) {
            this->informGameStateProxy.informGameOver();
        }
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
    this->heldBlock = nullptr;
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

void Board::setBlindEffect(bool enabled) {
    this->blindEffectEnabled = enabled;
}

void Board::setHeavyEffect() {
    this->currentBlockHeavyEffect = true;
}

int Board::getHeight() const {
    return this->HEIGHT + this->NUM_RESERVE_ROWS;
}

int Board::getWidth() const {
    return this->WIDTH;
}

int Board::getNumBlocksPlacedWithoutClearing() const {
    return this->numBlocksPlacedWithoutClearing;
}

BlockCellCoordinates Board::getCurrentBlockDropPreviewCellCoordinates() const {
    return this->currentBlock->getDropPreviewCellCoordinates();
}

BlockAttributes Board::getCurrentBlockAttributes() const {
    return {this->currentBlock->getCellCoordinates(), this->currentBlock->getType()};
}

BlockAttributes Board::getNextBlockAttributes() const {
    return {this->nextBlock->getCellCoordinates(), this->nextBlock->getType()};
}

BlockAttributes Board::getHeldBlockAttributes() const {
    return {this->heldBlock->getCellCoordinates(), this->heldBlock->getType()};
}

std::vector<BlockAttributes> Board::getBlockAttributesBacklog() const {
    return this->currentLevel->getBlockAttributesBacklog();
}

void Board::replaceCurrentBlock(char blockType) {
    switch (blockType) {
        case 'I': this->currentBlock = std::make_unique<IBlock>(this->boardProxy, blockSequenceFileName); break;
        case 'J': this->currentBlock = std::make_unique<JBlock>(this->boardProxy, blockSequenceFileName); break;
        case 'L': this->currentBlock = std::make_unique<LBlock>(this->boardProxy, blockSequenceFileName); break;
        case 'O': this->currentBlock = std::make_unique<OBlock>(this->boardProxy, blockSequenceFileName); break;
        case 'S': this->currentBlock = std::make_unique<SBlock>(this->boardProxy, blockSequenceFileName); break;
        case 'Z': this->currentBlock = std::make_unique<ZBlock>(this->boardProxy, blockSequenceFileName); break;
        case 'T': this->currentBlock = std::make_unique<TBlock>(this->boardProxy, blockSequenceFileName); break;
    }

    if (!this->currentBlock->isValidPosition()) {
        this->informGameStateProxy.informGameOver();
    }
}

void Board::setLevelRandomEnabled(bool enabled) {
    if (RandomizedLevel::RANDOMIZED_LEVEL_NUMS.contains(this->currentLevel->getLevelNum())) {
        static_cast<RandomizedLevel*>(this->currentLevel.get())->setRandomEnabled(enabled);
    } else {
        throw std::runtime_error("Invalid: not a random level!");
    }
}

void Board::setBlockSequenceFile(std::string & blockSequenceFile) {
    this->currentLevel->setBlockSequenceFile(blockSequenceFile);
    this->blockSequenceFileName = blockSequenceFile;
}

int Board::getCurrentScore() const {
    return this->currentScore;
}

int Board::getHighScore() const {
    return this->highScore;
}

int Board::getLevelNum() const {
    return this->currentLevel->getLevelNum();
}

bool Board::getBlindEffectEnabled () const {
    return this->blindEffectEnabled;
}
