#include "rectangular.h"

namespace dsp::window {
    Rectangular::Rectangular() {
        define();
    }

    void Rectangular::define() {
        def = [](float x) { return 1.0f; };
    }
}