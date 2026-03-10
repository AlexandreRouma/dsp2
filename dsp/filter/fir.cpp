#include "fir.h"
#include "../complex.h"
#include <volk/volk.h>

namespace dsp::filter {
    template <class SAMPLE, class TAP>
    FIR<SAMPLE, TAP>::FIR() {}

    template <class SAMPLE, class TAP>
    FIR<SAMPLE, TAP>::FIR(const Taps<TAP>& taps) {
        // Save the taps
        this->taps = taps;

        // Pre-allocate the history buffer
        hist.reserve(taps.size());

        // Initialize the state
        reset();
    }

    template <class SAMPLE, class TAP>
    FIR<SAMPLE, TAP>::FIR(Taps<TAP>&& taps) {
        // Save the taps
        this->taps = taps;

        // Pre-allocate the history buffer
        hist.reserve(taps.size());

        // Initialize the state
        reset();
    }

    template <class SAMPLE, class TAP>
    const Taps<TAP>& FIR<SAMPLE, TAP>::getTaps() const {
        // Return the taps
        return taps;
    }

    template <class SAMPLE, class TAP>
    void FIR<SAMPLE, TAP>::setTaps(const Taps<TAP>& taps) {
        // Update the taps
        this->taps = taps;
    }

    template <class SAMPLE, class TAP>
    void FIR<SAMPLE, TAP>::setTaps(Taps<TAP>&& taps) {
        // Update the taps
        this->taps = taps;
    }

    template <class SAMPLE, class TAP>
    void FIR<SAMPLE, TAP>::reset() {
        // Zero out the history buffer
        memset(hist.data(), 0, (taps.size() - 1) * sizeof(SAMPLE));
    }

    template <class SAMPLE, class TAP>
    size_t FIR<SAMPLE, TAP>::process(const SAMPLE* in, SAMPLE* out, size_t count) {
        // Reserve enough space in the history buffer
        hist.reserve(taps.size() + count - 1, REALLOC_KEEP);

        // Copy over the new input samples
        memcpy(&hist[taps.size() - 1], in, count * sizeof(SAMPLE));

        // Filter the samples
        for (uintptr_t i = 0; i < count; i++) {
            // Compute the dot product depending on type
            if constexpr (std::is_same_v<SAMPLE, float>) {
                volk_32f_x2_dot_prod_32f(&out[i], &hist[i], taps.data(), taps.size());
            }
            else if constexpr (std::is_same_v<SAMPLE, Complex> && std::is_same_v<TAP, float>) {
                volk_32fc_32f_dot_prod_32fc((lv_32fc_t*)&out[i], (const lv_32fc_t*)&hist[i], taps.data(), taps.size());
            }
            else if constexpr (std::is_same_v<SAMPLE, Complex> && std::is_same_v<TAP, Complex>) {
                volk_32fc_x2_dot_prod_32fc((lv_32fc_t*)&out[i], (const lv_32fc_t*)&hist[i], (const lv_32fc_t*)taps.data(), taps.size());
            }
        }

        // Move over the unused sample to the history buffer
        memmove(hist.data(), &hist[count], (taps.size() - 1) * sizeof(SAMPLE));

        // Return the number of samples processed
        return count;
    }

    template class FIR<float, float>;
    template class FIR<Complex, float>;
    template class FIR<Complex, Complex>;
}