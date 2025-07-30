#pragma once
#include "../taps.h"

namespace dsp::taps {
    // TODO: Add option to only use an odd number of taps and an option to query the delay

    /**
     * Low-pass filter taps.
     * This class is NOT thread-safe.
    */
    class LowPass : public Taps<float> {
    public:
        // Default constructor
        LowPass();

        /**
         * Create low-pass FIR taps.
         * @param cutoff 3dB cutoff frequency in Hz.
         * @param transWidth Transition width in Hz.
         * @param samplerate Sample rate in Hz.
        */
        LowPass(float cutoff, float transWidth, float samplerate);

        /**
         * Get cutoff frequency.
        */
        float getCutoff();

        /**
         * Set cutoff frequency.
         * @param cutoff Cutoff frequency in Hz.
         * @param transWidth Transition width in Hz. Negative if unchanged.
        */
        void setCutoff(float cutoff, float transWidth = -1);

        /**
         * Get transition width.
        */
        float getTransWidth();

        /**
         * Set transition width.
         * @param transWidth Transition width in Hz.
        */
        void setTransWidth(float transWidth);

        /**
         * Get sample rate.
        */
        float getSamplerate();

        /**
         * Set sample rate.
         * @param samplerate Sample rate in Hz.
        */
        void setSamplerate(float samplerate);

    private:
        void generate();

        float cutoff = 0.0f;
        float transWidth = 0.0f;
        float samplerate = 0.0f;
    };
}