#ifndef BLOCK_TYPES_H
#define BLOCK_TYPES_H

#include "block.h"
#include <unordered_map>

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;

class IBlock : public Block {
    private:
        static const std::unordered_map<Rotation, BlockCellCoordinates> BASE_SHAPE_ROTATIONS;
        
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;
    public:
        IBlock(BoardProxy& board, int level);      
};

class JBlock : public Block {
    private:
        static const std::unordered_map<Rotation, BlockCellCoordinates> BASE_SHAPE_ROTATIONS;
    
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;
    public:
        JBlock(BoardProxy& board, int level);
};

class LBlock : public Block {
    private:
        static const std::unordered_map<Rotation, BlockCellCoordinates> BASE_SHAPE_ROTATIONS;
            
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;

    public:
        LBlock(BoardProxy& board, int level);
};

class OBlock : public Block {
    private:
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;

    public:
        OBlock(BoardProxy& board, int level);
};

class SBlock : public Block {
    private:
        static const std::unordered_map<Rotation, BlockCellCoordinates> BASE_SHAPE_ROTATIONS;
        
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;

    public:
        SBlock(BoardProxy& board, int level);
};

class ZBlock : public Block {
    private:
        static const std::unordered_map<Rotation, BlockCellCoordinates> BASE_SHAPE_ROTATIONS;

        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;

    public:
        ZBlock(BoardProxy& board, int level);
};

class TBlock : public Block {
    private:
        static const std::unordered_map<Rotation, BlockCellCoordinates> BASE_SHAPE_ROTATIONS;
    
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;

    public:
        TBlock(BoardProxy& board, int level);
};

class StarBlock : public Block {
    private:
        
        int getClearScore() const override;
        BlockCellCoordinates getBaseShape(Rotation rotation) const override;
        char getType() const override;

    public:
        StarBlock(BoardProxy& board, int level);
};

#endif
