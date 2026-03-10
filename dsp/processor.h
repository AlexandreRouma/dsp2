#pragma once
#include <stdint.h>
#include <mutex>

namespace dsp {
    template <class T_IN, class T_OUT>
    class SISOProcessor {
    public:
        inline SISOProcessor() {}

        inline SISOProcessor(SISOProcessor&& b) {}

        virtual size_t process(const T_IN* in, T_OUT* out, size_t count) = 0;

        inline size_t processSafe(const T_IN* in, T_OUT* out, size_t count) {
            // Acquire the mutex
            std::lock_guard<std::mutex> lck(mtx);

            // Process the samples
            return process(in, out, count);
        }

        /**
         * Give the required output buffer size for a given input buffer size.
         * @return Required output buffer size for a given input buffer size.
        */
        virtual inline size_t outputBufferSize(size_t inputBufferSize) { return inputBufferSize; }

    protected:
        /**
         * Block mutex. Must be acquired when modifying parameters.
        */
        std::mutex mtx;
    };
}