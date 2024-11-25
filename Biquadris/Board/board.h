#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "board-proxy.h"
#include "biquadris-proxies.h"
#include "block.h"
#include "level.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;

class Board {
    private:
        static const int WIDTH = 11;
        static const int HEIGHT = 15;
        static const int NUM_RESERVE_ROWS = 3;

        std::string blockSequenceFileName;
        BoardProxy boardProxy;
        ManageGameStateProxy & gameProxy;
        std::unique_ptr<Level> currentLevel;

        int currentScore = 0;
        int highScore = 0;
        int numBlocksPlacedWithoutClearing = 0;

        std::unique_ptr<Block> currentBlock;
        std::unique_ptr<Block> nextBlock;
        std::unique_ptr<Block> blockOnHold;
        bool allowedToHold;

        bool currentBlockHeavyEffect = false;

        std::vector<std::vector<std::shared_ptr<BlockCell>>> grid;

        void setLevel(int levelNum);
        void applyLevelHeaviness();
        void applyHeavyEffect();
        int countAndClearFilledRows();

    public:
        Board(ManageGameStateProxy & game, int startLevelNum, std::string blockSequenceFileName, bool allowedToHold);
        ~Board() = default;

        bool cellAvailable(int column, int row);
        void insertBlockCell(int column, int row, std::shared_ptr<BlockCell> cell);

        void moveBlockLeft(int multiplier);
        void moveBlockRight(int multiplier);
        void moveBlockDown(int multiplier);
        void rotateBlockClockwise(int multiplier);
        void rotateBlockCounterClockwise(int multiplier);
        void dropBlock(int multiplier);
        void holdBlock();
        BlockCellCoordinates getBlockDropPreview();

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
