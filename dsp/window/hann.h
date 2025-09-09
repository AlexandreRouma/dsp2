#pragma once
#include "../window.h"

namespace dsp::window {
    class Hann : public Window {
    public:
        Hann();
        
    private:
        void define();
    };
}