#ifndef BLOCK_TYPES_H
#define BLOCK_TYPES_H

#include "block.h"

// Rotation is protected, could make public to use this alias
// using ShapeMap = std::unordered_map<Block::Rotation, std::vector<std::pair<int, int>>>;

class IBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        IBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class JBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        JBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class LBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        LBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class OBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        OBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class SBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        SBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class ZBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        ZBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class TBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        TBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
};

class StarBlock : public Block {
    private:
        std::unordered_map<Rotation, std::vector<std::pair<int, int>>> baseShapeRotations;
    public:
        StarBlock(BoardProxy& board, int level);
        std::vector<std::pair<int, int>> getBaseShape(Rotation rotation) override;
        int getClearScore();
};


#endif
