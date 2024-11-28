#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include <map>
#include "./display-observer.h"
#include "./window.h"

const int PIXELS_PER_SQUARE = 28;

class GraphicsView : public DisplayObserver {

    private:
        Xwindow window;
        std::map<char, int> charColorMap;
        const int blockGapPixels = 4;
        const int paddingPixels = 36;
        const int gapBetweenGridsPixels = 24;
        const int fontHeight = 20;
        const int fontWidth = 10;
        const int sidebarPadding = 20;
        const int sidebarWidth = 4 * PIXELS_PER_SQUARE + 3 * blockGapPixels + sidebarPadding * 2;
        const int nextBlocksHeight = 3 * sidebarPadding + 16 * PIXELS_PER_SQUARE + 8 * blockGapPixels + fontHeight;
        const int holdBlocksHeight = 3 * sidebarPadding + 2 * PIXELS_PER_SQUARE + 1 * blockGapPixels + fontHeight;
        const int scoreboardSpacing = 4;
        const int scoreboardPadding = 8;
        const int scoreboardHeight = scoreboardPadding * 2 + fontHeight;
        const int previewBlockWeight = 1;

        void render() override;

    public:
        GraphicsView(const DisplayProxy & displayProxy);

        // void fillRectangle();
        // void drawString();


};

#endif
