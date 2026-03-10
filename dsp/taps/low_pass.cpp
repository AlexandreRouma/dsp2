#include "low_pass.h"

namespace dsp::taps {
    LowPass::LowPass() {}

    LowPass::LowPass(double cutoff, double transWidth, double samplerate, double gain, bool forceOdd) {
        // Save parameters
        this->cutoff = cutoff;
        this->transWidth = transWidth;
        this->samplerate = samplerate;
        this->gain = gain;
        this->forceOdd = forceOdd;

        // Generate the filter
        generate();
    }

    double LowPass::getCutoff() {
        // Return the cutoff
        return cutoff;
    }

    void LowPass::setCutoff(double cutoff, double transWidth) {
        // Update the cutoff
        this->cutoff = cutoff;

        // If the transition width is given, update is as well
        if (!isnan(transWidth)) { this->transWidth = transWidth; }

        // Re-generate the filter
        generate();
    }

    double LowPass::getTransWidth() {
        // Return the transition width
        return transWidth;
    }

    void LowPass::setTransWidth(double transWidth) {
        // Update the transition width
        this->transWidth = transWidth;

        // Re-generate the filter
        generate();
    }

    double LowPass::getSamplerate() {
        // Return the sampling rate
        return samplerate;
    }

    void LowPass::setSamplerate(double samplerate) {
        // Update sampling rate
        this->samplerate = samplerate;

        // Re-generate filter
        generate();
    }

    double LowPass::getGain() {
        // Return the gain
        return gain;
    }

    void LowPass::setGain(double gain) {
        // Update the gain
        this->gain = gain;

        // Re-generate the filter
        generate();
    }

    double LowPass::getForceOdd() {
        // Return force odd
        return forceOdd;
    }

    void LowPass::setForceOdd(bool forceOdd) {
        // Update force odd
        this->forceOdd = forceOdd;

        // Re-generate the filter
        generate();
    }

    void LowPass::generate() {
        // Estimate the number of required taps


        // Reserve enough space in the buffer
        // TODO

        // Generate taps
        // TODO
    }
}