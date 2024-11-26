#include "graphics-view.h"

GraphicsView::GraphicsView(DisplayProxy &displayProxy, bool enhanced) :
    DisplayObserver{displayProxy, enhanced}, 
    window{1800, 1000} {
        this->charColorMap['I'] = 2;
        this->charColorMap['J'] = 3;
        this->charColorMap['L'] = 4;
        this->charColorMap['O'] = 5;
        this->charColorMap['S'] = 6;
        this->charColorMap['Z'] = 7;
        this->charColorMap['z'] = 7;
        this->charColorMap['T'] = 8;
    }

void GraphicsView::render() {
    int Black = 1;
    int pixelsDown = 0;
    int boardWidth = this->gameGridCols * (PIXELS_PER_SQUARE + this->blockGapPixels) + this->blockGapPixels;

    for (int r = 0; r < this->gameGridRows; r++) {

        // temporarily calling multiple times, first few calls sometimes dont render
        this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);
        this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);

        pixelsDown += this->blockGapPixels;

        int pixelsLeft = 0;
        for (int c = 0; c < this->gameGridCols; c++) {

            char currentBlockChar = this->p1GameGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 0;
            }

            this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);
            pixelsLeft += this->blockGapPixels;

            this->window.fillRectangle(pixelsLeft, pixelsDown, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            pixelsLeft += PIXELS_PER_SQUARE;
        }
        this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE, Black);

        pixelsDown += PIXELS_PER_SQUARE;

    }
    this->window.fillRectangle(0, pixelsDown, boardWidth, this->blockGapPixels, Black);

    pixelsDown = 0;
    // temporary to simulate spacing in between
    const int gapBetweenGridsPixels = 200;
    int shiftLeft = boardWidth + gapBetweenGridsPixels;
    
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

}


