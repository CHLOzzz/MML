# MML
A collaborator with Michigan Technological University's Math and Music Lab seeking to develop new musical scales through voltage quantization with the software VCV Rack.

# Early Stages
Currently, working plugins for exclusively Linux x86 systems have been generated. Attempting to go through the public repository so VCV properly exports the plugin for all operating systems. 2 plugins of 7 are currently ready for testing.

# Early Stage Testing
To build from source:

0) Install VCV Rack 2 on a Linux x86 system.

1) Have installed a C compiler. Recommended to install [CLion](https://www.jetbrains.com/clion/).

2) After git cloning the repository, navigate to the same directory as `Makefile`. Run `make && make dist && make install`.

3) Run VCV Rack 2, right click in an empty space, and the provided modules should be ready for use.

# Quantizers
Each quantizer presented is a voltage mapping inspired by Dr. Schneider's paper [A Non-Pythagorean Musical Scale Based on Logarithms](https://arxiv.org/abs/1312.5020). Currently this project focuses on mapping chromatic scales (12-note) via voltage.

Let $v$ denote the input voltage in Volts (V). Define $v _{f} = \lfloor v \rfloor$. Let $v _{o}$ be the voltage outputted by the quantizers. The mappings for all modules available in this plugin are as follows:

- **Base 2 Logarithm Quantizer (LOG QNT):**

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \log _{2} \left( 4 + \lfloor 12 * \left( v - v _{f} \right) \rfloor \right) \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

- **Square Root Quantizer (SQT QNT):**

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \sqrt{4 + \lfloor 12 * \left( v - v _{f} \right) \rfloor} \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$
