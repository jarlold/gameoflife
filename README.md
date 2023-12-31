# What is this?
An implementation of John Conway's Game of Life in C++ with OpenGL. 

# Why?
Train ride was long.

# Installing
Install dependencies:
`apt install freeglut-dev`

Compile:
`./compile ./life_gui.cpp`.


# Optimization
I'm just storing everything in a big array because it lets me pass a kernel over
it easily. You could save memory by only storing the living pixels or such, but
it'd be annoying to write the kernel/convolution for it, and might run slower.

