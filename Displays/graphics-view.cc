#include "graphics-view.h"

GraphicsView::GraphicsView(DisplayProxy &displayProxy) :
    DisplayObserver{displayProxy, true}, window{500, 500} {}
