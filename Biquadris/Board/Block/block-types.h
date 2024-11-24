#ifndef BLOCK_TYPES_H
#define BLOCK_TYPES_H

#include "block.h"

// Rotation is protected, could make public to use this alias
// using ShapeMap = std::unordered_map<Block::Rotation, std::vector<std::pair<int, int>>>;
using Shape = std::vector<std::pair<int, int>>;
using CellCoordinate = std::pair<int, int>;

class IBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        IBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class JBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        JBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class LBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        LBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class OBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        OBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class SBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        SBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class ZBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        ZBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class TBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        TBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
};

class StarBlock : public Block {
    private:
        std::unordered_map<Rotation, Shape> baseShapeRotations;
    public:
        StarBlock(BoardProxy& board, int level);
        Shape getBaseShape(Rotation rotation) override;
        int getClearScore();
};


#endif
