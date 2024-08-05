#include "dsp/taps.h"
#include "dsp/taps/low_pass.h"
#include "dsp/complex.h"
#include "dsp/stream.h"
#include <stdio.h>

struct TestStruct {
    bool a;
    int b;
};

int main() {
    dsp::taps::LowPass lp(3000, 100, 15000);

    float test = lp[0];

    dsp::Stream<float> str;

    return 0;
}