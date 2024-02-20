/**
 * MML LOG Quantizer Module
 * Leave this .cpp file "messy" as it should be used to learn from, not to assume from.
 * Looking at whomever takes over my position O.O
 */
#include "plugin.hpp"
float logV = 0.0f;


struct LogQnt : Module {
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

	LogQnt() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
        configInput(INPUT,"V/IN");
        configOutput(OUTPUT,"V/OUT");
	}

	void process(const ProcessArgs& args) override {
        if(inputs[INPUT].isConnected()){ // Plugin detects 3.5mm input
            // Store current input voltage
            logV = inputs[INPUT].getVoltage();

            // Apply MML algorithm & output
            logV = MMLFQFunction(logV);

            // Output
            outputs[OUTPUT].setVoltage(logV);
        }
        else {                           // Plugin doesn't detect input
            outputs[OUTPUT].setVoltage(0.f);
        }
	}

    /**
     * MML functionally quantized logarithmic non-Pythagorean musical function handling voltage. Helper function meant
     * to make code easier to read.
     *
     * @param vIn input voltage
     * @return output voltage after applying Logarithmic non-Pythagorean musical function
     */
    static float MMLFQFunction(float vIn) {
        if(vIn < 0.f) { // Input voltage is negative
            return(0.f);
        }
        else {          // Input voltage is non-negative
            float vFloor = floorf(vIn);
            return(
                    vFloor - 1.f + log2f(log2f(4.f + floorf(12.f * (vIn - vFloor))))
                    );
                    //return(
                            //vFloor - 1 + log2f(sqrtf(4 + (12 * (vIn - vFloor))))
                            //);
        }
    }
};


struct LogQntWidget : ModuleWidget {
	LogQntWidget(LogQnt* module) {
		// Create module & set panel
        setModule(module);
		//setPanel(createPanel(asset::plugin(pluginInstance, "res/LOG_QNT.pdf"))); // Included with "helper.py" - doesn't work
        setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LOG_QNT_resized.svg")));

        // Add screws to module - guessing just purely aesthetic
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0))); // Top Screw
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH))); // Bottom screw
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

        // Add input voltage to module
        addInput(createInput<PJ301MPort>(Vec(RACK_GRID_WIDTH-4, 270), module, LogQnt::INPUT));

        // Add output voltage to module
        addOutput(createOutput<DarkPJ301MPort>(Vec(RACK_GRID_WIDTH-4, 320), module, LogQnt::OUTPUT));
	}
};


Model* modelLogQnt = createModel<LogQnt, LogQntWidget>("LogQnt");