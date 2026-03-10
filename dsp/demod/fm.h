#pragma once
#include <stddef.h>
#include "../complex.h"

namespace dsp::demod {
    class FM {
    public:
        // Default constructor
        FM();

        /**
         * Create a FM demodulator.
         * @param deviation Deviation in Hz.
         * @param samplerate Sampling rate in Hz.
        */
        FM(double deviation, double samplerate);

        /**
         * Get the deviation.
         * @return Deviation in Hz.
        */
        double getDeviation();

        /**
         * Set the deviation.
         * @param deviation Deviation in Hz.
        */
        void setDeviation(double deviation);

        /**
         * Get the sampling rate.
         * @return Sampling rate in Hz.
        */
        double getSamplerate();

        /**
         * Set the sampling rate.
         * @param deviation Sampling rate in Hz.
        */
        void setSamplerate(double deviation);

        /**
         * Reset the state of the demodulator.
        */
        void reset();

        /**
         * Demodulate an FM signal.
         * @param in Modulated sample input.
         * @param out Demodulated sample output.
         * @param count Number of samples to process.
         * @return Number of samples processed. Always equal to `count`.
        */
        size_t process(const Complex* in, float* out, size_t count);

    private:
        double deviation = 0.0;
        double samplerate = 0.0;
        float gain = 0.0f;
        float lastPhase = 0.0f;
    };
}