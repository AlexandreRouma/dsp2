#pragma once
#include <math.h>

namespace dsp {
    /**
     * Two 32bit floating-point number representing the left and right channels.
    */
    struct Stereo {
        // TODO: Allow construction from a float

        void operator=(float b) {
            l = b;
            r = b;
        }

        /**
         * Left channel.
        */
        float l;

        /**
         * Right channel.
        */
        float r;
    };

    inline constexpr dsp::Stereo operator+(const dsp::Stereo& a, float b) {
        return dsp::Stereo{ a.l + b, a.r + b};
    }

    inline constexpr dsp::Stereo operator+(float a, const dsp::Stereo& b) {
        return dsp::Stereo{ a + b.l, a + b.r };
    }

    inline constexpr dsp::Stereo operator-(const dsp::Stereo& a, float b) {
        return dsp::Stereo{ a.l - b, a.r - b };
    }

    inline constexpr dsp::Stereo operator-(float a, const dsp::Stereo& b) {
        return dsp::Stereo{ a - b.l, a - b.r };
    }

    inline constexpr dsp::Stereo operator*(const dsp::Stereo& a, float b) {
        return dsp::Stereo{ a.l*b, a.r*b };
    }

    inline constexpr dsp::Stereo operator*(float a, const dsp::Stereo& b) {
        return dsp::Stereo{ a*b.l, a*b.r };
    }

    inline constexpr dsp::Stereo operator/(const dsp::Stereo& a, float b) {
        return dsp::Stereo{ a.l/b, a.r/b };
    }

    inline constexpr dsp::Stereo operator/(float a, const dsp::Stereo& b) {
        return dsp::Stereo{ a/b.l, a/b.r };
    }

    inline constexpr dsp::Stereo operator+(const dsp::Stereo& a, const dsp::Stereo& b) {
        return dsp::Stereo{ a.l + b.l, a.r + b.r };
    }

    inline constexpr dsp::Stereo operator-(const dsp::Stereo& a, const dsp::Stereo& b) {
        return dsp::Stereo{ a.l - b.l, a.r - b.r };
    }

    inline constexpr dsp::Stereo operator*(const dsp::Stereo& a, const dsp::Stereo& b) {
        return dsp::Stereo{ a.l*b.l, a.r*b.r };
    }

    inline constexpr dsp::Stereo operator/(const dsp::Stereo& a, const dsp::Stereo& b) {
        return dsp::Stereo{ a.l/b.l, a.r/b.r };
    }

    inline constexpr dsp::Stereo operator""_L(unsigned long long value) {
        return dsp::Stereo{ (float)value, 0.0f };
    }

    inline constexpr dsp::Stereo operator""_L(long double value) {
        return dsp::Stereo{ (float)value, 0.0f };
    }

    inline constexpr dsp::Stereo operator""_R(unsigned long long value) {
        return dsp::Stereo{ 0.0f, (float)value };
    }

    inline constexpr dsp::Stereo operator""_R(long double value) {
        return dsp::Stereo{ 0.0f, (float)value };
    }
}