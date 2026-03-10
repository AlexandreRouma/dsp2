#pragma once
#include "../processor.h"
#include "../buffer.h"
#include "../taps.h"
#include <vector>

namespace dsp::mrate {
    template <class SAMPLE, class TAP>
    class FIRInterp {
    public:
        // Default constructor
        FIRInterp();

        /**
         * Create a decimating FIR filter.
         * @param taps Taps to use for the filter.
         * @param interp Interpolation factor.
        */
        FIRInterp(const Taps<TAP>& taps, int interp);

        /**
         * Create a decimating FIR filter.
         * @param taps Taps to use for the filter.
         * @param interp Interpolation factor.
        */
        FIRInterp(Taps<TAP>&& taps, int interp);

        /**
         * Get the filter taps.
         * @return Filter taps.
        */
        const Taps<TAP>& getTaps() const;

        /**
         * Set the filter taps.
         * @param taps Filter taps.
         * @param interp Interpolation factor. Zero to keep unchanged.
        */
        void setTaps(const Taps<TAP>& taps, int interp = 0);

        /**
         * Set the filter taps.
         * @param taps Filter taps.
         * @param interp Interpolation factor. Zero to keep unchanged.
        */
        void setTaps(Taps<TAP>&& taps, int interp = 0);

        /**
         * Get the interpolation factor.
         * @return Interpolation factor.
        */
        int getInterpolation();

        /**
         * Set the interpolation factor.
         * @param interp Interpolation factor.
        */
        void setInterpolation(int interp);

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
        void generatePhases();

        Buffer<SAMPLE> hist;
        uintptr_t offset = 0;
        Taps<TAP> taps;
        std::vector<Buffer<TAP>> phases;
        int interp = 0;
    };
}