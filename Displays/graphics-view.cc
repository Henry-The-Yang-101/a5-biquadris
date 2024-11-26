#include "graphics-view.h"

GraphicsView::GraphicsView(DisplayProxy &displayProxy, bool enhanced) :
    DisplayObserver{displayProxy, enhanced}, 
    window{WINDOW_WIDTH, 1200} {
        this->charColorMap['I'] = 2;
        this->charColorMap['J'] = 3;
        this->charColorMap['L'] = 4;
    }

void GraphicsView::render() {
    int Black = 1;
    int pixelsDown = 0;
    for (int r = 0; r < this->gameGridRows; r++) {
        this->window.fillRectangle(0, pixelsDown, this->gameGridCols * PIXELS_PER_SQUARE + this->blockGapPixels + 1, this->blockGapPixels, Black);

        for (int c = 0; c < this->gameGridCols; c++) {

            char currentBlockChar = this->p1GameGrid[r][c];
            int colour = 0;

            try {
                colour = this->charColorMap.at(currentBlockChar); 
            } catch (const std::out_of_range&) {
                colour = 0;
            }

            int pixelsLeft = c * PIXELS_PER_SQUARE + c * this->blockGapPixels;

            this->window.fillRectangle(pixelsLeft + blockGapPixels, pixelsDown + this->blockGapPixels, PIXELS_PER_SQUARE, PIXELS_PER_SQUARE, colour);
            this->window.fillRectangle(pixelsLeft, pixelsDown, this->blockGapPixels, PIXELS_PER_SQUARE + this->blockGapPixels, Black);

        }

        pixelsDown += PIXELS_PER_SQUARE + this->blockGapPixels;


    }
    this->window.fillRectangle(0, pixelsDown, this->gameGridCols * PIXELS_PER_SQUARE + this->blockGapPixels + 1, this->blockGapPixels, Black);

}


