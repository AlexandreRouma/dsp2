#pragma once
#include <math.h>

namespace dsp {
    /**
     * Complex 32bit floating-point number.
     * This struct is NOT thread-safe.
    */
    struct Complex {
        // Default constructor
        constexpr inline Complex() {}

        /**
         * Create a complex number from its real and imaginary components.
         * @param re Real component.
         * @param im Imaginary component.
        */
        constexpr inline Complex(float re, float im) {
            this->re = re;
            this->im = im;
        }

        /**
         * Create a complex number from a real value.
         * @param value Real component.
        */
        constexpr inline Complex(float value) {
            re = value;
            im = 0.0f;
        }

        /**
         * Compute the conjugate of the Complex number.
        */
        constexpr inline Complex conj() const {
            return Complex{ re, -im };
        }

        /**
         * Compute the phase of the Complex number normalized between -pi and pi.
        */
        inline float phase() const {
            return atan2f(im, re);
        }
        
        /**
         * Compute the amplitude of the Complex number.
        */
        inline float amplitude() const {
            return sqrtf(re*re + im*im);
        }

        // Assignment operator
        inline void operator=(float b) {
            re = b;
        }

        /**
         * Real component.
        */
        float re;

        /**
         * Imaginary component.
        */
        float im;
    };
}

inline constexpr dsp::Complex operator+(const dsp::Complex& a, float b) {
    return dsp::Complex{ a.re + b, a.im };
}

inline constexpr dsp::Complex operator+(float a, const dsp::Complex& b) {
    return dsp::Complex{ a + b.re, b.im };
}

inline constexpr dsp::Complex operator-(const dsp::Complex& a, float b) {
    return dsp::Complex{ a.re - b, a.im };
}

inline constexpr dsp::Complex operator-(float a, const dsp::Complex& b) {
    return dsp::Complex{ a - b.re, b.im };
}

inline constexpr dsp::Complex operator*(const dsp::Complex& a, float b) {
    return dsp::Complex{ a.re*b, a.im*b };
}

inline constexpr dsp::Complex operator*(float a, const dsp::Complex& b) {
    return dsp::Complex{ a*b.re, a*b.im };
}

inline constexpr dsp::Complex operator/(const dsp::Complex& a, float b) {
    return dsp::Complex{ a.re/b, a.im/b };
}

inline constexpr dsp::Complex operator/(float a, const dsp::Complex& b) {
    float denom = b.re*b.re + b.im*b.im;
    return dsp::Complex{ a*b.re / denom, -a*b.im / denom };
}

inline constexpr dsp::Complex operator+(const dsp::Complex& a, const dsp::Complex& b) {
    return dsp::Complex{ a.re + b.re, a.im + b.im };
}

inline constexpr dsp::Complex operator-(const dsp::Complex& a, const dsp::Complex& b) {
    return dsp::Complex{ a.re - b.re, a.im - b.im };
}

inline constexpr dsp::Complex operator*(const dsp::Complex& a, const dsp::Complex& b) {
    return dsp::Complex{ a.re*b.re - a.im*b.im, a.im*b.re + a.re*b.im };
}

inline constexpr dsp::Complex operator/(const dsp::Complex& a, const dsp::Complex& b) {
    float denom = b.re*b.re + b.im*b.im;
    return dsp::Complex{ (a.re*b.re + a.im*b.im) / denom, (a.im*b.re - a.re*b.im) / denom };
}

inline constexpr dsp::Complex operator""j(unsigned long long value) {
    return dsp::Complex{ 0.0f, (float)value };
}

inline constexpr dsp::Complex operator""j(long double value) {
    return dsp::Complex{ 0.0f, (float)value };
}