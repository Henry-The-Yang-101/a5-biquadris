#ifndef BLOCK_H
#define BLOCK_H

#include "board.h"
#include "board-proxy.h"

using CellCoords = pair<int, int>;

class BlockCell {

    private:
        BoardProxy & board;
        int clearScore;

    public:
        BlockCell(BoardProxy & board, char type);
        ~BlockCell();

        char type;
};

class Block {

    protected:
        enum class Rotation {UP, RIGHT, DOWN, LEFT};

    private:

        Rotation rotation;

        BoardProxy & board;
        int leftShift;
        int downShift;
        int level;
        char type;

        int getClearScore();
        bool checkPositionValidity(Rotation newRotation, int newX, int newY);

    public:
        Block(BoardProxy& board, char type, int level);
        ~Block();

        virtual std::vector<CellCoords> getBaseShape(Rotation rotation);

        bool moveLeft();
        bool moveRight();
        bool rotateClockwise();
        bool rotateCounterClockwise();

        void drop();
        bool down();

        std::vector<CellCoords> dropPreview(); 

};

#endif