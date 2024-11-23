#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "biquadris-proxies.h"
#include "block.h"

using Grid = std::vector<std::vector<std::shared_ptr<BlockCell>>>;

class Board {
    private:
        ManageGameStateProxy game;
        std::unique_ptr<Level> currentLevel;
        
        int width;
        int height;
        int currentScore;
        int highScore;
        int numBlocksPlacedWithoutClearing;

        std::unique_ptr<Block> currentBlock;
        std::unique_ptr<Block> nextBlock;
        std::unique_ptr<Block> blockOnHold;
        std::unique_ptr<Block> allowedToHold;

        bool currentBlockHeavyEffect;

        Grid grid;
    public:
        Board(ManageGameStateProxy game, std::unique_ptr<Level> level, int width, int height);
        ~Board();

        bool cellAvailable(int x, int y);
        void insertBlockCell(int x, int y, std::shared_ptr<BlockCell> cell);

        void moveBlockHorizontal(int multiplier);
        void moveBlockDown(int multiplier);
        void rotateBlockClockwise(int multiplier);
        void rotateBlockCounterClockwise(int multiplier);
        void dropBlock(int multiplier);
        void holdBlock();
        std::vector<std::pair<int, int>> getBlockDropPreview();

        void restart();
        void levelUp(int multiplier);
        void levelDown(int multiplier);
        void increaseScore(int points);

        void setHeavyEffect();
};

#endif
