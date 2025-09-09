#include "welch.h"

namespace dsp::window {
    Welch::Welch() {
        define();
    }

    void Welch::define() {
        def = [](float x) {
            float y = 2.0f*x - 1.0f;
            return 1.0f - y*y;
        };
    }
}