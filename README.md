
<center> <!-- you will depricate this tag over my cold dead body -->
	<img src=./gameoflife_cropped.gif></img>
</center>


# What is this?
An implementation of John Conway's Game of Life in C++ with OpenGL. 

# Why?
Train ride was long. It's in C++ instead of C because OpenGL C bindings weren't installed
on my laptop and the train didn't have internet.

# Installing
Install dependencies:
`apt install freeglut-dev`

Compile:
`./compile.sh ./life_gui.cpp`.

# Alternative Rule Sets
Currently only supports the original Conway's Game of Life and High Life. To change
which one you want to run, add `h` as a flag as shown below:

- `./a.out` to start the game normally, with some random pattern.
- `./a.out h` to start the game using "high life" ruleset.`
- `./a.out i` also runs the original game.

# Optimization
I'm just storing everything in a big array because it lets me pass a kernel over
it easily. You could save memory by only storing the living pixels or such, but
it'd be annoying to write the kernel/convolution for it, and might run slower.

