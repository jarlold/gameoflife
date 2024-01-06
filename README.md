
<center> <!-- you will depricate this tag over my cold dead body -->
	<img src=./gameoflife_cropped.gif></img>
</center>


# What is this?
An implementation of John Conway's Game of Life in C++ with OpenGL. <br>
EDIT: This sent me down a rabbit hole, and it now contains some other life-like celluar automata.

# Why?
Train ride was long. It's in C++ instead of C because OpenGL C bindings weren't installed
on my laptop and the train didn't have internet.

# Installing
Install dependencies:
`apt install freeglut-dev`

Compile:
`./compile.sh ./life_gui.cpp`.

# Alternative Rule Sets
I've added a few alternative rules and some other celluar automata, you can select 
between them as shown below:

- `./a.out life` for the original Game of Life
- `./a.out hlife` for Nathan Thompson's High Life
- `./a.out slife` for Stochastic Life
- `./a.out w30` for Wolfram's Rule 30
<br>
Not addng any of these will simply run the original Game of Life.

# Controls
use good ol' `WASD` to move around, and `-`/`=` to zoom in and out. Pressing 
`space` advances the simulation by one tick, holding `space` works too.

# Optimization
I'm just storing everything in a big array because it lets me pass a kernel over
it easily. You could save memory by only storing the living pixels or such, but
it'd be annoying to write the kernel/convolution for it, and might run slower.

