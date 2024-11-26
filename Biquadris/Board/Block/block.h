#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <utility>

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;

class BoardProxy;

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
        BoardProxy & boardProxy;

        Block(BoardProxy& boardProxy);

    private:
        const int numLevel;
        Rotation rotation;
        int rightShift = 0;
        int downShift = 0;

        static Rotation rotationAfterRotatedClockwise(Rotation rotation);
        static Rotation rotationAfterRotatedCounterClockwise(Rotation rotation);

        virtual int getClearScore() const;
        virtual BlockCellCoordinates getBaseShape(Rotation rotation) const = 0;
        
        BlockCellCoordinates getCellCoordinates(Rotation newRotation, int newrightShift, int newDownShift) const;
        bool isValidPosition(const BlockCellCoordinates & cellCoords) const;

    public:
        bool moveLeft();
        bool moveRight();
        bool rotateClockwise();
        bool rotateCounterClockwise();
        bool down();

        void drop();

        BlockCellCoordinates getCellCoordinates() const;
        BlockCellCoordinates getDropPreviewCellCoordinates() const;
        virtual char getType() const = 0;

        bool isValidPosition() const;
        virtual ~Block() = default;
};

#endif
