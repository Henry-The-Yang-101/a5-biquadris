#include "graphics-view.h"

GraphicsView::GraphicsView(DisplayProxy &displayProxy, bool enhanced) :
    DisplayObserver{displayProxy, enhanced}, 
    window{1352, 720} {

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

    // TO DO: change font color / size, standarize spacing in sidebar (easier when we can control font size)

    int Black = 1;
    int pixelsDown = paddingPixels;
    int boardWidth = this->gameGridCols * (PIXELS_PER_SQUARE + this->blockGapPixels) + this->blockGapPixels;

    for (int r = 0; r < this->gameGridRows; r++) {

        // temporarily calling multiple times, first few calls sometimes dont render
        this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);

        pixelsDown += this->blockGapPixels;

        int pixelsLeft = paddingPixels;
        for (int c = 0; c < this->gameGridCols; c++) {

            char currentBlockChar = this->p1GameGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 1;
            }

            // logging for debugging
            // std::cout << c << ", " << r << endl;
            // std::cout << "colour: " << colour << std::endl;

            this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
            pixelsLeft += this->blockGapPixels;

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE;
        }
        this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);

        pixelsDown += PIXELS_PER_SQUARE;

    }
    this->window.fillRectangle(paddingPixels, pixelsDown, boardWidth, this->blockGapPixels, Black);


    // next blocks 

    int alignNextBlocks = boardWidth + paddingPixels + this->blockGapPixels;
    int sidebarPadding = 24;

    int nextBlockGridStartLeft = boardWidth + paddingPixels + this->blockGapPixels + sidebarPadding;
    pixelsDown = paddingPixels + sidebarPadding;
    this->window.fillRectangle(alignNextBlocks, paddingPixels, sidebarWidth, boardHeightTemp, 0);
    this->window.drawString(nextBlockGridStartLeft, pixelsDown, "Next:");

    pixelsDown += sidebarPadding * 2;

    for (int r = 0; r < this->nextGridRows; r++) {

        int pixelsLeft = nextBlockGridStartLeft;

        for (int c = 0; c < this->nextGridCols; c++) {
            char currentBlockChar = this->p1NextGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 1;
            }

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        pixelsDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }

    pixelsDown += sidebarPadding;
    this->window.drawString(nextBlockGridStartLeft, pixelsDown, "Hold:");

    pixelsDown += sidebarPadding * 2;

    for (int r = 0; r < this->holdGridRows; r++) {

        int pixelsLeft = nextBlockGridStartLeft;

        for (int c = 0; c < this->holdGridCols; c++) {
            char currentBlockChar = this->p1HoldGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 1;
            }

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        pixelsDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }




    pixelsDown = paddingPixels;
    int shiftLeft = boardWidth + gapBetweenGridsPixels + sidebarWidth + paddingPixels;
    
    for (int r = 0; r < this->gameGridRows; r++) {
        this->window.fillRectangle(shiftLeft, pixelsDown, boardWidth, this->blockGapPixels, Black);
        pixelsDown += this->blockGapPixels;

        int pixelsLeft = shiftLeft;

        for (int c = 0; c < this->gameGridCols; c++) {

            char currentBlockChar = this->p2GameGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 1;
            }


            this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
            pixelsLeft += this->blockGapPixels;

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE;

        }
        this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);


        pixelsDown += PIXELS_PER_SQUARE;


    }
    this->window.fillRectangle(shiftLeft, pixelsDown, boardWidth, this->blockGapPixels, Black);




    alignNextBlocks += shiftLeft - paddingPixels; // account for double counting padding
    nextBlockGridStartLeft += shiftLeft - paddingPixels;

    pixelsDown = paddingPixels + sidebarPadding;

    this->window.fillRectangle(alignNextBlocks, paddingPixels, sidebarWidth, boardHeightTemp, 0);
    this->window.drawString(nextBlockGridStartLeft, pixelsDown, "Next:");

    pixelsDown += sidebarPadding * 2;

    for (int r = 0; r < this->nextGridRows; r++) {

        int pixelsLeft = nextBlockGridStartLeft;

        for (int c = 0; c < this->nextGridCols; c++) {
            char currentBlockChar = this->p2NextGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 1;
            }

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        pixelsDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }

    pixelsDown += sidebarPadding;
    this->window.drawString(nextBlockGridStartLeft, pixelsDown, "Hold:");

    pixelsDown += sidebarPadding * 2;

    for (int r = 0; r < this->holdGridRows; r++) {

        int pixelsLeft = nextBlockGridStartLeft;

        for (int c = 0; c < this->holdGridCols; c++) {
            char currentBlockChar = this->p2HoldGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 1;
            }

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE + this->blockGapPixels;

        }

        pixelsDown += PIXELS_PER_SQUARE + this->blockGapPixels;

    }






}


