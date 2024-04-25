# MML
A collaborator with Michigan Technological University's Math and Music Lab seeking to develop new musical scales through voltage quantization with the software VCV Rack.

# Official Release
The [Mathematics and Music Lab (MML)](https://library.vcvrack.com/MML) plugin for VCV Rack 2 is now officially released, and available from [VCV Library](https://library.vcvrack.com)!

# Building from Source
To build from source:

0) Install VCV Rack 2 on your device.

1) Have installed a C compiler. Recommended to install [CLion](https://www.jetbrains.com/clion/) for easy compilation.

2) Navigate to a desired directory and run `git clone https://github.com/CHLOzzz/MML.git && cd MML`. After cloning the repository and navigating to the directory, run `make clean && make && make dist && make install`. The plugin should install itself for use with VCVRack.

3) Run VCV Rack 2, right click in an empty space, and the provided modules should be listed and ready for use.

4) (Troubleshooting) As of VCV Rack 2.5.1, on my personal machine the plugins folder was changed, and may be the case for others building from source. After running `make install`, you will be given a directory where the .vcvplugin file was placed; simply copy this file, paste into the appropriate plugins folder, and run VCV Rack.
- For example, my old directory in Linux was "/home/USER/.Rack2/plugins-lin-x64", and changed to "/home/USER/.local/share/Rack2/plugins-lin-x64". So when I `make install`, I copy from the first directory the .vcvplugin file created and then paste into the second directory.

# Quantizers
Each quantizer presented is a voltage mapping inspired by Dr. Schneider's paper [A Non-Pythagorean Musical Scale Based on Logarithms](https://arxiv.org/abs/1312.5020) with an updated paper accompanying: [Mathematics of the MML functional quantizer modules for VCV Rack software synthesizer](https://arxiv.org/abs/2404.04739). Currently this project focuses on mapping chromatic scales (12-note) via voltage.

Let $v$ denote the input voltage in Volts (V). Define $v _{f} = \lfloor v \rfloor$. Let $v _{o}$ be the voltage outputted by the quantizers. The mappings for all quantizers available in this plugin are as follows:

- **Base 2 Logarithm Quantizer (LOG QNT):** Quantizer to produce the non-Pythagorean musical scale of [The Apples in Stereo](https://en.wikipedia.org/wiki/The_Apples_in_Stereo), tuned to the logarithms of whole numbers. 

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \log _{2} \left( 4 + \lfloor 12 * \left( v - v _{f} \right) \rfloor \right) \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

- **Square Root Quantizer (SQT QNT):** Quantizer to produce a musical scale tuned to the square roots of whole numbers.

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \sqrt{4 + \lfloor 12 * \left( v - v _{f} \right) \rfloor} \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

- **Power Quantizer (POW QNT):** Quantizer to produce infinite families of musical scales at the turn of a knob, tuned to a special power function.

  Assume $p > 0$.

  $$v _{o} \left( v \ge 0 \right) = v _{f} - 1 + \log _{2} \left( \sqrt[p]{2 ^{p} + \frac{4 ^{p} - 2 ^{p}}{12} * \lfloor 12 * \left( v - v _{f} \right) \rfloor} \right)$$

  $$v _{o} \left( v < 0 \right) = 0$$

# Future Quantizers
Because the mathematics behind the quantizers is well understood, we also propose the following quantizers in future releases:

- **Power Quantizer 2 (POW QNT 2):** Quantizer to produce infinite families of musical scales at the turn of a knob, tuned to a similarly special power function compared to the original **POW QNT**.

- **Sine Quantizer (SIN QNT):** Quantizer to produce a musical scale tuned to the sine function. 

- **Arctangent Quantizer (ATN QNT):** Quantizer to produce a musical scale tuned to the arctangent function. 

# Credit
A huge thanks to the following who all contributed to the project (order from implementation to theorization):

- Cody McCarthy: Lead Programmer
- Max Schneider: Programming Consultant & Math Assistant
- Michael G. Maxwell: Audio Synthesis Consultant
- Joshua Pfeffer: Lead Artistic Designer
- Robert Schneider: MML Founder & Researcher
- Andrew V. Sills: Researcher

# Changelog
Full changelog provided in "changelog.txt".
