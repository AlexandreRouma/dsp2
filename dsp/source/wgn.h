#pragma once

namespace dsp::source {
    template <class T>
    class WGN {
    public:
        // Default constructor
        WGN();

        /**
         * Create a White Guassian Noise (WGN) source.
         * @param amplitude RMS amplitude.
         * @param offset DC offset.
        */
        WGN(float amplitude, T offset = 0.0f);

        /**
         * Get the RMS amplitude.
         * @return RMS amplitude.
        */
        float getAmplitude();

        /**
         * Set the RMS ampltiude.
         * @param amplitude RMS amplitude.
        */
        void setAmplitude(float amplitude);

        /**
         * Get the DC offset.
         * @return DC offset.
        */
        T getOffset();

        /**
         * Set the DC offset.
         * @param offset DC offset.
        */
        void setOffset(T offset);

        /**
         * Source samples.
         * @param out Buffer to write the sourced samples to.
         * @param count Number of samples to source.
         * @return Number of samples sourced. Always equal to `count` for this class.
        */
        size_t source(T* out, size_t count);

    private:
        float amplitude;
        T offset;
    };
}