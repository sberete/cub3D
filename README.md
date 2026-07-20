# cub3D

A 42 school project that implements a simplified 3D game engine using raycasting, inspired by Wolfenstein 3D. Written in C with the MiniLibX graphics library, it renders a first-person view of a map described in a custom `.cub` file format.

## Features

The engine parses and validates `.cub` map files (textures, colors, player spawn point), renders walls using raycasting, and lets the player move and look around in real time. Interactive doors that can be opened and closed are also supported.

## Map format

Maps are plain text files (`.cub`) describing textures for each wall orientation, floor and ceiling colors, and the map layout itself using a grid of characters (walls, empty space, player start position and orientation).

## Build

```bash
make        # builds cub3D (also clones MiniLibX automatically)
make clean  # removes object files
make fclean # also removes the executable and MiniLibX
make re     # rebuilds everything
```

## Usage

```bash
./cub3D maps/good/map.cub
```

## Controls

| Action | Control |
|---|---|
| Move | `W` `A` `S` `D` |
| Look around | Arrow keys / mouse |
| Open/close door | `E` |
| Quit | `Esc` |

## Constraints

- Follows the 42 Norm
- Compiles without errors or warnings (`-Wall -Wextra -Werror`)
- Relies on `libft` and MiniLibX as internal/graphics libraries
