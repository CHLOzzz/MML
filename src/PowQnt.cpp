/**
 * MML POW Quantizer Module
 */
#include "plugin.hpp"
float powV = 0.0f;


struct PowQnt : Module {
	enum ParamId {
        POW_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		ENUMS(INPUT,1),
        INPUTS_LEN
	};
	enum OutputId {
        ENUMS(OUTPUT,1),
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	PowQnt() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(INPUT,"V/IN");
        configOutput(OUTPUT,"V/OUT");
        configParam(POW_PARAM, 0.01, 4.f, 2.f, "V/POW");
	}

	void process(const ProcessArgs& args) override {
        if(inputs[INPUT].isConnected()){ // Plugin detects 3.5mm input
            // Store current input voltage
            powV = inputs[INPUT].getVoltage();

            // Apply MML algorithm & output
            powV = MMLFQFunction(powV, params[POW_PARAM].getValue());

            // Output
            outputs[OUTPUT].setVoltage(powV);
        }
        else {                           // Plugin doesn't detect input
            outputs[OUTPUT].setVoltage(-1.f);
        }
	}

    /**
     * MML functionally quantized power musical function handling voltage. Helper function meant
     * to make code easier to read.
     *
     * @param vIn input voltage
     * @return output voltage after applying square root musical function
     */
    static float MMLFQFunction(float vIn, float paramIn) {
        if(vIn < 0.f) { // Input voltage is negative
            return(0.f);
        }
        else {          // Input voltage is non-negative
            float vFloor = floorf(vIn);
            return(
                    vFloor - 1.f + log2f(powf(powf(2.f, paramIn) + ((powf(4.f, paramIn) - powf(2.f,paramIn)) / 12.f) * floorf(12.f * (vIn - vFloor)), 1.f / paramIn))
            );
        }
    }
};


struct PowQntWidget : ModuleWidget {
	PowQntWidget(PowQnt* module) {
		// Create module & set panel
        setModule(module);
		//setPanel(createPanel(asset::plugin(pluginInstance, "res/LOG_QNT.pdf"))); // Included with "helper.py" - doesn't work
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/POW_QNT_v1.svg")));

        // Add screws to module - guessing just purely aesthetic
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0))); // Top Screw
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH))); // Bottom screw

        // Add input voltage to module
        addInput(createInput<PJ301MPort>(Vec(RACK_GRID_WIDTH-4.25, 271), module, PowQnt::INPUT));

        // Add output voltage to module
        addOutput(createOutput<DarkPJ301MPort>(Vec(RACK_GRID_WIDTH-4.25, 320), module, PowQnt::OUTPUT));

        // Add knob for varying power
        addParam(createParam<RoundBlackKnob>(Vec(RACK_GRID_WIDTH-6.75, 225), module, PowQnt::POW_PARAM));
	}
};


Model* modelPowQnt = createModel<PowQnt, PowQntWidget>("PowQnt");