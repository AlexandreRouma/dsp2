#include <stdio.h>
#include <exception>
#include <string.h>
#include <atomic>
#include <thread>
#include "../dsp/buffer.h"
#include "../dsp/source/wgn.h"
#include "../dsp/demod/fm.h"
#include "../dsp/taps/low_pass.h"
#include "../dsp/mrate/fir_decim.h"
#include "../dsp/sink/file.h"

#define BUFFER_SIZE 1250

int main() {
    try {
        dsp::source::WGN<dsp::Complex> wgn(1.0f);
        dsp::demod::FM fmd(6125, 240e3);
        dsp::mrate::FIRDecim<float, float> decim(dsp::taps::LowPass(20e3, 4e3, 240e3), 5);
        dsp::sink::File<float> file("output.f32");

        dsp::Buffer<dsp::Complex> cbuf(BUFFER_SIZE);
        dsp::Buffer<float> rbuf(BUFFER_SIZE);

        wgn.source(cbuf, BUFFER_SIZE);
        fmd.process(cbuf, rbuf, BUFFER_SIZE);
        size_t ocount = decim.process(rbuf, rbuf, BUFFER_SIZE);
        file.sink(rbuf, ocount);

        return 0;
    }
    catch (const std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return -1;
    }
}