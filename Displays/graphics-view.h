#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include <map>
#include "./display-observer.h"
#include "./window.h"

const int WINDOW_WIDTH = 800;
const int PIXELS_PER_SQUARE = 28;

class GraphicsView : public DisplayObserver {

    private:
        Xwindow window;
        std::map<char, int> charColorMap;
        const int blockGapPixels = 4;
        const int paddingPixels = 40;
        const int gapBetweenGridsPixels = 24;
        const int sidebarWidth = 4 * PIXELS_PER_SQUARE + 40;
        const int sidebarPadding = 20;
        const int nextBlocksHeight = sidebarPadding * 2 + 16 * PIXELS_PER_SQUARE + 8 * blockGapPixels;
        const int holdBlocksHeight = sidebarPadding * 2 + 2 * PIXELS_PER_SQUARE + 1 * blockGapPixels;
        const int fontHeight = 20;

    public:

        GraphicsView(DisplayProxy &displayProxy, bool enhanced);
        ~GraphicsView() = default;

        void render();
        // void fillRectangle();
        // void drawString();


};

#endif
