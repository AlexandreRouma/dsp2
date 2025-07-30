#include "fm.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace dsp::demod {
    FM_s::FM_s() {}

    FM_s::FM_s(float deviation, float samplerate) {
        // Save the settings
        this->deviation = deviation;
        this->samplerate = samplerate;

        // Update the normalization factor
        normFact = samplerate / (2.0f * M_PI * deviation);
    }

    float FM_s::getDeviation() const {
        // Acquire the settings mutex
        std::lock_guard<std::recursive_mutex> lck(settingsMtx);

        // Return the deviation
        return deviation;
    }

    void FM_s::setDeviation(float deviation) {
        // Acquire the settings mutex
        std::lock_guard<std::recursive_mutex> lck(settingsMtx);

        // Update the deviation
        this->deviation = deviation;

        // Update the normalization factor
        normFact = samplerate / (2.0f * M_PI * deviation);
    }

    float FM_s::getSamplerate() const {
        // Acquire the settings mutex
        std::lock_guard<std::recursive_mutex> lck(settingsMtx);

        // Return the samplerate
        return samplerate;
    }

    void FM_s::setSamplerate(float samplerate) {
        // Acquire the settings mutex
        std::lock_guard<std::recursive_mutex> lck(settingsMtx);

        // Update the samplerate
        this->samplerate = samplerate;

        // Update the normalization factor
        normFact = samplerate / (2.0f * M_PI * deviation);
    }

    void FM_s::reset() {
        // Acquire the settings mutex
        std::lock_guard<std::recursive_mutex> lck(settingsMtx);
        
        // Set the current phase to zero
        phase = 0.0f;
    }

    int FM_s::process(const Complex* in, float* out, int count) {
        for (int i = 0; i < count; i++) {
            // Get the current phase
            float cphase = in[i].phase();

            // Compute the difference with the last phase
            // TODO
            //out[i] = math::normalizePhase(cphase - phase) * normFact;

            // Save the current phase for the next iteration
            phase = cphase;
        }
        return count;
    }

    FM::FM() {}

    FM::FM(float deviation, float samplerate) :
        FM_s(deviation, samplerate),
        ProcessorAsync(this)
    {}

    FM::FM(Stream<Complex>* in, float deviation, float samplerate) :
        FM_s(deviation, samplerate),
        ProcessorAsync(this, in)
    {}

    FM::FM(Stream<Complex>* in, Stream<float>* out, float deviation, float samplerate) :
        FM_s(deviation, samplerate),
        ProcessorAsync(this, in, out)
    {}
}