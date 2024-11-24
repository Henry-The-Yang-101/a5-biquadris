#include "block-types.h"

IBlock::IBlock(BoardProxy & board, int level) : Block(board, 'I', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
        {Rotation::RIGHT, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
        {Rotation::DOWN,  {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
        {Rotation::LEFT, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}}
    };
}

Shape IBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}

JBlock::JBlock(BoardProxy & board, int level) : Block(board, 'J', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 0}, {1, 0}, {2, 0}, {0, 1}}},
        {Rotation::RIGHT, {{0, 0}, {1, 0}, {2, 0}, {2, 1}}},
        {Rotation::DOWN, {{0, 1}, {1, 1}, {2, 1}, {2, 0}}},
        {Rotation::LEFT, {{0, 0}, {0, 1}, {1, 1}, {2, 1}}}
    };
}

Shape JBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}

LBlock::LBlock(BoardProxy & board, int level) : Block(board, 'L', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 0}, {1, 0}, {2, 0}, {2, 1}}},
        {Rotation::RIGHT, {{0, 0}, {0, 1}, {0, 2}, {1, 0}}},
        {Rotation::DOWN, {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
        {Rotation::LEFT, {{0, 2}, {1, 0}, {1, 1}, {1, 2}}}
    };
}

Shape LBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}

OBlock::OBlock(BoardProxy & board, int level) : Block(board, 'O', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
        {Rotation::RIGHT, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
        {Rotation::DOWN, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
        {Rotation::LEFT, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}}
    };
}

Shape OBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}

SBlock::SBlock(BoardProxy & board, int level) : Block(board, 'S', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
        {Rotation::RIGHT, {{0, 1}, {0, 2}, {1, 1}, {1, 0}}},
        {Rotation::DOWN, {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
        {Rotation::LEFT, {{0, 1}, {0, 2}, {1, 1}, {1, 0}}}
    };
}

Shape SBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}

ZBlock::ZBlock(BoardProxy & board, int level) : Block(board, 'Z', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 1}, {1, 1}, {1, 0}, {2, 0}}},
        {Rotation::RIGHT, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
        {Rotation::DOWN, {{0, 1}, {1, 1}, {1, 0}, {2, 0}}},
        {Rotation::LEFT, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}}
    };
}

Shape ZBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}

TBlock::TBlock(BoardProxy & board, int level) : Block(board, 'T', level) {
    baseShapeRotations = {
        {Rotation::UP, {{0, 1}, {1, 1}, {2, 1}, {1, 0}}},
        {Rotation::RIGHT, {{0, 1},{1, 0}, {1, 1}, {1, 2}}},
        {Rotation::DOWN, {{0, 0}, {1, 0}, {2, 0}, {1, 1}}},
        {Rotation::LEFT, {{0, 0}, {0, 1}, {0, 2}, {1, 1}}}
    };
}

Shape TBlock::getBaseShape(Rotation rotation) {
    return baseShapeRotations[rotation];
}
