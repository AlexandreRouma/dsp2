#include "wgn.h"
#include <type_traits>
#include <stdlib.h>
#include <volk/volk.h>
#include "../constants.h"
#include "../complex.h"

namespace dsp::source {
    template <class T>
    WGN<T>::WGN() {}

    template <class T>
    WGN<T>::WGN(float amplitude, T offset) {
        // Save the parameters
        this->amplitude = amplitude;
        this->offset = offset;
    }

    template <class T>
    float WGN<T>::getAmplitude() {
        // Return the amplitude
        return amplitude;
    }

    template <class T>
    void WGN<T>::setAmplitude(float amplitude) {
        // Update the amplitude
        this->amplitude = amplitude;
    }

    template <class T>
    T WGN<T>::getOffset() {
        // Return the offset
        return offset;
    }

    template <class T>
    void WGN<T>::setOffset(T offset) {
        // Update the offset
        this->offset = offset;
    }

    template <class T>
    size_t WGN<T>::source(T* out, size_t count) {
        // Choose algo depending on sample rate
        if constexpr (std::is_same_v<T, float>) {
            // Generate samples with a variance of 1
            for (uintptr_t i = 0; i < count; i++) {
                // Generate two uniforn random numbers
                const double u1 = (double)rand() / (double)RAND_MAX;
                const double u2 = (double)rand() / (double)RAND_MAX;

                // Generate a normally distributed number from them
                const double z = sqrt(-2 * log(u1)) * cos(2.0 * DSP_PI * u2);

                // Save it
                out[i] = (float)z;
            }

            // Apply the scaling if necessary
            if (amplitude != 1.0f) { volk_32f_s32f_multiply_32f(out, out, amplitude, count); }

            // Apply the offset if necessary
            if (offset != 0.0f) { volk_32f_s32f_add_32f(out, out, offset, count); }
        }
        else if constexpr (std::is_same_v<T, Complex>) {
            // Generate samples with a variance of 1
            for (uintptr_t i = 0; i < count; i++) {
                // Generate two uniforn random numbers
                const double u1 = (double)rand() / (double)RAND_MAX;
                const double u2 = (double)rand() / (double)RAND_MAX;

                // Generate two normally distributed number from them
                const double sqr = sqrt(-2 * log(u1));
                const double phi = 2.0 * DSP_PI * u2;
                const double z1 = sqr * cos(phi);
                const double z2 = sqr * sin(phi);

                // Save it
                out[i].re = z1;
                out[i].im = z2;
            }

            // Apply the scaling if necessary
            if (amplitude != 1.0f) { volk_32fc_s32fc_multiply_32fc((lv_32fc_t*)out, (const lv_32fc_t*)out, amplitude, count); }

            // Apply the offset if necessary
            if (offset != 0.0f) {
                // Apply the offset without volk since that kernel is not available
                for (uintptr_t i = 0; i < count; i++) {
                    out[i] += offset;
                }
            }
        }

        // Return the sample count
        return count;
    }

    // Instantiate the class
    template class WGN<float>;
    template class WGN<Complex>;
}