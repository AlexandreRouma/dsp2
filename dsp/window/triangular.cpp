#include "triangular.h"
#include <math.h>

namespace dsp::window {
    Triangular::Triangular() {
        define();
    }

    void Triangular::define() {
        def = [](float x) { return 1.0f - fabsf(2.0f*x - 1.0f); };
    }
}