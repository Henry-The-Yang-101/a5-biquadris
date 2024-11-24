#ifndef BLOCK_H
#define BLOCK_H

#include <utility>
#include "board-proxy.h"

using CellCoordinate = std::pair<int, int>;

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
        virtual std::vector<CellCoordinate> getBaseShape(Rotation rotation) const = 0;
        std::vector<CellCoordinate> getCellCoordinates(Rotation newRotation, int newrightShift, int newDownShift) const;
        bool checkPositionValidity(const std::vector<CellCoordinate> & coords) const;

    public:
        bool moveLeft();
        bool moveRight();
        bool rotateClockwise();
        bool rotateCounterClockwise();
        bool down();

        void drop();

        std::vector<CellCoordinate> getCellCoordinates() const;
        std::vector<CellCoordinate> getDropPreviewCellCoordinate() const;

        bool checkPositionValidity() const; // This is how board is gonna check if its game over
        // board should run this right after constructing Block

};

#endif
