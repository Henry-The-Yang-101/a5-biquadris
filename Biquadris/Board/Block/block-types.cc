#include "block-types.h"
#include "../board-proxy.h"

using CellCoordinate = std::pair<int, int>;
using BlockCellCoordinates = std::vector<CellCoordinate>;


// IBlock definitions
IBlock::IBlock(BoardProxy & board) : Block{board} {}

const std::unordered_map<Block::Rotation, BlockCellCoordinates> IBlock::BASE_SHAPE_ROTATIONS = {
    { Rotation::UP, {{0, 0}, {1, 0}, {2, 0}, {3, 0}} },
    { Rotation::RIGHT, {{0, -3}, {0, -2}, {0, -1}, {0, 0}} },
    { Rotation::DOWN, {{0, 0}, {1, 0}, {2, 0}, {3, 0}} },
    { Rotation::LEFT, {{0, -3}, {0, -2}, {0, -1}, {0, 0}} }
};

BlockCellCoordinates IBlock::getBaseShape(Rotation rotation) const { return BASE_SHAPE_ROTATIONS.at(rotation); }

char IBlock::getType() const { return 'I'; }


// JBlock definitions
JBlock::JBlock(BoardProxy & board) : Block{board} {}

const std::unordered_map<Block::Rotation, BlockCellCoordinates> JBlock::BASE_SHAPE_ROTATIONS = {
    { Rotation::UP, {{0, -1}, {0, 0}, {1, 0}, {2, 0}} },
    { Rotation::RIGHT, {{0, -2}, {1, -2}, {0, -1}, {0, 0}} },
    { Rotation::DOWN, {{0, -1}, {1, -1}, {2, -1}, {2, 0}} },
    { Rotation::LEFT, {{1, -2}, {1, -1}, {0, 0}, {1, 0}} }
};

BlockCellCoordinates JBlock::getBaseShape(Rotation rotation) const { return BASE_SHAPE_ROTATIONS.at(rotation); }

char JBlock::getType() const { return 'J'; }


// LBlock definitions
LBlock::LBlock(BoardProxy & board) : Block{board} {}

const std::unordered_map<Block::Rotation, BlockCellCoordinates> LBlock::BASE_SHAPE_ROTATIONS = {
    { Rotation::UP, {{2, -1}, {0, 0}, {1, 0}, {2, 0}} },
    { Rotation::RIGHT, {{0, -2}, {0, -1}, {0, 0}, {1, 0}} },
    { Rotation::DOWN, {{0, -1}, {1, -1}, {2, -1}, {0, 0}} },
    { Rotation::LEFT, {{0, -2}, {0, -1}, {0, 0}, {1, 0}} }
};

BlockCellCoordinates LBlock::getBaseShape(Rotation rotation) const { return BASE_SHAPE_ROTATIONS.at(rotation); }

char LBlock::getType() const { return 'L'; }


// OBlock definitions
OBlock::OBlock(BoardProxy & board) : Block{board} {}

BlockCellCoordinates OBlock::getBaseShape(Rotation rotation) const { return {{0, -1}, {1, -1}, {0, 0}, {1, 0}}; }

char OBlock::getType() const { return 'O'; }


// SBlock definitions
SBlock::SBlock(BoardProxy & board) : Block{board} {}

const std::unordered_map<Block::Rotation, BlockCellCoordinates> SBlock::BASE_SHAPE_ROTATIONS = {
    { Rotation::UP, {{1, -1}, {2, -1}, {0, 0}, {1, 0}} },
    { Rotation::RIGHT, {{0, -2}, {0, -1}, {1, -1}, {1, 0}} },
    { Rotation::DOWN, {{1, -1}, {2, -1}, {0, 0}, {1, 0}} },
    { Rotation::LEFT, {{0, -2}, {0, -1}, {1, -1}, {1, 0}} }
};

BlockCellCoordinates SBlock::getBaseShape(Rotation rotation) const { return BASE_SHAPE_ROTATIONS.at(rotation); }

char SBlock::getType() const { return 'S'; }


// ZBlock definitions
ZBlock::ZBlock(BoardProxy & board) : Block{board} {}

const std::unordered_map<Block::Rotation, BlockCellCoordinates> ZBlock::BASE_SHAPE_ROTATIONS = {
    { Rotation::UP, {{0, -1}, {1, -1}, {1, 0}, {2, 0}} },
    { Rotation::RIGHT, {{1, -2}, {0, -1}, {1, -1}, {0, 0}} },
    { Rotation::DOWN, {{0, -1}, {1, -1}, {1, 0}, {2, 0}} },
    { Rotation::LEFT, {{1, -2}, {0, -1}, {1, -1}, {0, 0}} }
};

BlockCellCoordinates ZBlock::getBaseShape(Rotation rotation) const { return BASE_SHAPE_ROTATIONS.at(rotation); }

char ZBlock::getType() const { return 'Z'; }


// TBlock definitions
TBlock::TBlock(BoardProxy & board) : Block{board} {}

const std::unordered_map<Block::Rotation, BlockCellCoordinates> TBlock::BASE_SHAPE_ROTATIONS = {
    { Rotation::UP, {{0, -1}, {1, -1}, {2, -1}, {1, 0}} },
    { Rotation::RIGHT, {{1, -2}, {0, -1}, {1, -1}, {1, 0}} },
    { Rotation::DOWN, {{1, -1}, {0, 0}, {1, 0}, {2, 0}} },
    { Rotation::LEFT, {{0, -2}, {0, -1}, {1, -1}, {0, 0}} }
};

BlockCellCoordinates TBlock::getBaseShape(Rotation rotation) const { return BASE_SHAPE_ROTATIONS.at(rotation); }

char TBlock::getType() const { return 'T'; }


// StarBlock definitions
StarBlock::StarBlock(BoardProxy & board) : Block{board} {}

int StarBlock::getClearScore() const {
    return 0;
}

// Base shape is at the middle of the board
BlockCellCoordinates StarBlock::getBaseShape(Rotation rotation) const { return {{this->boardProxy.getBoardWidth() - (this->boardProxy.getBoardWidth() / 2), 0}};}

char StarBlock::getType() const { return '*'; }
