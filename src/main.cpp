#include <stdio.h>
#include <exception>
#include "dsp/buffer.h"
#include "dsp/demod/fm.h"
#include "dsp/sink/file.h"
#include <atomic>
#include <thread>

#include "dsp/source/wgn.h"

#define BUFFER_SIZE 1250

void sendWorker(dsp::Stream<dsp::Complex>* input) {
    // Generate a buffer of random data
    dsp::source::WGN<dsp::Complex> wgn(1.0);
    dsp::Buffer<dsp::Complex> randShit(BUFFER_SIZE);
    wgn.source(randShit.data(), BUFFER_SIZE);
    
    while (true) {
        // Get a buffer for sending
        auto bset = input->reserve(BUFFER_SIZE);

        // Copy over the samples
        memcpy(bset.buffer[0], randShit.data(), BUFFER_SIZE * sizeof(dsp::Complex));

        // Send the samples
        if (!input->send(BUFFER_SIZE)) { break; }
    }
}

std::atomic_uint64_t counter;
void receiveWorker(dsp::Stream<float>* output) {
    while (true) {
        // Receive a buffer
        auto bset = output->recv();
        if (!bset.samples) { break; }

        // Add to the counter
        counter += bset.samples;

        // Flush the buffer
        output->flush();
    }
}

int main() {
    try {
        // Define the DSP
        dsp::demod::FMw fmw = dsp::demod::FM(6125, 50e3);

        // Start the send worker
        std::thread sendThread(sendWorker, fmw.in());
        std::thread receiveThread(receiveWorker, fmw.out());

        // Start the FM demod
        fmw.start();

        // Start receiving
        while (true) {
            // Get the number of samples processed
            size_t proc = counter.exchange(0);

            // Print
            printf("%lf MS/s\n", (double)proc / 1e6);

            // Wait
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        return 0;
    }
    catch (const std::exception& e) {
        fprintf(stderr, "ERROR: %s\n", e.what());
        return -1;
    }
}