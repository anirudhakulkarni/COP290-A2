# Steiner travelling salesman problem Simulation

Visualize path finding algorithm

## Installation

1. To install clone the repo, navigate to `src` and run `make all`
2. Debugging:
    1. To generate random maze `make maze`
    2. To eject the repo `make clean`
    3. To test build `make build`
    1. To run `make run`

Libraries:
* sdl2 `brew install sdl2`
* sdl2_image `brew install sdl2_image`
* sdl2_net `brew install sdl2_net`
* sdl2_ttf `brew install sdl2_ttf`

## Directory Structure
``` 
├── build         # Build directory with compiled files
├── makefile      # makefile for compilation
├── outputs       # intermediate outputs
│   ├── matrix.out
│   ├── MAZE_100x100_n9604.bmp
│   ├── MAZE_20x20_n324.bmp
│   └── MAZE_50x10_n384.bmp
├── src           # Core logic
│   ├── constants.h
│   ├── game
│   ├── main.cpp
│   ├── makefile
│   ├── matrix.out
│   ├── mazegenerator.cpp
│   ├── mazegenerator.hpp
│   ├── path.txt
│   ├── resources # resources - images
│   │   ├── bullet.bmp
│   │   ├── player.bmp
│   │   └── tile.bmp
│   ├── select.cpp
│   ├── select.hpp
│   ├── steiner_tsp.cpp
│   ├── steiner_tsp.hpp
│   ├── text.cpp
│   ├── text.hpp
│   ├── travel.cpp
│   ├── travel.hpp
│   └── valid_path.cpp
└── statement.png

```
