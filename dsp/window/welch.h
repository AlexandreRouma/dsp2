#pragma once
#include "../window.h"

namespace dsp::window {
    class Welch : public Window {
    public:
        Welch();
        
    private:
        void define();
    };
}