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
