#pragma once
#include "../taps.h"

namespace dsp::taps {
    class RootRaisedCosine : public Taps<float> {
    public:

    private:
        void generate();
        
        float beta;
        float symbolrate;
        float samplerate;
    };
}
