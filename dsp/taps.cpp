#include "taps.h"
#include "complex.h"
#include <string.h>

namespace dsp {
    template <class T>
    Taps<T>::Taps() {}

    template <class T>
    Taps<T>::Taps(int count, bool zero) {
        // Allocate buffer
        reallocate(count);

        // Null out if requested
        if (zero) { memset(buffer, 0, count*sizeof(T)); }
    }

    template <class T>
    Taps<T>::Taps(T* taps, int count) {
        // Allocate buffer
        reallocate(count);

        // Copy data over
        memcpy(buffer, taps, count*sizeof(T));
    }

    template <class T>
    Taps<T>::Taps(const Taps<T>& b) {
        // Allocate buffer
        reallocate(b.count);

        // Copy data over
        memcpy(buffer, b.buffer, b.count*sizeof(T));
    }

    template <class T>
    Taps<T>::Taps(Taps<T>&& b) {
        // Copy members
        buffer = b.buffer;
        count = b.count;

        // Neutralize old instance
        b.buffer = NULL;
        b.count = 0;
    }

    template <class T>
    Taps<T>::~Taps() {
        // Free the buffer if it is allocated
        if (buffer) { delete[] buffer; }
    }

    template <class T>
    Taps<T>& Taps<T>::operator=(const Taps<T>& b) {
        // Reallocate buffer
        reallocate(b.count);

        // Copy data over
        memcpy(buffer, b.buffer, b.count*sizeof(T));

        // Return self
        return *this;
    }

    template <class T>
    Taps<T>& Taps<T>::operator=(Taps<T>&& b) {
        // Destroy current instance
        if (buffer) { delete[] buffer; }

        // Copy members
        buffer = b.buffer;
        count = b.count;

        // Neutralize old instance
        b.buffer = NULL;
        b.count = 0;

        // Return self
        return *this;
    }

    template <class T>
    void Taps<T>::reallocate(int count) {
        // If the new count is no different and the buffer is allocated, no need to realloc
        if (buffer && this->count == count) { return; }

        // Free buffer
        if (buffer) { delete[] buffer; }

        // Allocate buffer
        // TODO: Use volk instead
        buffer = new T[count, sizeof(T)];

        // Update tap count
        this->count = count;
    }

    // Instantiate the class
    template class Taps<float>;
    template class Taps<Complex>;
}