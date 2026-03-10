#include "fir_decim.h"
#include "../complex.h"
#include <string.h>
#include <volk/volk.h>

namespace dsp::mrate {
    template <class SAMPLE, class TAP>
    FIRDecim<SAMPLE, TAP>::FIRDecim() {}

    template <class SAMPLE, class TAP>
    FIRDecim<SAMPLE, TAP>::FIRDecim(const Taps<TAP>& taps, int decim) {
        // Save the parameters
        this->taps = taps;
        this->decim = decim;

        // Pre-allocate the history buffer
        hist.reserve(taps.size());

        // Initialize the state
        reset();
    }

    template <class SAMPLE, class TAP>
    FIRDecim<SAMPLE, TAP>::FIRDecim(Taps<TAP>&& taps, int decim) {
        // Save the parameters
        this->taps = taps;
        this->decim = decim;

        // Pre-allocate the history buffer
        hist.reserve(taps.size());

        // Initialize the state
        reset();
    }

    template <class SAMPLE, class TAP>
    const Taps<TAP>& FIRDecim<SAMPLE, TAP>::getTaps() const {
        // Return the taps
        return taps;
    }

    template <class SAMPLE, class TAP>
    void FIRDecim<SAMPLE, TAP>::setTaps(const Taps<TAP>& taps, int decim) {
        // Update the taps
        this->taps = taps;

        // Update the decimation factor if it was given
        if (decim) { this->decim = decim; }
    }

    template <class SAMPLE, class TAP>
    void FIRDecim<SAMPLE, TAP>::setTaps(Taps<TAP>&& taps, int decim) {
        // Update the taps
        this->taps = taps;
        
        // Update the decimation factor if it was given
        if (decim) { this->decim = decim; }
    }

    template <class SAMPLE, class TAP>
    void FIRDecim<SAMPLE, TAP>::reset() {
        // Zero out the history buffer
        memset(hist.data(), 0, (taps.size() - 1) * sizeof(SAMPLE));

        // Reset the offset
        offset = 0;
    }

    template <class SAMPLE, class TAP>
    size_t FIRDecim<SAMPLE, TAP>::process(const SAMPLE* in, SAMPLE* out, size_t count) {
        // Reserve enough space in the history buffer
        hist.reserve(taps.size() + count - 1, REALLOC_KEEP);

        // Copy over the new input samples
        memcpy(&hist[taps.size() - 1], in, count * sizeof(SAMPLE));

        // Filter the samples
        uintptr_t i;
        uintptr_t io = 0;
        for (i = offset; i < count; i += decim) {
            // Compute the dot product depending on type
            if constexpr (std::is_same_v<SAMPLE, float>) {
                volk_32f_x2_dot_prod_32f(&out[io++], &hist[i], taps.data(), taps.size());
            }
            else if constexpr (std::is_same_v<SAMPLE, Complex> && std::is_same_v<TAP, float>) {
                volk_32fc_32f_dot_prod_32fc((lv_32fc_t*)&out[io++], (const lv_32fc_t*)&hist[i], taps.data(), taps.size());
            }
            else if constexpr (std::is_same_v<SAMPLE, Complex> && std::is_same_v<TAP, Complex>) {
                volk_32fc_x2_dot_prod_32fc((lv_32fc_t*)&out[io++], (const lv_32fc_t*)&hist[i], (const lv_32fc_t*)taps.data(), taps.size());
            }
        }

        // Update the offset
        offset = i - count;

        // Move over the unused sample to the history buffer
        memmove(hist.data(), &hist[count], (taps.size() - 1) * sizeof(SAMPLE));

        // Return the number of samples generated
        return io;
    }

    // Instantiate the class
    template class FIRDecim<float, float>;
    template class FIRDecim<Complex, float>;
    template class FIRDecim<Complex, Complex>;
}