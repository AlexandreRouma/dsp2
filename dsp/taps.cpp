#include "taps.h"
#include "complex.h"
#include <utility>
#include <string.h>

namespace dsp {
    template <class T>
    Taps<T>::Taps() {}

    template <class T>
    Taps<T>::Taps(const T* taps, size_t count) {
        // Intialize the buffer
        buffer = Buffer<T>(taps, count);

        // Set the size
        _size = count;
    }

    template <class T>
    Taps<T>::Taps(const Taps<T>& b) {
        // Reserve enough space in the buffer
        buffer.reserve(b._size);

        // Copy over the taps
        memcpy(buffer.data(), b.buffer.data(), b._size * sizeof(T));

        // Set the size
        _size = b._size;
    }

    template <class T>
    Taps<T>::Taps(Taps<T>&& b) {
        // Move the buffer
        buffer = std::move(b.buffer);

        // Move the size
        _size = b._size;
        b._size = 0;
    }

    template <class T>
    Taps<T>& Taps<T>::operator=(const Taps<T>& b) {
        // Reserve enough space in the buffer
        buffer.reserve(b._size);

        // Copy over the taps
        memcpy(buffer.data(), b.buffer.data(), b._size * sizeof(T));

        // Set the size
        _size = b._size;

        // Return self
        return *this;
    }

    template <class T>
    Taps<T>& Taps<T>::operator=(Taps<T>&& b) {
        // Move the buffer
        buffer = std::move(b.buffer);

        // Move the size
        _size = b._size;
        b._size = 0;

        // Return self
        return *this;
    }

    template class Taps<float>;
    template class Taps<Complex>;
}