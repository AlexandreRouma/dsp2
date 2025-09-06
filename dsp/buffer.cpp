#include "buffer.h"
#include "complex.h"
#include <volk/volk.h>
#include <stdint.h>

namespace dsp {
    template <class T>
    Buffer<T>::Buffer() {}

    template <class T>
    Buffer<T>::Buffer(size_t size, bool zero) {
        // Allocate buffer
        realloc(size, zero ? REALLOC_ZERO : REALLOC_DISCARD);
    }

    template <class T>
    Buffer<T>::Buffer(const T* samples, size_t size) {
        // Allocate buffer
        realloc(size);

        // Copy data over
        memcpy(buffer, samples, size * sizeof(T));
    }

    template <class T>
    Buffer<T>::Buffer(const Buffer<T>& b) {
        // Allocate buffer
        realloc(b.count);

        // Copy data over
        memcpy(buffer, b.buffer, b.count * sizeof(T));
    }

    template <class T>
    Buffer<T>::Buffer(Buffer<T>&& b) {
        // Copy members
        buffer = b.buffer;
        capacity = b.capacity;

        // Neutralize old instance
        b.buffer = NULL;
        b.capacity = 0;
    }

    template <class T>
    Buffer<T>::~Buffer() {
        // Free the buffer
        free();
    }

    template <class T>
    Buffer<T>& Buffer<T>::operator=(const Buffer<T>& b) {
        // Reallocate the buffer
        realloc(b.capacity);

        // Copy over the data
        memcpy(buffer, b.buffer, capacity * sizeof(T));
    }

    template <class T>
    Buffer<T>& Buffer<T>::operator=(Buffer<T>&& b) {
        // Free the current buffer
        free();

        // Copy the state of the original
        buffer = b.buffer;
        capacity = b.capacity;

        // Neutralize the original
        b.buffer = NULL;
        b.capacity = 0;
    }

    template <class T>
    void Buffer<T>::realloc(size_t size, ReallocBehavior behavior) {
        // Select the desired behavior
        switch (behavior) {
        case REALLOC_DISCARD:
            // Free the current buffer
            volk_free(buffer);

            // Allocate a new buffer
            buffer = volk_malloc(size * sizeof(T));
            break;
        case REALLOC_KEEP:
            // Allocate a new buffer
            T* newbuf = volk_malloc(size * sizeof(T));

            // Copy the existing data
            memcpy(newbuf, buffer, std::min<size_t>(capacity, size));

            // Replace buffer
            buffer = newbuf;
            break;
        case REALLOC_ZERO:
            // Free the current buffer
            volk_free(buffer);

            // Allocate a new buffer
            buffer = volk_malloc(size * sizeof(T));

            // Zero-out the new buffer
            memset(buffer, 0, size);
            break;
        case REALLOC_KEEP_AND_ZERO:

        }

        // Update the current capacity
        capacity = size;
    }

    template <class T>
    void Buffer<T>::free() {
        // Free the buffer
        volk_free(buffer);

        // Mark the buffer as freed
        buffer = NULL;
        capacity = 0;
    }

    // Instantiate the class
    template class Buffer<uint8_t>;
    template class Buffer<uint16_t>;
    template class Buffer<uint32_t>;
    template class Buffer<uint64_t>;
    template class Buffer<int8_t>;
    template class Buffer<int16_t>;
    template class Buffer<int32_t>;
    template class Buffer<int64_t>;
    template class Buffer<float>;
    template class Buffer<double>;
    template class Buffer<Complex>;
}