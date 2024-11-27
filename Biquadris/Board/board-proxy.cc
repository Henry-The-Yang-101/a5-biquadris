#include "board-proxy.h"
#include "board.h"

BoardProxy::BoardProxy(Board & board) : board{board} {}
BoardProxy::~BoardProxy() {}

bool BoardProxy::cellAvailable(int x, int y) {
    return this->board.cellAvailable(x, y);
}

void BoardProxy::insertBlockCell(int x, int y, std::shared_ptr<BlockCell> cell) {
    this->board.insertBlockCell(x, y, cell);
}

void BoardProxy::increaseScore(int points) {
    this->board.increaseScore(points);
}

int BoardProxy::getBoardWidth() {
    return this->board.getWidth();
}

int BoardProxy::getBoardHeight() {
    return this->board.getHeight();
}

int BoardProxy::getLevelNum() {
    return this->board.getLevelNum();
}

int BoardProxy::getNumBlocksPlacedWithoutClearing() {
    return this->board.getNumBlocksPlacedWithoutClearing();
}
