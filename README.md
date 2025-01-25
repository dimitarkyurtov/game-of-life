# MPI Conway's Game of Life

This repository contains an MPI (Message Passing Interface) implementation of Conway's Game of Life with standard rules as described on the [Wikipedia page](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life). The grid wraps around when reaching the edges, making it a toroidal space. The code was developed and tested on M3 MacOS.

## Project Structure

```
.
├── README.md               # Project documentation
├── src                     # Source code directory
│   ├── game-of-life.cpp     # C++ implementation of the Game of Life (requires C++11)
│   ├── gol-visualizator.py  # Python script for animating the game
├── animations              # Generated animations
│   ├── input_data           # Common starting configurations - generated with the C++ program 
│   │   ├── beacon.txt
│   │   ├── heavy-weight-ship.txt
│   │   ├── medium-weight-ship.txt
│   │   ├── pulsar.txt
│   ├── videos               # Generated videos from input_data
│   │   ├── beacon.mov
│   │   ├── heavy-weight-ship.mov
│   │   ├── medium-weight-ship.mov
│   │   ├── pulsar.mov
├── benchmarking            
│   ├── benchmark.bash       # Bash script for performance evaluation
│   ├── results.numbers      # Benchmark results and visualization
```

## Installation

### Prerequisites

Ensure you have the following installed:

- OpenMPI (installed via Homebrew):
  ```sh
  brew install open-mpi
  ```
- Python3 (installed via Homebrew):
  ```sh
  brew install python
  ```
- Required Python libraries:
  ```sh
  pip install matplotlib numpy
  ```

## Compilation

Navigate to the `src` directory and compile the C++ source code using:

```sh
mpic++ -std=c++11 -o game-of-life game-of-life.cpp
```

## Usage

### Running the MPI Program

Execute the program using:

```sh
mpirun -np <num_processes> ./game-of-life <N> <iterations>
```

- `<num_processes>`: Number of processes to use.
- `<N>`: Grid size (NxN).
- `<iterations>`: Number of iterations to simulate.

Example:

```sh
mpirun -np 4 ./game-of-life 100 500
```

### Debugging and Animation

You can use the C++ program to generate input files for the Python script to visualize. You can do that by disabling RANDOM\_DATA macro and enabling the DEBUG\_ANIMATION. By doing that the program expect a starting configuration for the game. There are predefined configurations located as global variables in the source code. Make sure to disable the RANDOM\_DATA macro if you are generating the animation. Feel free to define your own starting configurations and animate them!

To enable debug mode and generate an animation input file, compile with:

```sh
mpic++ -std=c++11 -DDEBUG_ANIMATION -o game-of-life game-of-life.cpp
```

After compiling the program run it normally with the desired number of iterations. The *N* should match the width and height of the starting configuration defined in the source code. After running the program with debug mode enabled, generate an animation (the animation has 3-4 fps):

```sh
python3 gol-visualizator.py gol_animation.txt
```

## Benchmarking

A benchmarking script is provided in the `benchmarking` directory to evaluate runtime and speedup with different process counts.

Run the benchmark script with:

```sh
bash benchmarking/benchmark.bash
```

Results from running the bechmarks on my machine are stored in `benchmarking/results.numbers` with visualized graphs and hardware details.

