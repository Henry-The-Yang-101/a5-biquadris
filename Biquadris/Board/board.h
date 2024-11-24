#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "board-proxy.h"
#include "biquadris-proxies.h"
#include "block.h"
#include "level.h"

using Grid = std::vector<std::vector<std::shared_ptr<BlockCell>>>;
using CellCoordinate = std::pair<int, int>;

class Board {
    private:
        const BoardProxy boardProxy;
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
        bool allowedToHold;

        bool currentBlockHeavyEffect;

        Grid grid;

        const std::string blockSequenceFileName;
    public:
        Board(ManageGameStateProxy game, std::unique_ptr<Level> level, int width, int height, std::string blockSequenceFileName);
        ~Board();

        bool cellAvailable(int x, int y);
        void insertBlockCell(int x, int y, std::shared_ptr<BlockCell> cell);

        void moveBlockHorizontal(int multiplier);
        void moveBlockDown(int multiplier);
        void rotateBlockClockwise(int multiplier);
        void rotateBlockCounterClockwise(int multiplier);
        void dropBlock(int multiplier);
        void holdBlock();
        std::vector<CellCoordinate> getBlockDropPreview();

        void restart();
        void levelUp(int multiplier);
        void levelDown(int multiplier);
        void increaseScore(int points);

        void setHeavyEffect();

        int getWidth();
        int getHeight();
        int getNumBlocksPlacedWithoutClearing();
};

#endif
