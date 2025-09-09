#pragma once
#include "../window.h"

namespace dsp::window {
    class Triangular : public Window {
    public:
        Triangular();
        
    private:
        void define();
    };
}