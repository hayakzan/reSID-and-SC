// SIDWaveformUGen.sc
// Yigit Kolat (yigitkolat@gmail.com)

SIDWaveformUGen : UGen {

    // Audio rate method
    *ar { |input, gain = 1.0|
        ^this.multiNew('audio', input, gain);
    }
	//
	// // Check input validity
	// checkInputs {
	// 	if (rate == \audio) {
	// 		// Ensure the input rates are compatible
	// 		if (inputs[0].rate != \audio) {
	// 			Error("Input must be audio rate for SIDWaveformUGen").throw;
	// 		}
	// 	}
	//
	// 	// Gain must be a scalar value
	// 	if (inputs[1].rate != \control) {
	// 		Error("Gain must be a control rate parameter").throw;
	// 	}
	//
	// 	^this.checkValidInputs;
	// }
}
