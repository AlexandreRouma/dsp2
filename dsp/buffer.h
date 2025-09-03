#pragma once
#include <stddef.h>

namespace dsp {
    /**
     * Sample buffer aligned for efficient DSP use.
     * This class is NOT thread-safe.
    */
    template <class T>
    class Buffer {
    public:
        // Default constructor
        Buffer();
        
        /**
         * Create a sample buffer of a given capacity.
         * @param size Number of samples.
         * @param zero Zero out the buffer.
        */
        Buffer(size_t size, bool zero = false);

        /**
         * Create a buffer from an array.
         * @param taps Array containing the samples.
         * @param count Number of samples to load.
        */
        Buffer(T* taps, int count);

        // Copy constructor
        Buffer(const Buffer<T>& b);

        // Move constructor
        Buffer(Buffer<T>&& b);

        // Destructor
        virtual ~Buffer();

        // Copy assignment operator
        Buffer<T>& operator=(const Buffer<T>& b);

        // Move assignment operator
        Buffer<T>& operator=(Buffer<T>&& b);

        /**
         * Re-allocate the buffer conserving the existing data.
         * @param size Number of samples.
         * @param zero Zero out additional samples.
        */
        void realloc(size_t size, bool zero = false);

        /**
         * Free the buffer.
        */
        void free();

        /**
         * Get the number of samples in the buffer.
        */
        inline int size() const { return capacity; }

        /**
         * Get a pointer to the samples.
        */
        inline const T* data() const { return buffer; }

        /**
         * Cast to bool.
         * @return True if the buffer contains samples, false if it is empty.
        */
        inline operator bool() const { return capacity; }

        /**
         * Get a sample by index.
         * @param index Index of the tap
         * @return Tap at index.
        */
        inline const T& operator[](int index) const { return buffer[index]; }

    private:
        size_t capacity = 0;
        T* buffer = NULL;
    };
}