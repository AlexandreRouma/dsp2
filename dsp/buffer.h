#pragma once
#include <stddef.h>

namespace dsp {
    /**
     * Re-allocation behavior of buffers.
    */
    enum ReallocBehavior {
        // Discard the exiting content of the buffer.
        REALLOC_DISCARD         = 0,

        // Keep the existing content of the buffer.
        REALLOC_KEEP            = (1 << 0),

        // Zero out the buffer after reallocation.
        REALLOC_ZERO            = (1 << 1),

        // Keep the existing content and zero out the excess new samples.
        REALLOC_KEEP_AND_ZERO   = (REALLOC_KEEP | REALLOC_ZERO)
    };

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
         * Create a buffer from an array of samples.
         * @param samples Array containing the samples.
         * @param size Number of samples to load.
        */
        Buffer(const T* samples, size_t size);

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
         * @param behavior Specify the reallocaition behavior to either discard exiting samples, keep existing samples or zero out the buffer.
        */
        void realloc(size_t size, ReallocBehavior behavior = REALLOC_DISCARD);

        /**
         * Ensure the buffer is big enough to contain a certain number of samples without being too big. Only reallocates when necessary.
         * @param size Number of samples that the buffer must be able to hold.
         * @param behavior Specify the reallocaition behavior to either discard exiting samples, keep existing samples or zero out the buffer.
        */
        inline void reserve(size_t size, ReallocBehavior behavior = REALLOC_DISCARD) {
            if (size > capacity || size < (capacity >> 1)) { realloc(size, behavior); }
        }

        /**
         * Free the buffer. The buffer can still be reallocated afterwards if desired.
        */
        void free();

        /**
         * Get the number of samples in the buffer.
        */
        inline size_t size() const { return capacity; }

        /**
         * Get a pointer to the samples.
        */
        inline T* data() { return buffer; }

        /**
         * Get a const pointer to the samples.
        */
        inline const T* data() const { return buffer; }

        /**
         * Cast to bool.
         * @return True if the buffer contains samples, false if it is empty.
        */
        inline operator bool() const { return capacity; }

        /**
         * Access a sample by index.
         * @param index Index of the tap
         * @return Tap at index.
        */
        inline T& operator[](int index) { return buffer[index]; }

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