#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "board-proxy.h"
#include "../biquadris-proxies.h"
#include "block.h"
#include "level.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;
using BlockAttributes = std::pair<BlockCellCoordinates, char>;
using Grid = std::vector<std::vector<std::shared_ptr<BlockCell>>>

class Board {
    private:
        static const int WIDTH = 11;
        static const int HEIGHT = 15;
        static const int NUM_RESERVE_ROWS = 3;

        const int initLevelNum;

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
        bool allowedToHold = true;

        bool currentBlockHeavyEffect = false;

        Grid grid;

        void setUpEmptyGrid();
        void setCurrentLevel(int levelNum);
        void applyLevelHeaviness();
        void applyHeavyEffect();
        int countAndClearFilledRows();
        int calculateScoreIncrease(int linesCleared);

    public:
        Board(ManageGameStateProxy & game, int initLevelNum, std::string blockSequenceFileName);
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

        void restart();
        void levelUp(int multiplier);
        void levelDown(int multiplier);
        void increaseScore(int points);

        void setHeavyEffect();
        void setCurrentBlock(char blockType);

        void setLevelRandomEnabled(bool enabled);

        int getWidth();
        int getHeight();
        int getNumBlocksPlacedWithoutClearing();

        int getCurrentScore() const;
        int getHighScore() const;

        int getLevelNum() const;

        BlockCellCoordinates getCurrentBlockDropPreviewCellCoordinates() const;
        BlockAttributes getCurrentBlockAttributes() const;
        BlockAttributes getNextBlockAttributes() const;
        BlockAttributes getNextBlockAttributes() const;
        BlockAttributes getHeldBlockAttributes() const;

        Grid getGrid() const;

};

#endif
