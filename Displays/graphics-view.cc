#include "graphics-view.h"

GraphicsView::GraphicsView(DisplayProxy &displayProxy, bool enhanced) :
    DisplayObserver{displayProxy, enhanced}, 
    window{1736, 720} {

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

    this->window.drawString(0, 0, "");
    this->window.drawString(0, 0, "");
    this->window.drawString(0, 0, "");
    this->window.drawString(0, 0, "");
    this->window.drawString(0, 0, "");

    // dynamic calculation of boardwidth, necessary for rendering second player's board and grid lines
    const int boardWidth = this->gameGridCols * (PIXELS_PER_SQUARE + this->blockGapPixels) + this->blockGapPixels;

    // constant for vertical shift down for scoreboard
    const int scoreboardShiftDown = this->paddingPixels;

    // constant for vertical shift down for game grid and objects in line with game grid
    const int gameGridShiftDown = this->paddingPixels + this->scoreboardHeight;

    // vertical start position
    int shiftDown = scoreboardShiftDown;

    // left position, starting at scoreboard left edge
    int shiftLeft = paddingPixels + sidebarWidth + gapBetweenGridsPixels;

    // render scoreboard
    this->window.fillRectangle(shiftLeft, paddingPixels, boardWidth, this->scoreboardHeight, 0);

    
    // hold block container 

    shiftDown = gameGridShiftDown;

    shiftLeft = paddingPixels;

    this->window.fillRectangle(shiftLeft, shiftDown, sidebarWidth, this->holdBlocksHeight, Black);

    int holdBlockGridStartLeft = shiftLeft + sidebarPadding;

    shiftDown += sidebarPadding + this->fontHeight;
    this->window.drawString(holdBlockGridStartLeft, shiftDown, "Hold:");

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
    this->window.drawString(nextBlockGridStartLeft, shiftDown, "Next:");

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


    // second player hold block container

    // reset vertical start position
    shiftDown = gameGridShiftDown;

    // horizontal shift to the right (points to left corner of second player's board)
    shiftLeft += boardWidth + this->blockGapPixels + sidebarWidth + gapBetweenGridsPixels;

    this->window.fillRectangle(shiftLeft, shiftDown, sidebarWidth, this->holdBlocksHeight, Black);

    holdBlockGridStartLeft = shiftLeft + sidebarPadding;

    shiftDown += sidebarPadding + this->fontHeight;
    this->window.drawString(holdBlockGridStartLeft, shiftDown, "Hold:");

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
    this->window.drawString(nextBlockGridStartLeft, shiftDown, "Next:");

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

}


