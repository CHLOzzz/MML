/**
 * MML SQT Quantizer Module
 */
#include "plugin.hpp"
float sqtV = 0.0f;


struct SqtQnt : Module {
	enum ParamId {
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

	SqtQnt() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(INPUT,"V/IN");
        configOutput(OUTPUT,"V/OUT");
	}

	void process(const ProcessArgs& args) override {
        if(inputs[INPUT].isConnected()){ // Plugin detects 3.5mm input
            // Store current input voltage
            sqtV = inputs[INPUT].getVoltage();

            // Apply MML algorithm & output
            sqtV = MMLFQFunction(sqtV);

            // Output
            outputs[OUTPUT].setVoltage(sqtV);
        }
        else {                           // Plugin doesn't detect input
            outputs[OUTPUT].setVoltage(0.f);
        }
	}

    /**
     * MML functionally quantized square root musical function handling voltage. Helper function meant
     * to make code easier to read.
     *
     * @param vIn input voltage
     * @return output voltage after applying square root musical function
     */
    static float MMLFQFunction(float vIn) {
        if(vIn < 0.f) { // Input voltage is negative
            return(0.f);
        }
        else {          // Input voltage is non-negative
            float vFloor = floorf(vIn);
            return(
                    vFloor - 1.f + log2f(sqrtf(4.f + floorf(12.f * (vIn - vFloor))))
            );
        }
    }
};


struct SqtQntWidget : ModuleWidget {
	SqtQntWidget(SqtQnt* module) {
		// Create module & set panel
        setModule(module);
		//setPanel(createPanel(asset::plugin(pluginInstance, "res/LOG_QNT.pdf"))); // Included with "helper.py" - doesn't work
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SQT_QNT.svg")));

        // Add screws to module - guessing just purely aesthetic
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0))); // Top Screw
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH))); // Bottom screw

        // Add input voltage to module
        addInput(createInput<PJ301MPort>(Vec(RACK_GRID_WIDTH-4.25, 271), module, SqtQnt::INPUT));

        // Add output voltage to module
        addOutput(createOutput<DarkPJ301MPort>(Vec(RACK_GRID_WIDTH-4.25, 320), module, SqtQnt::OUTPUT));
	}
};


Model* modelSqtQnt = createModel<SqtQnt, SqtQntWidget>("SqtQnt");