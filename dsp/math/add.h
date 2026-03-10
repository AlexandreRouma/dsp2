#pragma once
#include <stdint.h>
#include <stddef.h>

namespace dsp::math {
    template <class T>
    class Add {
    public:
        /**
         * Add the samples together.
         * @param a Operand A.
         * @param b Operand B.
         * @param out Sum of A and B.
        */
        size_t process(const T* a, const T* b, T* out, size_t count);
    };

    const int test = sizeof(Add<float>);
}