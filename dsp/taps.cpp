#include "taps.h"
#include "complex.h"

namespace dsp {
    template <class T>
    Taps<T>::Taps() {}

    template <class T>
    Taps<T>::Taps(const T* taps, size_t count) : Buffer<T>(taps, count) {}

    template class Buffer<float>;
    template class Buffer<double>;
    template class Buffer<Complex>;
}