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
        if (zero) { memset(data, 0, count*sizeof(T)); }
    }

    template <class T>
    Taps<T>::Taps(T* taps, int count) {
        // Allocate buffer
        reallocate(count);

        // Copy data over
        memcpy(data, taps, count*sizeof(T));
    }

    template <class T>
    Taps<T>::Taps(const Taps<T>& b) {
        // Allocate buffer
        reallocate(b.count);

        // Copy data over
        memcpy(data, b.data, b.count*sizeof(T));
    }

    template <class T>
    Taps<T>::Taps(Taps<T>&& b) {
        // Copy members
        data = b.data;
        count = b.count;

        // Neutralize old instance
        b.data = NULL;
        b.count = 0;
    }

    template <class T>
    Taps<T>::~Taps() {
        // Free the buffer if it is allocated
        if (data) { delete[] data; }
    }

    template <class T>
    Taps<T>& Taps<T>::operator=(const Taps<T>& b) {
        // Reallocate buffer
        reallocate(b.count);

        // Copy data over
        memcpy(data, b.data, b.count*sizeof(T));

        // Return self
        return *this;
    }

    template <class T>
    Taps<T>& Taps<T>::operator=(Taps<T>&& b) {
        // Copy members
        data = b.data;
        count = b.count;

        // Neutralize old instance
        b.data = NULL;
        b.count = 0;

        // Return self
        return *this;
    }

    template <class T>
    void Taps<T>::reallocate(int count) {
        // If the new count is no different and the buffer is allocated, no need to realloc
        if (data && this->count == count) { return; }

        // Free buffer
        if (data) { delete[] data; }

        // Allocate buffer
        data = new T[count, sizeof(T)];

        // Update tap count
        this->count = count;
    }

    // Instantiate the class
    template class Taps<float>;
    template class Taps<Complex>;
}