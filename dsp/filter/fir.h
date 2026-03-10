#pragma once
#include "../processor.h"
#include "../buffer.h"
#include "../taps.h"

namespace dsp::filter {
    template <class SAMPLE, class TAP>
    class FIR : public SISOProcessor<SAMPLE, SAMPLE> {
    public:
        // Default constructor
        FIR();

        /**
         * Create a FIR filter.
         * @param taps Taps to use for the filter.
        */
        FIR(const Taps<TAP>& taps);

        /**
         * Create a FIR filter.
         * @param taps Taps to use for the filter.
        */
        FIR(Taps<TAP>&& taps);

        /**
         * Get the filter taps.
         * @return Filter taps.
        */
        const Taps<TAP>& getTaps() const;

        /**
         * Set the filter taps.
         * @param taps Filter taps.
        */
        void setTaps(const Taps<TAP>& taps);

        /**
         * Set the filter taps.
         * @param taps Filter taps.
        */
        void setTaps(Taps<TAP>&& taps);

        /**
         * Reset the state of the filter.
        */
        void reset();

        /**
         * Filter samples.
         * @param in Input samples.
         * @param out Output samples.
         * @param count Number of samples to filter.
         * @return Number of samples fitlered. Always equal to `count`.
        */
        size_t process(const SAMPLE* in, SAMPLE* out, size_t count);

    private:
        Buffer<SAMPLE> hist;
        Taps<TAP> taps;
    };
}