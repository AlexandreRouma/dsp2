#pragma once
#include "../processor.h"
#include "../taps.h"

namespace dsp::filter {
    /**
     * Finite Inpulse Response filter (Synchronous).
     * This class is thread-safe except for `process()`.
    */
    template <class SAMP_T, class TAPS_T>
    class FIR_s : public ProcessorSync<SAMP_T, SAMP_T> {
    public:
        /**
         * Create a FIR filter.
         * @param taps Filter taps.
        */
        FIR_s(const Taps<TAPS_T>& taps);

        /**
         * Get the filter taps.
         * @return Filter taps.
        */
        Taps<TAPS_T> getTaps();

        /**
         * Set the filter taps.
         * @param taps Filter taps.
        */
        void setTaps(const Taps<TAPS_T>& taps);

        /**
         * Reset the state of the filter.
        */
        void reset();

        /**
         * Filter samples.
         * @param in Input sample buffer.
         * @param out Filtered sample buffer.
         * @param count Number of samples in the input buffer.
         * @return Number of samples in the output buffer. Will always be equal to the number of samples in the input buffer.
        */
        int process(const SAMP_T* in, SAMP_T* out, int count);

    private:
        Taps<TAPS_T> taps;
    };

    /**
     * Finite Inpulse Response filter.
     * This class is thread-safe except for `process()`.
    */
    template <class SAMP_T, class TAPS_T>
    class FIR : public FIR_s<SAMP_T, TAPS_T>, public ProcessorAsync<SAMP_T, SAMP_T> {
    public:
        /**
         * Create a FIR filter.
         * @param taps Filter taps.
        */
        FIR(const Taps<TAPS_T>& taps);

        /**
         * Create a FIR filter.
         * @param in Input samples.
         * @param taps Filter taps.
        */
        FIR(Stream<SAMP_T>* in, const Taps<TAPS_T>& taps);

        /**
         * Create a FIR filter.
         * @param in Input samples.
         * @param in Filtered samples.
         * @param taps Filter taps.
        */
        FIR(Stream<SAMP_T>* in, Stream<SAMP_T>* out, const Taps<TAPS_T>& taps);
    };
}