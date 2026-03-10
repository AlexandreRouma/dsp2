#pragma once
#include "../taps.h"
#include <math.h>

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
         * @param gain Passband amplitude gain.
         * @param forceOdd Ensures the filter has an odd number of taps. Useful to guarantee an integer delay.
        */
        LowPass(double cutoff, double transWidth, double samplerate, double gain = 1.0, bool forceOdd = false);

        /**
         * Get the cutoff frequency.
         * @return Cutoff frequency in Hz.
        */
        double getCutoff();

        /**
         * Set the cutoff frequency.
         * @param cutoff Cutoff frequency in Hz.
         * @param transWidth Transition width in Hz. NAN if unchanged.
        */
        void setCutoff(double cutoff, double transWidth = NAN);

        /**
         * Get the transition width.
         * @return Transition width in Hz.
        */
        double getTransWidth();

        /**
         * Set the transition width.
         * @param transWidth Transition width in Hz.
        */
        void setTransWidth(double transWidth);

        /**
         * Get the sampling rate.
         * @return Sampling rate in Hz.
        */
        double getSamplerate();

        /**
         * Set the sampling rate.
         * @param samplerate Sample rate in Hz.
        */
        void setSamplerate(double samplerate);

        /**
         * Get the passband amplitude gain.
         * @return Passband amplitude gain in linear scale.
        */
        double getGain();

        /**
         * Set the passband amplitude gain.
         * @param gain Passband gain in linear scale.
        */
        void setGain(double gain);

        /**
         * Get whether the filter is forced to an odd length. Useful to guarantee an integer delay.
         * @return True if the length if forced to be odd, False otherwise.
        */
        double getForceOdd();

        /**
         * Set whether the filter is forced to an odd length. Useful to guarantee an integer delay.
         * @param forceOdd True to force the length to be odd, False otherwise.
        */
        void setForceOdd(bool forceOdd);

    private:
        void generate();

        double cutoff = 0.0;
        double transWidth = 0.0;
        double samplerate = 0.0;
        double gain = 0.0;
        bool forceOdd = false;
    };
}