#include "fir_interp.h"
#include "../complex.h"
#include <string.h>
#include <volk/volk.h>

namespace dsp::mrate {
    template <class SAMPLE, class TAP>
    FIRInterp<SAMPLE, TAP>::FIRInterp() {}

    template <class SAMPLE, class TAP>
    FIRInterp<SAMPLE, TAP>::FIRInterp(const Taps<TAP>& taps, int interp) {
        // Save the parameters
        this->taps = taps;
        this->interp = interp;

        // Pre-allocate the history buffer
        hist.reserve(taps.size());

        // Initialize the state
        reset();

        // Generate the tap phases
        generatePhases();
    }

    template <class SAMPLE, class TAP>
    FIRInterp<SAMPLE, TAP>::FIRInterp(Taps<TAP>&& taps, int interp) {
        // Save the parameters
        this->taps = taps;
        this->interp = interp;

        // Pre-allocate the history buffer
        hist.reserve(taps.size());

        // Initialize the state
        reset();

        // Generate the tap phases
        generatePhases();
    }

    template <class SAMPLE, class TAP>
    const Taps<TAP>& FIRInterp<SAMPLE, TAP>::getTaps() const {
        // Return the taps
        return taps;
    }

    template <class SAMPLE, class TAP>
    void FIRInterp<SAMPLE, TAP>::setTaps(const Taps<TAP>& taps, int interp) {
        // Update the taps
        this->taps = taps;

        // Update the interpolation factor if it was given
        if (interp) { this->interp = interp; }

        // Regenerate the tap phases
        generatePhases();
    }

    template <class SAMPLE, class TAP>
    void FIRInterp<SAMPLE, TAP>::setTaps(Taps<TAP>&& taps, int interp) {
        // Update the taps
        this->taps = taps;
        
        // Update the interpolation factor if it was given
        if (interp) { this->interp = interp; }

        // Regenerate the tap phases
        generatePhases();
    }

    template <class SAMPLE, class TAP>
    void FIRInterp<SAMPLE, TAP>::reset() {
        // Zero out the history buffer
        memset(hist.data(), 0, (taps.size() - 1) * sizeof(SAMPLE));

        // Reset the offset
        offset = 0;
    }

    template <class SAMPLE, class TAP>
    size_t FIRInterp<SAMPLE, TAP>::process(const SAMPLE* in, SAMPLE* out, size_t count) {
        // TODO

        // Return the number of samples generated
        return 0;
    }

    template <class SAMPLE, class TAP>
    void FIRInterp<SAMPLE, TAP>::generatePhases() {
        // TODO
    }

    // Instantiate the class
    template class FIRInterp<float, float>;
    template class FIRInterp<Complex, float>;
    template class FIRInterp<Complex, Complex>;
}