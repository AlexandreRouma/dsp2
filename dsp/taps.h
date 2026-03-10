#pragma once
#include "buffer.h"

namespace dsp {
    // TODO: Force inline the data stuff for maximal performance in FIR

    /**
     * Filter tap container.
     * This class is NOT thread-safe.
    */
    template <class T>
    class Taps {
    public:
        // Default constructor
        Taps();

        /**
         * Create a taps object from an array of taps.
         * @param taps Array containing the taps.
         * @param count Number of taps to load.
        */
        Taps(const T* taps, size_t count);

        // Copy constructor
        Taps(const Taps<T>& b);

        // Move constructor
        Taps(Taps<T>&& b);

        // Copy assignment operator
        Taps<T>& operator=(const Taps<T>& b);

        // Move assignment operator
        Taps<T>& operator=(Taps<T>&& b);

        /**
         * Get the number of taps.
         * @return Number of taps.
        */
        inline size_t size() { return _size; }

        /**
         * Get a pointer to the taps.
        */
        inline T* data() { return buffer.data(); }

        /**
         * Get a const pointer to the taps.
        */
        inline const T* data() const { return buffer.data(); }

        // TODO: Operations to combine, window, etc taps efficiently

        /**
         * Cast to bool.
         * @return True if there are more than zero taps, false otherwise.
        */
        inline operator bool() const { return _size; }

        /**
         * Access a sample by index.
         * @param index Index of the tap.
         * @return Tap at index.
        */
        inline T& operator[](uintptr_t index) { return buffer[index]; }

        /**
         * Get a sample by index.
         * @param index Index of the tap.
         * @return Tap at index.
        */
        inline const T& operator[](uintptr_t index) const { return buffer[index]; }

    protected:
        Buffer<T> buffer;
        size_t _size = 0;
    };
}