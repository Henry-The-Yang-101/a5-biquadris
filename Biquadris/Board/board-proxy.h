#ifndef BOARD_PROXY_H
#define BOARD_PROXY_H

#include "Block/block.h"
#include <memory>

class Board;

class BoardProxy {
    
    private:
        Board & board;
    public:
        BoardProxy(Board & board);
        ~BoardProxy();

        bool cellAvailable(int x, int y);
        void insertBlockCell(int x, int y, std::shared_ptr<BlockCell> cell);
        void increaseScore(int points);
        int getBoardWidth();
        int getBoardHeight();
        int getLevelNum();
        int getNumBlocksPlacedWithoutClearing();
};

#endif
