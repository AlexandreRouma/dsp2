#include "taps.h"
#include "complex.h"

namespace dsp {
    template <class T>
    Taps<T>::Taps() {}

    template <class T>
    Taps<T>::Taps(const T* taps, size_t count) : Buffer<T>(taps, count) {}

    template class Taps<float>;
    template class Taps<Complex>;
}