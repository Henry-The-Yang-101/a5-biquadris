#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include <map>
#include "../Miscellaneous/observer.h"
#include "./test/biquadris-proxies.h"
#include "./display-observer.h"
#include "./window.h"

class GraphicsView : public DisplayObserver {

    private:
        Xwindow window;

    public:

        GraphicsView(DisplayProxy &displayProxy);
        ~GraphicsView() = default;

        // void render();
        // void fillRectangle();
        // void drawString();



    

};

#endif
