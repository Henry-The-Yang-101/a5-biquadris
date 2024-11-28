#include "graphics-view.h"

GraphicsView::GraphicsView(const DisplayProxy & displayProxy) :
    DisplayObserver{displayProxy}, 
    window{1736, 744} {

        this->charColorMap[' '] = 1;
        this->charColorMap['I'] = 2;
        this->charColorMap['J'] = 3;
        this->charColorMap['L'] = 4;
        this->charColorMap['O'] = 5;
        this->charColorMap['S'] = 6;
        this->charColorMap['Z'] = 7;
        this->charColorMap['T'] = 8;
    }

void GraphicsView::render() {

    int Black = 1;

    const BiQuadris::PlayerTurn currentPlayer = this->displayProxy.getCurrentPlayerTurn();

    this->window.drawString(0, 0, "", 0);
    this->window.drawString(0, 0, "", 0);
    this->window.drawString(0, 0, "", 0);
    this->window.drawString(0, 0, "", 0);
    this->window.drawString(0, 0, "", 0);

    // dynamic calculation of boardwidth, necessary for rendering second player's board and grid lines
    const int boardWidth = this->gameGridCols * (PIXELS_PER_SQUARE + this->blockGapPixels) + this->blockGapPixels;

    // constant for vertical/horizontal shift down for scoreboard
    const int scoreboardShiftDown = this->paddingPixels;
    const int scoreboardShiftLeft = paddingPixels + sidebarWidth + this->blockGapPixels;

    // constant for vertical shift down for game grid and objects in line with game grid
    const int gameGridShiftDown = this->paddingPixels + this->scoreboardHeight;
    const int gameGridShiftLeft = scoreboardShiftLeft;

    // vertical start position
    int shiftDown = scoreboardShiftDown;

    // left position, starting at scoreboard left edge
    int shiftLeft = scoreboardShiftLeft;

    std::string playerOneTitle = "Player 1";
    if (currentPlayer == BiQuadris::PlayerTurn::PLAYER1) {
        playerOneTitle = "--> Player 1 <--";
    }

    shiftLeft += boardWidth / 2 - playerOneTitle.size() * this->fontWidth / 2;
    this->window.drawString(shiftLeft, shiftDown - this->scoreboardSpacing, playerOneTitle, 1);

    shiftLeft = scoreboardShiftLeft;

    // render scoreboard
    this->window.fillRectangle(shiftLeft, shiftDown, boardWidth, this->scoreboardHeight, 10);

    shiftDown += this->fontHeight + this->scoreboardPadding - 2;
    shiftLeft += this->scoreboardPadding;

    int p1Level = this->displayProxy.getLevelNum(BiQuadris::PlayerTurn::PLAYER1);
    int p1Score = this->displayProxy.getCurrentScore(BiQuadris::PlayerTurn::PLAYER1);
    int p1HighScore = this->displayProxy.getHighScore(BiQuadris::PlayerTurn::PLAYER1);

    std::string player1Stats = "Level: " + std::to_string(p1Level) + " Score: " + std::to_string(p1Score) + " High Score: " + std::to_string(p1HighScore);

    this->window.drawString(shiftLeft, shiftDown, player1Stats, 1);

    // hold block container 

    shiftDown = gameGridShiftDown;

    shiftLeft = paddingPixels;

    this->window.fillRectangle(shiftLeft, shiftDown, sidebarWidth, this->holdBlocksHeight, Black);

    int holdBlockGridStartLeft = shiftLeft + sidebarPadding;

    shiftDown += sidebarPadding + this->fontHeight;
    this->window.drawString(holdBlockGridStartLeft, shiftDown, "Hold:", 0);

    shiftDown += sidebarPadding ;

    for (int r = 0; r < this->holdGridRows; r++) {

        int pixelsLeft = holdBlockGridStartLeft;

        for (int c = 0; c < this->holdGridCols; c++) {

            char currentBlockChar = this->p1HoldGrid[r][c];
            int colour = this->charColorMap.at(currentBlockChar);

            // if the background is black, we can remove drawing the gridlines <-- DELETE THIS COMMENT LATER PLUH
            this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        shiftDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }

    shiftLeft += sidebarWidth + this->blockGapPixels;


    // draw first player's board

    // reset vertical start position
    shiftDown = gameGridShiftDown;

    for (int r = 0; r < this->gameGridRows; r++) {

        // draw top border
        this->window.fillRectangle(shiftLeft, shiftDown, boardWidth, this->blockGapPixels, Black);

        // move pointer down by width of whatever was just drawn
        shiftDown += this->blockGapPixels;

        // horizontal start position (resets every row)
        int pixelsLeft = shiftLeft;

        for (int c = 0; c < this->gameGridCols; c++) {

            char currentBlockChar = this->p1GameGrid[r][c];

            if (currentPlayer == BiQuadris::PlayerTurn::PLAYER1) {
                BlockAttributes blockAttributesCurrent = this->displayProxy.getCurrentBlockAttributes(BiQuadris::PlayerTurn::PLAYER1);
                for (const auto &coord : blockAttributesCurrent.first) {
                    if (coord.first == c && coord.second + 1 == r) {
                        currentBlockChar = blockAttributesCurrent.second;
                        break;
                    }
                }

                BlockCellCoordinates previewCoordinates = this->displayProxy.getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn::PLAYER1);
                for (const auto &coord : previewCoordinates) {
                    if (coord.first == c && coord.second + 1 == r) {
                        this->window.fillRectangle(pixelsLeft, shiftDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
                        pixelsLeft += this->blockGapPixels;

                        // fill in with black
                        this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, Black);

                        // draw border
                        this->window.fillRectangle(pixelsLeft, shiftDown, this->previewBlockWeight, PIXELS_PER_SQUARE, 0);
                        this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, this->previewBlockWeight, 0);
                        this->window.fillRectangle(pixelsLeft, shiftDown + PIXELS_PER_SQUARE - this->previewBlockWeight, PIXELS_PER_SQUARE, this->previewBlockWeight, 0);
                        this->window.fillRectangle(pixelsLeft + PIXELS_PER_SQUARE - this->previewBlockWeight, shiftDown, this->previewBlockWeight, PIXELS_PER_SQUARE, 0);
                        pixelsLeft += PIXELS_PER_SQUARE;
                        currentBlockChar = 'X';
                    }
                }
            }

            if (currentBlockChar == 'X') {
                continue;
            }

            int colour = this->charColorMap.at(currentBlockChar);

            // try { // idk maybe this isnt necessary @debugged-rat @raywang1265
            //     colour = this->charColorMap.at(currentBlockChar); 
            // } catch (const std::out_of_range&) {
            //     colour = 1;
            // }

            // draw grid line
            this->window.fillRectangle(pixelsLeft, shiftDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
            pixelsLeft += this->blockGapPixels;

            // draw block
            this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE;
        }

        // draw right border
        this->window.fillRectangle(pixelsLeft, shiftDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);

        shiftDown += PIXELS_PER_SQUARE;

    }

    // draw bottom border
    this->window.fillRectangle(shiftLeft, shiftDown, boardWidth, this->blockGapPixels, Black);


    // next blocks 

    // left position of start of sidebar
    int alignNextBlocks = shiftLeft + boardWidth + this->blockGapPixels;

    // left position of start of next block grid inside of sidebar
    int nextBlockGridStartLeft = alignNextBlocks + sidebarPadding;

    // vertical start position inside of sidebar
    shiftDown = gameGridShiftDown + sidebarPadding + this->fontHeight;
    this->window.fillRectangle(alignNextBlocks, gameGridShiftDown, sidebarWidth, this->nextBlocksHeight, 1);
    this->window.drawString(nextBlockGridStartLeft, shiftDown, "Next:", 0);

    // gap between text and grid
    shiftDown += sidebarPadding;

    for (int r = 0; r < this->nextGridRows; r++) {

        int pixelsLeft = nextBlockGridStartLeft;

        for (int c = 0; c < this->nextGridCols; c++) {
            char currentBlockChar = this->p1NextGrid[r][c];
            int colour = this->charColorMap.at(currentBlockChar);

            this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        shiftDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }


    // second player scoreboard rendering

    // reset vertical start position
    shiftDown = scoreboardShiftDown;
    int secondScoreboardShiftLeft = scoreboardShiftLeft + boardWidth + 2 * this->blockGapPixels + sidebarWidth + sidebarWidth + gapBetweenGridsPixels;

    std::string playerTwoTitle = "Player 2";
    if (this->displayProxy.getCurrentPlayerTurn() == BiQuadris::PlayerTurn::PLAYER2) {
        playerTwoTitle = "--> Player 2 <--";
    }

    int secondTitleShiftLeft = secondScoreboardShiftLeft + boardWidth / 2 - playerTwoTitle.size() * this->fontWidth / 2;
    this->window.drawString(secondTitleShiftLeft, shiftDown - this->scoreboardSpacing, playerTwoTitle, 1);

    // render scoreboard
    this->window.fillRectangle(secondScoreboardShiftLeft, shiftDown, boardWidth, this->scoreboardHeight, 10);

    shiftDown += this->fontHeight + this->scoreboardPadding - 2;
    secondScoreboardShiftLeft += this->scoreboardPadding;

    int p2Level = this->displayProxy.getLevelNum(BiQuadris::PlayerTurn::PLAYER2);
    int p2Score = this->displayProxy.getCurrentScore(BiQuadris::PlayerTurn::PLAYER2);
    int p2HighScore = this->displayProxy.getHighScore(BiQuadris::PlayerTurn::PLAYER2);

    std::string player2Stats = "Level: " + std::to_string(p2Level) + " Score: " + std::to_string(p2Score) + " High Score: " + std::to_string(p2HighScore);

    this->window.drawString(secondScoreboardShiftLeft, shiftDown, player2Stats, 1);

    // second player hold block container

    // reset vertical start position
    shiftDown = gameGridShiftDown;

    // horizontal shift to the right (points to left corner of second player's board)
    shiftLeft += boardWidth + this->blockGapPixels + sidebarWidth + gapBetweenGridsPixels;

    this->window.fillRectangle(shiftLeft, shiftDown, sidebarWidth, this->holdBlocksHeight, Black);

    holdBlockGridStartLeft = shiftLeft + sidebarPadding;

    shiftDown += sidebarPadding + this->fontHeight;
    this->window.drawString(holdBlockGridStartLeft, shiftDown, "Hold:", 0);

    shiftDown += sidebarPadding ;

    for (int r = 0; r < this->holdGridRows; r++) {

        int pixelsLeft = holdBlockGridStartLeft;

        for (int c = 0; c < this->holdGridCols; c++) {

            char currentBlockChar = this->p2HoldGrid[r][c];
            int colour = this->charColorMap.at(currentBlockChar);

            // if the background is black, we can remove drawing the gridlines <-- DELETE THIS COMMENT LATER PLUH
            this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        shiftDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }

    shiftLeft += sidebarWidth + this->blockGapPixels;


    // draw second player's board

    // reset vertical start position
    shiftDown = gameGridShiftDown;
    
    for (int r = 0; r < this->gameGridRows; r++) {
        this->window.fillRectangle(shiftLeft, shiftDown, boardWidth, this->blockGapPixels, Black);
        shiftDown += this->blockGapPixels;

        int pixelsLeft = shiftLeft;

        for (int c = 0; c < this->gameGridCols; c++) {

            char currentBlockChar = this->p2GameGrid[r][c];

            if (currentPlayer == BiQuadris::PlayerTurn::PLAYER2) {
                BlockAttributes blockAttributesCurrent = this->displayProxy.getCurrentBlockAttributes(BiQuadris::PlayerTurn::PLAYER2);
                for (const auto &coord : blockAttributesCurrent.first) {
                    if (coord.first == c && coord.second + 1 == r) {
                        currentBlockChar = blockAttributesCurrent.second;
                        break;
                    }
                }

                BlockCellCoordinates previewCoordinates = this->displayProxy.getCurrentBlockDropPreviewCellCoordinates(BiQuadris::PlayerTurn::PLAYER2);
                for (const auto &coord : previewCoordinates) {
                    if (coord.first == c && coord.second + 1 == r) {
                        this->window.fillRectangle(pixelsLeft, shiftDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
                        pixelsLeft += this->blockGapPixels;

                        // fill in with black
                        this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, Black);

                        // draw border
                        this->window.fillRectangle(pixelsLeft, shiftDown, this->previewBlockWeight, PIXELS_PER_SQUARE, 0);
                        this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, this->previewBlockWeight, 0);
                        this->window.fillRectangle(pixelsLeft, shiftDown + PIXELS_PER_SQUARE - this->previewBlockWeight, PIXELS_PER_SQUARE, this->previewBlockWeight, 0);
                        this->window.fillRectangle(pixelsLeft + PIXELS_PER_SQUARE - this->previewBlockWeight, shiftDown, this->previewBlockWeight, PIXELS_PER_SQUARE, 0);
                        pixelsLeft += PIXELS_PER_SQUARE;
                        currentBlockChar = 'X';
                    }
                }
            }

            if (currentBlockChar == 'X') {
                continue;
            }


            int colour = this->charColorMap.at(currentBlockChar);

            this->window.fillRectangle(pixelsLeft, shiftDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
            pixelsLeft += this->blockGapPixels;

            this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE;

        }
        this->window.fillRectangle(pixelsLeft, shiftDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);

        shiftDown += PIXELS_PER_SQUARE;
    }

    this->window.fillRectangle(shiftLeft, shiftDown, boardWidth, this->blockGapPixels, Black);


    alignNextBlocks += shiftLeft - paddingPixels - sidebarWidth - this->blockGapPixels; // account for double counting padding
    nextBlockGridStartLeft += shiftLeft - paddingPixels - sidebarWidth - this->blockGapPixels;

    shiftDown = gameGridShiftDown + sidebarPadding + this->fontHeight;

    this->window.fillRectangle(alignNextBlocks, gameGridShiftDown, sidebarWidth, this->nextBlocksHeight, Black);
    this->window.drawString(nextBlockGridStartLeft, shiftDown, "Next:", 0);

    shiftDown += sidebarPadding;

    for (int r = 0; r < this->nextGridRows; r++) {

        int pixelsLeft = nextBlockGridStartLeft;

        for (int c = 0; c < this->nextGridCols; c++) {
            char currentBlockChar = this->p2NextGrid[r][c];
            int colour = this->charColorMap.at(currentBlockChar);

            this->window.fillRectangle(pixelsLeft, shiftDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        shiftDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }

    this->displayProxy.getCurrentBlockAttributes(BiQuadris::PlayerTurn::PLAYER1);

}


