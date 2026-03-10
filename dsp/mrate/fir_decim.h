#pragma once
#include "../processor.h"
#include "../buffer.h"
#include "../taps.h"

namespace dsp::mrate {
    template <class SAMPLE, class TAP>
    class FIRDecim {
    public:
        // Default constructor
        FIRDecim();

        /**
         * Create a decimating FIR filter.
         * @param taps Taps to use for the filter.
         * @param decim Decimation factor.
        */
        FIRDecim(const Taps<TAP>& taps, int decim);

        /**
         * Create a decimating FIR filter.
         * @param taps Taps to use for the filter.
         * @param decim Decimation factor.
        */
        FIRDecim(Taps<TAP>&& taps, int decim);

        /**
         * Get the filter taps.
         * @return Filter taps.
        */
        const Taps<TAP>& getTaps() const;

        /**
         * Set the filter taps.
         * @param taps Filter taps.
         * @param decim Decimation factor. Zero to keep unchanged.
        */
        void setTaps(const Taps<TAP>& taps, int decim = 0);

        /**
         * Set the filter taps.
         * @param taps Filter taps.
         * @param decim Decimation factor. Zero to keep unchanged.
        */
        void setTaps(Taps<TAP>&& taps, int decim = 0);

        /**
         * Get the decimation factor.
         * @return Decimation factor.
        */
        int getDecimation();

        /**
         * Set the decimation factor.
         * @param decim Decimation factor.
        */
        void setDecimation(int decim);

        /**
         * Reset the state of the filter.
        */
        void reset();

        /**
         * Filter and decimate samples.
         * @param in Input samples.
         * @param out Output samples.
         * @param count Number of samples to filter.
         * @return Number of samples generates.
        */
        size_t process(const SAMPLE* in, SAMPLE* out, size_t count);

    private:
        Buffer<SAMPLE> hist;
        uintptr_t offset = 0;
        Taps<TAP> taps;
        int decim = 0;
    };
}