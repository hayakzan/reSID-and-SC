#include "SC_PlugIn.hpp"
#include "wave6581_P_T.h" // Include the triangle wave lookup table

static InterfaceTable* ft;

namespace SIDWaveformUGen {

class SIDWaveformUGen : public SCUnit {
public:
    SIDWaveformUGen();

private:
    void next(int nSamples);
    float mPhase; // Phase accumulator
    float mPhaseIncrement; // Phase increment per sample
};

SIDWaveformUGen::SIDWaveformUGen()
    : mPhase(0.0f), mPhaseIncrement(0.0f) {
    mCalcFunc = make_calc_function<SIDWaveformUGen, &SIDWaveformUGen::next>();
    next(1); // Initialize output
}

void SIDWaveformUGen::next(int nSamples) {
    const float* freqInput = in(0); // Frequency input
    const float gain = in0(1); // Gain input
    float* outbuf = out(0); // Output buffer

    const int tableSize = 4096; // Size of the triangle wave table
    const float tableStep = static_cast<float>(tableSize);

    for (int i = 0; i < nSamples; ++i) {
        // Update phase increment based on frequency
        mPhaseIncrement = freqInput[i] / sampleRate();

        // Update phase
        mPhase += mPhaseIncrement;

        // Wrap phase to stay within [0, 1]
        if (mPhase >= 1.0f) {
            mPhase -= 1.0f;
        }

        // Map phase to table index
        int idx = static_cast<int>(mPhase * tableStep) % tableSize;

        // Fetch triangle wave sample from lookup table and apply gain
        outbuf[i] = wave6581_P_T[idx] * gain / 4096.0f; // Normalize to [0, 1]
    }
}

} // namespace SIDWaveformUGen

// Plugin entry point
PluginLoad(SIDWaveformUGenUGens) {
    ft = inTable;
    registerUnit<SIDWaveformUGen::SIDWaveformUGen>(ft, "SIDWaveformUGen", false);
}
