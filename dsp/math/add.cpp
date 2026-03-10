#include "add.h"
#include <type_traits>
#include <volk/volk.h>
#include "../complex.h"

namespace dsp::math {
    template <class T>
    size_t Add<T>::process(const T* a, const T* b, T* out, size_t count) {
        if constexpr (std::is_same_v<T, float>) {
            // Add using volk
            volk_32f_x2_add_32f(out, a, b, count);
        }
        else if constexpr (std::is_same_v<T, Complex>) {
            // Add using volk
            volk_32fc_x2_add_32fc(out, a, b, count);
        }
    }
}