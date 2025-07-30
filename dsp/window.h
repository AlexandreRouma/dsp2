#pragma once
#include <stdint.h>

// TODO: Make something better, this sucks to use

namespace dsp {
    class Window {
    public:
        // Virtual destructor
        virtual ~Window();

        /**
         * Compute the value of the window function.
         * @param x Point at which to compute the window at. Must be bounded between 0 and 1.
         * @return Value of the window bounded between 0 and 1.
        */
        virtual float operator()(float x) const = 0;

        /**
         * Generate a window of a given length.
         * @param data Samples buffer to write the window to.
         * @param len Length of the window.
        */
        void generate(float* data, size_t len) const;

        /**
         * Apply the window function to samples.
         * @param data Sample buffer to apply the window to.
         * @param len Length of the sample buffer.
        */
        template <class T>
        void apply(T* data, size_t len) const;
    };
}