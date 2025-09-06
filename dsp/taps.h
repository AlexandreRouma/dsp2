#pragma once
#include "buffer.h"

namespace dsp {
    /**
     * Filter tap container.
     * This class is NOT thread-safe.
    */
    template <class T>
    class Taps : public Buffer<T> {
    public:
        // Default constructor
        Taps();

        /**
         * Create a taps object from an array of taps.
         * @param taps Array containing the taps.
         * @param count Number of taps to load.
        */
        Taps(const T* taps, size_t count);

        // TODO: Operations to combine, window, etc taps efficiently

    protected:
        using Buffer<T>::realloc;

    private:
        using Buffer<T>::reserve;
    };
}