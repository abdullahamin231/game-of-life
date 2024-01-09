# Game of Life Simulation

## Overview
This program is a simple implementation of Conway's Game of Life using the SFML graphics library in C++. The Game of Life is a cellular automaton devised by the British mathematician John Conway. It is a zero-player game, meaning that its evolution is determined by its initial state, with no further input from humans.

## Features
- **Menu System:** The program features a menu system where users can navigate through options like starting the Game of Life simulation, initializing a custom configuration, or exiting the program.
- **Initialization:** Users can initialize the starting state of the simulation by clicking on the cells in a grid. This allows for custom configurations before starting the simulation.
- **Randomization and Inversion:** During initialization, users can press 'Space' to randomize the grid or 'R' to invert the current state of the cells.
- **Simulation:** Once initialized, the program enters the simulation mode, where the Game of Life rules are applied to evolve the cellular automaton over time.
- **Dynamic Updates:** The simulation is updated periodically, and users can escape to the menu or exit the program at any time.

## Controls
- **Menu Navigation:**
  - Use the 'Up' and 'Down' arrow keys to navigate through the menu options.
  - Press 'Enter' to select an option.
- **Initialization:**
  - Click on cells in the grid to set their initial state during initialization.
  - Press 'Space' to randomize the grid.
  - Press 'R' to invert the current state of the cells.
  - Press 'Enter' to start the simulation after initialization.
  - Press 'Escape' to return to the main menu.
- **Simulation:**
  - Press 'Escape' to return to the main menu.

## Compilation and Execution
Ensure you have the SFML library installed on your system. You can compile the program using a C++ compiler and link against the SFML library. For example, using g++:

```bash
g++ -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system

![App Screenshot](https://snipboard.io/9BS1Fu.jpg)
![App Screenshot](https://snipboard.io/vqnVM5.jpg)
![App Screenshot](https://snipboard.io/x1dUy0.jpg)
