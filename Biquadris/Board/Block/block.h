#ifndef BLOCK_H
#define BLOCK_H

#include <utility>
#include "board-proxy.h"

using CellCoords = std::pair<int, int>;

class BlockCell {

    private:
        BoardProxy & boardProxy;
        const int clearScore;

    public:
        const char type;

        BlockCell(BoardProxy & boardProxy, int clearScore, char type);
        ~BlockCell();
};

class Block {

    protected:
        enum class Rotation {UP, RIGHT, DOWN, LEFT};
        Block(BoardProxy& boardProxy, char type, int numLevel);

        static Rotation rotationAfterRotatedClockwise(Rotation rotation);
        static Rotation rotationAfterRotatedCounterClockwise(Rotation rotation);

        virtual ~Block() = default;

    private:
        BoardProxy & boardProxy;
        const char type;
        const int numLevel;
        Rotation rotation;
        int rightShift = 0;
        int downShift = 0;

        virtual int getClearScore() const;
        bool checkPositionValidity(Rotation newRotation, int newrightShift, int newDownShift) const;
    public:
        virtual std::vector<CellCoords> getBaseShape(Rotation rotation) const = 0;

        bool moveLeft();
        bool moveRight();
        bool rotateClockwise();
        bool rotateCounterClockwise();

        void drop();
        bool down();

        bool checkPositionValidity() const; // This is how board is gonna check if its game over

        std::vector<CellCoords> getDropPreview() const; 

};

#endif
