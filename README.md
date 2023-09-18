# Raycasting Game

This is a simple raycasting game written in C. The game renders a 3D-like environment using raycasting techniques. 

![Game Screenshot](Maze_game.png)

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [License](#license)

## Features

- First-person perspective.
- 3D-like environment created using raycasting.
- Textured walls and sprite rendering.
- Mini-map for navigation.
- Simple game objects (barrels, lights, guard, armor).

## Prerequisites

Before running the game, ensure you have the following dependencies installed:

- [SDL2](https://www.libsdl.org/download-2.0.php): Simple DirectMedia Layer library for graphics and window management.
- [upng](https://github.com/elanthis/upng): A lightweight PNG decoder library.

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/istacyn/maze

2. Navigate to the project directory:

    cd maze

3. Build the game:

    make

4. Run the game:
    
    ./maze

## Controls

**W**: Move forward

**S**: Move backward

**A**: Strafe left

**D**: Strafe right

**Left Arrow**: Rotate left

**Right Arrow**: Rotate right

**M**: Toggle minimap

**Esc**: Quit the game

## Project Structure

`src/`: Source code files.
`images/`: Textures used in the game.
`Makefile`: Makefile for building the project.
`README.md`: This file.

## Technical Details

The game uses raycasting to render the 3D-like environment. It features textured walls and sprite rendering. The codebase is organized into several C files for different aspects of the game, including player movement, rendering, raycasting, textures, walls, sprites, and utility functions.

## License
This project is licensed under the MIT License. See the LICENSE file for details.