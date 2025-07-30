#pragma once
#include "../processor.h"
#include "../complex.h"

namespace dsp::demod {
    /**
     * FM demodulator (Synchronous).
     * This class is thread-safe except for `process()`.
    */
    class FM_s : public ProcessorSync<Complex, float> {
    public:
        // Default constructor
        FM_s();

        /**
         * Create an FM demodulator.
         * @param deviation Deviation of the FM signal in Hz.
         * @param samplerate Samplerate of the signal in Hz.
        */
        FM_s(float deviation, float samplerate);

        /**
         * Get the deviation.
         * @return Deviation of the FM signal in Hz.
        */
        float getDeviation() const;

        /**
         * Set the deviation.
         * @param deviation Deviation of the FM signal in Hz.
        */
        void setDeviation(float deviation);

        /**
         * Get the samplerate.
         * @return Samplerate of the signal in Hz.
        */
       float getSamplerate() const;

        /**
         * Set the samplerate.
         * @param deviation Samplerate of the signal in Hz.
        */
        void setSamplerate(float samplerate);

        /**
         * Reset the state of the demodulator.
        */
        void reset();

        /**
         * Demodulate a FM-modulated signal. A lock must be acquired using `getLock()` prior to invoking if settings could be set from another thread.
         * @param in Modulated signal buffer.
         * @param out Demodulated signal buffer.
         * @param count Number of samples in the input buffer.
         * @return Number of samples in the output buffer. Will always be equal to the number of samples in the input buffer.
        */
        int process(const Complex* in, float* out, int count);

    private:
        float deviation = 0.0f;
        float samplerate = 0.0f;
        float normFact = 1.0f;
        float phase = 0.0f;
    };

    /**
     * FM demodulator.
     * This class is thread-safe.
    */
    class FM : public FM_s, public ProcessorAsync<Complex, float> {
    public:
        // Default constructor
        FM();

        /**
         * Create an FM demodulator.
         * @param deviation Deviation of the FM signal in Hz.
         * @param samplerate Samplerate of the signal in Hz.
        */
        FM(float deviation, float samplerate);

        /**
         * Create an FM demodulator.
         * @param in Modulated signal stream.
         * @param deviation Deviation of the FM signal in Hz.
         * @param samplerate Samplerate of the signal in Hz.
        */
        FM(Stream<Complex>* in, float deviation, float samplerate);

        /**
         * Create an FM demodulator.
         * @param in Modulated signal stream.
         * @param out Demodulated signal stream.
         * @param deviation Deviation of the FM signal in Hz.
         * @param samplerate Samplerate of the signal in Hz.
        */
        FM(Stream<Complex>* in, Stream<float>* out, float deviation, float samplerate);
    };
}