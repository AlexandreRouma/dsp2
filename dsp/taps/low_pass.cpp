#include "low_pass.h"

namespace dsp::taps {
    LowPass::LowPass() {}

    LowPass::LowPass(float cutoff, float transWidth, float samplerate) {
        // Save parameters
        this->cutoff = cutoff;
        this->transWidth = transWidth;
        this->samplerate = samplerate;

        // Generate filter
        generate();
    }

    float LowPass::getCutoff() {
        return cutoff;
    }

    void LowPass::setCutoff(float cutoff, float transWidth) {
        // Update parameter
        this->cutoff = cutoff;

        // If the transition width is given, update is as well
        if (transWidth > 0) { this->transWidth = transWidth; }

        // Regenerate filter
        generate();
    }

    float LowPass::getTransWidth() {
        return transWidth;
    }

    void LowPass::setTransWidth(float transWidth) {
        // Update parameter
        this->transWidth = transWidth;

        // Regenerate filter
        generate();
    }

    float LowPass::getSamplerate() {
        return samplerate;
    }

    void LowPass::setSamplerate(float samplerate) {
        // Update parameter
        this->samplerate = samplerate;

        // Regenerate filter
        generate();
    }

    void LowPass::generate() {
        // Reallocate the buffer
        realloc(0 /*TODO: Tap count estimation*/);

        // Generate taps
        // TODO
    }
}