#include "hann.h"
#include "../constants.h"

namespace dsp::window {
    Hann::Hann() {
        define();
    }

    void Hann::define() {
        def = [](float x) {
            float y = sinf(DSP_PI*x);
            return y*y;
        };
    }
}