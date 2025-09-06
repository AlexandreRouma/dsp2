#include <stdio.h>
#include "dsp/buffer.h"
#include "dsp/taps.h"
#include "dsp/complex.h"
#include <volk/volk.h>

void testFunc(const float* buf, size_t len) {

};

int main() {
    float* test;
    dsp::Taps<float> taps;

    testFunc(((const dsp::Taps<float>&)taps).data(), taps.size());

    return 0;
}