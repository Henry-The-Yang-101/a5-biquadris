#ifndef BLOCK_H
#define BLOCK_H

#include "board-proxy.h"

using CellCoords = pair<int, int>;

class BlockCell {

    private:
        BoardProxy & boardProxy;
        int clearScore;

    public:
        BlockCell(BoardProxy & boardProxy, char type);
        ~BlockCell();

        char type;
};

class Block {

    protected:
        enum class Rotation {UP, RIGHT, DOWN, LEFT};

    private:

        Rotation rotation;

        BoardProxy & boardProxy;
        int leftShift;
        int downShift;
        int level;
        char type;

        int getClearScore();
        bool checkPositionValidity(Rotation newRotation, int newX, int newY);

    public:
        Block(BoardProxy& boardProxy, char type, int level);
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