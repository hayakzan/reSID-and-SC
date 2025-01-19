// SIDWaveformUGen.cpp
// Yigit Kolat (yigitkolat@gmail.com)

#include "SC_PlugIn.hpp"
#include "SIDWaveformUGen.hpp"
#include "wave6581_P_T.h"


static InterfaceTable* ft;

namespace SIDWaveformUGen {

// Constructor
SIDWaveformUGen::SIDWaveformUGen() {
    // Set the calculation function for this UGen
    mCalcFunc = make_calc_function<SIDWaveformUGen, &SIDWaveformUGen::next>();
    next(1); // Process 1 sample during initialization
}

// Processing function
void SIDWaveformUGen::next(int nSamples) {
    // Audio-rate input (channel 0)
    const float* input = in(0);

    // Control-rate parameter: gain (channel 1)
    const float gain = in0(1);

    // Output buffer
    float* outbuf = out(0);

    // Apply gain to input signal
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain;
    }
}

} // namespace SIDWaveformUGen

// Plugin entry point
PluginLoad(SIDWaveformUGenUGens) {
    ft = inTable; // Assign the interface table
    // Register the UGen
    registerUnit<SIDWaveformUGen::SIDWaveformUGen>(ft, "SIDWaveformUGen", false);
}
