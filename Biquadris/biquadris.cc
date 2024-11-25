#include "biquadris.h"

BiQuadris::BiQuadris(string sequenceFile1, string sequenceFile2, bool devMode, bool bonusFeatures, int randomSeed, int board1Lvl, int board2Lvl) :
    board1{ManageGameStateProxy{*this}, board1Lvl, sequenceFile1}, board2{ManageGameStateProxy{*this}, board2Lvl, sequenceFile2}, 
    devMode{devMode}, bonusFeatures{bonusFeatures} {}

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
