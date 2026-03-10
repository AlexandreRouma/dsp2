#include "boxcar.h"

namespace dsp::window {
    Boxcar::Boxcar() {
        define();
    }

    void Boxcar::define() {
        def = [](float x) { return 1.0f; };
    }
}