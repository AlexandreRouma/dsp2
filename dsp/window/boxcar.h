#pragma once
#include "../window.h"

namespace dsp::window {
    class Boxcar : public Window {
    public:
        Boxcar();
        
    private:
        void define();
    };
}