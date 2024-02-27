# MML
A collaborator with Michigan Technological University's Math and Music Lab seeking to develop new musical scales through voltage quantization with the software VCV Rack.

# Unofficial Release
The MML plugin is now available from VCV Library and all modules can be accessed from [this link](https://library.vcvrack.com/?brand=MML). This is an unofficial release as we at MML are new to software development and wanted to see what we have to work with.

# Building from Source
To build from source:

0) Install VCV Rack 2 on your device.

1) Have installed a C compiler. Recommended to install [CLion](https://www.jetbrains.com/clion/) for easy compilation.

2) Navigate to a desired directory and run `git clone https://github.com/CHLOzzz/MML.git && cd MML`. After cloning the repository and navigating to the directory, run `make clean && make && make dist && make install`. The plugin should install itself for use with VCVRack.

3) Run VCV Rack 2, right click in an empty space, and the provided modules should be listed and ready for use.

# Quantizers
Each quantizer presented is a voltage mapping inspired by Dr. Schneider's paper [A Non-Pythagorean Musical Scale Based on Logarithms](https://arxiv.org/abs/1312.5020). Currently this project focuses on mapping chromatic scales (12-note) via voltage.

Let $v$ denote the input voltage in Volts (V). Define $v _{f} = \lfloor v \rfloor$. Let $v _{o}$ be the voltage outputted by the quantizers. The mappings for all modules available in this plugin are as follows:

- **Base 2 Logarithm Quantizer (LOG QNT):**

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \log _{2} \left( 4 + \lfloor 12 * \left( v - v _{f} \right) \rfloor \right) \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

- **Square Root Quantizer (SQT QNT):**

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \sqrt{4 + \lfloor 12 * \left( v - v _{f} \right) \rfloor} \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

- **Power Quantizer (POW QNT):**
  Will be released alongside the official release of the full MML plugin suite, and superscedes **SQT QNT**.

  Assume $p > 0$.

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \sqrt[p]{2 ^{p} + \frac{4 ^{p} - 2 ^{p}}{12} * \lfloor 12 * \left( v - v _{f} \right) \rfloor} \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

# Credit
A huge thanks to the following who all contributed to the project (ascending last name order):

- Michael Maxwell: Audio Synthesis Consultant
- Chloe McCarthy: Lead Programmer
- Joshua Pfeffer: Lead Artistic Designer
- Robert Schneider: MML Founder & Researcher
