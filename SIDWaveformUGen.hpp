// PluginSIDWaveformUGen.hpp
// Yigit Kolat (yigitkolat@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace SIDWaveformUGen {

class SIDWaveformUGen : public SCUnit {
public:
    // Constructor
    SIDWaveformUGen();

    // Destructor (optional)
    ~SIDWaveformUGen() = default;

private:
    // Signal processing function
    void next(int nSamples);

    // Internal member variables
    float mGain;           // Control-rate gain parameter
    float mAccumulator;    // Internal accumulator for phase/waveform
    float mCurrentOutput;  // Current waveform output sample
};

} // namespace SIDWaveformUGen
