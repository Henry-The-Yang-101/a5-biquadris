#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include <map>
#include "./display-observer.h"
#include "./window.h"

const int WINDOW_WIDTH = 800;
const int PIXELS_PER_SQUARE = 32;

class GraphicsView : public DisplayObserver {

    private:
        Xwindow window;
        std::map<char, int> charColorMap;
        const int blockGapPixels = 4;

    public:

        GraphicsView(DisplayProxy &displayProxy, bool enhanced);
        ~GraphicsView() = default;

        void render();
        // void fillRectangle();
        // void drawString();


};

#endif
