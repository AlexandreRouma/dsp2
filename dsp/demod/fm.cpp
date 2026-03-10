#include "fm.h"
#include "../constants.h"
#include "volk/volk.h"

// TODO: Thread safety

namespace dsp::demod {
    FM::FM() {}

    FM::FM(double deviation, double samplerate) {
        // Save the parameters
        this->deviation = deviation;
        this->samplerate = samplerate;

        // Compute the gain
        gain = samplerate / (2.0 * DSP_PI * deviation);
    }

    double FM::getDeviation() {
        // Return the deviation
        return deviation;
    }

    void FM::setDeviation(double deviation) {
        // Update the deviation
        this->deviation = deviation;

        // Recompute the gain
        gain = samplerate / (2.0 * DSP_PI * deviation);
    }

    double FM::getSamplerate() {
        // Return the sampling rate
        return samplerate;
    }

    void FM::setSamplerate(double deviation) {
        // Update the sampling rate
        this->samplerate = samplerate;

        // Recompute the gain
        gain = samplerate / (2.0 * DSP_PI * deviation);
    }

    void FM::reset() {
        // Reset the last phase
        lastPhase = 0.0f;
    }

    // TODO: Move to a dedicated utils file
    constexpr inline float clampPhase(float diff) {
        if (diff > DSP_PI_FL) { diff -= 2.0f * DSP_PI_FL; }
        else if (diff <= -DSP_PI_FL) { diff += 2.0f * DSP_PI_FL; }
        return diff;
    }

    size_t FM::process(const Complex* in, float* out, size_t count) {
        // Process all samples
        for (uintptr_t i = 0; i < count; i++) {
            // Get the input phase
            const float phase = in[i].phase();

            // Compute the difference with the last sample and update the last phase
            out[i] = clampPhase(phase - lastPhase) * gain;

            // Save the last phase
            lastPhase = phase;
        }

        // Return the number of samples in the output
        return count;
    }
}