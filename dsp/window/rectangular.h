#pragma once
#include "../window.h"

namespace dsp::window {
    class Rectangular : public Window {
    public:
        /**
         * Compute the value of the window function.
         * @param x Point at which to compute the window at. Must be bounded between 0 and 1.
         * @return Value of the window bounded between 0 and 1.
        */
        inline float operator()(float x) const { return 1.0f; }
    };
}