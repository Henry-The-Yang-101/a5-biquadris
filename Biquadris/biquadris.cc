#include "biquadris.h"
#include "./biquadris-proxies.h"

BiQuadris::BiQuadris(std::string sequenceFile1, std::string sequenceFile2, bool devMode, bool bonusFeatures, int randomSeed, int board1Lvl, int board2Lvl) :
    devMode{devMode}, bonusFeatures{bonusFeatures}, game{*this}, visualEffectProxy{*this}, boardActionProxy{*this}, levelBlockGenProxy{*this}, displayProxy{*this}, 
    board1{this->game, board1Lvl, sequenceFile1}, board2{this->game, board2Lvl, sequenceFile2} {

        
}

void BiQuadris::moveBlockLeft(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.moveBlockLeft(multiplier);
    } else {
        this->board2.moveBlockLeft(multiplier);
    }
}

void BiQuadris::moveBlockRight(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.moveBlockRight(multiplier);
    } else {
        this->board2.moveBlockRight(multiplier);
    }
}
void BiQuadris::moveBlockDown(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.moveBlockDown(multiplier);
    } else {
        this->board2.moveBlockDown(multiplier);
    }
}

void BiQuadris::rotateBlockClockwise(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.rotateBlockClockwise(multiplier);
    } else {
        this->board2.rotateBlockClockwise(multiplier);
    }
}
void BiQuadris::rotateBlockCounterClockwise(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.rotateBlockCounterClockwise(multiplier);
    } else {
        this->board2.rotateBlockCounterClockwise(multiplier);
    }
}
void BiQuadris::dropBlock(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.dropBlock(multiplier);
    } else {
        this->board2.dropBlock(multiplier);
    }
}

void BiQuadris::holdBlock() {
    if (this->currentBoardTurn == 1) {
        this->board1.holdBlock();
    } else {
        this->board2.holdBlock();
    }
}

void BiQuadris::restartBoard() {
    if (this->currentBoardTurn == 1) {
        this->board1.restart();
    } else {
        this->board2.restart();
    }
}

void BiQuadris::levelUp(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.levelUp(multiplier);
    } else {
        this->board2.levelUp(multiplier);
    }
}

void BiQuadris::levelDown(int multiplier) {
    if (this->currentBoardTurn == 1) {
        this->board1.levelDown(multiplier);
    } else {
        this->board2.levelDown(multiplier);
    }
}

void BiQuadris::replaceCurrentBlock(char blockType) {
    if (this->currentBoardTurn == 1) {
        this->board1.setCurrentBlock(blockType);
    } else {
        this->board2.setCurrentBlock(blockType);
    }
}

void BiQuadris::enableRandom() {
    if (this->currentBoardTurn == 1) {
        this->board1.setLevelRandomEnabled(true);
    } else {
        this->board2.setLevelRandomEnabled(true);
    }
}

void BiQuadris::disableRandom(std::string blockSequenceFile) {
    if (this->currentBoardTurn == 1) {
        this->board1.setLevelRandomEnabled(false);
    } else {
        this->board2.setLevelRandomEnabled(false);
    }
}

// getters
Grid BiQuadris::getGrid(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getGrid();
    } else {
        return this->board2.getGrid();
    }
}
BlockAttributes BiQuadris::getCurrentBlockAttributes(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getCurrentBlockAttributes();
    } else {
        return this->board2.getCurrentBlockAttributes();
    }
}

BlockAttributes BiQuadris::getNextBlockAttributes(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getNextBlockAttributes();
    } else {
        return this->board2.getNextBlockAttributes();
    }
}

BlockAttributes BiQuadris::getHeldBlockAttributes(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getHeldBlockAttributes();
    } else {
        return this->board2.getHeldBlockAttributes();
    }
}

// vector<BlockAttributes> BiQuadris::getBlockBacklog(int whichBoard) const {
    
// }

int BiQuadris::getCurrentScore(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getCurrentScore();
    } else {
        return this->board2.getCurrentScore();
    }
}

int BiQuadris::getHighScore(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getHighScore();
    } else {
        return this->board2.getHighScore();
    }
}

int BiQuadris::getLevel(int whichBoard) const {
    if (whichBoard == 1) {
        return this->board1.getLevelNum();
    } else {
        return this->board2.getLevelNum();
    }
}

bool BiQuadris::getIsGameOver() const {
    return this->isGameOver;
}

int BiQuadris::getCurrentBoardTurn() const {
    return this->currentBoardTurn;
}

bool BiQuadris::getCanUseSpecialAction() const {
    return this->canUseSpecialAction;
}


// setters
void BiQuadris::setBonusFeatures(bool isOn) {
    this->bonusFeatures = isOn;
}

void BiQuadris::setDevMode(bool isOn) {
    this->devMode = isOn;
}

// void BiQuadris::blindEffect() {
//     if (this->currentBoardTurn == 1) {
//         this->board1.setBlindEffect();
//     } else {
//         this->board2.setBlindEffect();
//     }
// }

void BiQuadris::heavyEffect() {
    if (this->currentBoardTurn == 1) {
        this->board1.setHeavyEffect();
    } else {
        this->board2.setHeavyEffect();
    }
}

// void BiQuadris::forceEffect(char blockType) {

// }


