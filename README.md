*This project has been created as part of the 42 curriculum by amacaull, ilsadi.*

# cub3D

## Description

cub3D is a 3D game engine inspired by the iconic Wolfenstein 3D, widely considered the first true first-person shooter. The project uses **ray-casting** to render a real-time first-person view inside a maze defined by a `.cub` scene file.

The player can navigate the maze using keyboard controls, with textured walls that change depending on their cardinal orientation (North, South, East, West), and configurable floor and ceiling colors.

### Bonus Features

Beyond the mandatory requirements, our implementation includes:

- **Wall collisions** — the player cannot walk through walls.
- **Minimap** — a circular, player-centered minimap with fog of war and line-of-sight visibility.
- **Doors** — animated doors that can be opened with a key item using the `E` key.
- **Animated sprites** — a 120-frame animated wall texture cycle.
- **Mouse rotation** — rotate the camera by moving the mouse.
- **Enemies (Endermen)** — hostile entities that teleport around the map and deal damage to the player.
- **Collectibles** — keys (to open doors), golden apples (restore health), and the dragon egg (triggers victory).
- **HUD** — Minecraft-style hotbar with inventory slots, health hearts, food bar, crosshair, offhand torch, and hand-view rendering for each item.
- **Game states** — game over screen (on death) and victory screen (on collecting and using the dragon egg).
- **Distance shading** — fog effect that darkens distant walls and sprites.
- **Floor & ceiling textures** — textured floor and ceiling rendering in addition to flat color support.

## Instructions

### Requirements

- **Libraries**: miniLibX, libft (included)
- **Compiler**: `cc` with flags `-Wall -Wextra -Werror`

### Compilation

```bash
# Compile the bonus version (includes all features)
make bonus

# Clean object files
make clean

# Full clean (remove binary and objects)
make fclean

# Recompile from scratch
make re
```

### Execution

```bash
./cub3D maps/your_map.cub
```

The program takes a single argument: a scene description file with the `.cub` extension.

### Map File Format

The `.cub` file must contain:

1. **Texture paths** for the four wall orientations:
   ```
   NO ./path_to_north_texture
   SO ./path_to_south_texture
   WE ./path_to_west_texture
   EA ./path_to_east_texture
   ```

2. **Floor and ceiling colors** in RGB (0–255):
   ```
   F 220,100,0
   C 225,30,0
   ```

3. **The map** (must be last), composed of:
   - `0` — empty space
   - `1` — wall
   - `2` — animated wall
   - `D` — door
   - `K` — key collectible
   - `A` — golden apple collectible
   - `V` — dragon egg collectible
   - `M` — enderman spawn
   - `N`, `S`, `E`, `W` — player start position and orientation

The map must be enclosed by walls (`1`). Spaces are valid and treated as void.

### Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward / left / backward / right |
| `←` `→` | Rotate camera left / right |
| Mouse movement | Rotate camera |
| `Shift` | Sprint (drains food) |
| `E` | Interact (use item / open door) |
| `1`–`9` | Select hotbar slot |
| `ESC` | Quit the game |

## Resources

### References

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the primary reference for understanding and implementing the DDA raycasting algorithm, wall rendering, floor/ceiling casting, and sprite projection.
- [42 miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — reference for the miniLibX graphics library API.
- [Wolfenstein 3D source code (GitHub)](https://github.com/id-Software/wolf3d) — original Id Software source code for historical and technical reference.
- [Permadi's Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) — complementary raycasting explanations with visual diagrams.

### AI Usage

AI tools were used during the development of this project for the following tasks:

- **Understanding new concepts**: Getting explanations on raycasting principles, DDA algorithm mechanics, sprite projection math, and floor/ceiling casting to better grasp the theory before implementing.
- **README writing**: Drafting and structuring this README file.
