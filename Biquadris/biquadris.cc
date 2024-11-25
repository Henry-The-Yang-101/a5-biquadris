#include "biquadris.h"
#include "./biquadris-proxies.h"

BiQuadris::BiQuadris(std::string sequenceFile1, std::string sequenceFile2, bool devMode, bool bonusFeatures, int randomSeed, int board1Lvl, int board2Lvl) :
    devMode{devMode}, bonusFeatures{bonusFeatures}, game{*this}, visualEffectProxy{*this}, boardActionProxy{*this}, levelBlockGenProxy{*this}, displayProxy{*this}, 
    board1{this->game, board1Lvl, sequenceFile1}, board2{this->game, board2Lvl, sequenceFile2} {

        
}

// void moveBlockHorizontal(int multiplier);
// void moveBlockDown(int multiplier);
// void rotateBlockClockwise(int multiplier);
// void rotateBlockCounterClockwise(int multiplier);
// void dropBlock(int multiplier);
// void holdBlock();
// void restartBoard();
// void levelUp(int multiplier);
// void levelDown(int multiplier);
// void enableRandom();
// void disableRandom(string blockSequenceFile);
// void replaceCurrentBlock(char blockType);
