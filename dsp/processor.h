#pragma once
#include <stdint.h>

namespace dsp {
    template <class T_IN, class T_OUT>
    class SISOProcessor {
    public:
        size_t process(const T_IN* in, T_OUT* out, size_t count);
    };
}