#pragma once
#include "../taps.h"

namespace dsp::taps {
    /**
     * Low-pass filter taps.
    */
    class LowPass : public Taps<float> {
    public:
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

        float cutoff;
        float transWidth;
        float samplerate;
    };
}