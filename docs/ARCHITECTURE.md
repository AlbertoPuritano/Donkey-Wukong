# Architecture overview

Donkey Wukong is organized as a small C++11 Allegro 5 game. The code is split into game orchestration, rendering, audio, and entity behavior.

## High-level runtime flow

```text
main.cpp
  ├─ Initializes Allegro core systems and add-ons
  ├─ Creates the display, timer, event queue, fonts, and rendering buffer
  ├─ Creates Graphics, Sounds, and Game managers
  └─ Enters the main menu loop
       ├─ New game → gameplay loop → cutscenes/static result screens
       ├─ Options → difficulty/audio settings
       ├─ Credits/static screen
       └─ Exit
```

The game runs at a timer rate of 30 frames per second. Input is received through Allegro keyboard events, and rendering happens when timer events mark the frame as ready to redraw.

## Source layout

| Path | Purpose |
| --- | --- |
| `Source/main.cpp` | Program entry point and Allegro initialization/shutdown. |
| `Source/Game.cpp` | Menu flow, gameplay loop, options screen, cutscenes, lives, levels, and scoring. |
| `Source/Graphics.cpp` | Loading and drawing bitmaps, fonts, maps, HUD, menus, cutscenes, and static screens. |
| `Source/Sounds.cpp` | Loading, playing, looping, stopping, and destroying Allegro audio samples. |
| `Source/Entities.cpp` | Movement, gravity, collision-adjacent behavior, animation frame state, barrels, player, and Kong. |
| `Headers/*.hpp` | Class declarations, shared constants, and Allegro-facing interfaces. |

## Main systems

### `Game`

`Game` coordinates the application state. It owns no Allegro resources directly; instead, it receives pointers to `Graphics` and `Sounds` managers.

Main responsibilities:

- Main menu handling.
- Gameplay loop and keyboard state tracking.
- Level progression and life count.
- Score updates.
- Options menu behavior.
- Cutscene and static screen sequencing.

### `Graphics`

`Graphics` is responsible for drawing all visual state using Allegro bitmaps and fonts.

Main responsibilities:

- Loading static bitmap resources used across frames.
- Loading level maps from `Assets/Maps/levelN.txt`.
- Drawing the tile map, player, Kong, barrels, Peach, hammer, lives, scores, menus, cutscenes, and static images.
- Scaling the internal game buffer to the fullscreen display.

The internal playfield constants are defined in `Headers/Entities.hpp`:

```text
Width:  500 pixels
Height: 560 pixels
Tile:   20 pixels
Grid:   25 columns x 28 rows, with zero-based access in code
```

### `Sounds`

`Sounds` wraps Allegro sample loading and playback.

Main responsibilities:

- Reserving sample channels.
- Loading WAV files from `Assets/Audio/`.
- Playing one-shot effects.
- Looping menu audio.
- Preventing overlapping walking/jump/hammer sample instances where applicable.
- Releasing audio resources on shutdown.

### Entity model

`Entity` is the base class for position, grid access, animation frame, falling state, ladder state, and direction.

Derived/specialized classes:

- `Player` — movement, jumping, climbing, gravity, hammer state, and death state.
- `Barrel` — rolling, falling, direction changes, stop condition, and animation frames.
- `Kong` — barrel throw timing and animation frame progression.

## Coordinates and tiles

The code uses pixel coordinates for entities and converts to tile coordinates with division by `20`. The map grid is read from text files where:

- `0` means empty space.
- `1` means ladder.
- `2` means solid ground/platform.

Some comments in the source note that X/Y naming is historically inverted in places. When changing movement or drawing logic, verify whether a variable represents screen row, screen column, pixel X, or pixel Y before editing.

## Resource ownership notes

Allegro resources are manually created and destroyed. When maintaining the code:

- Match each persistent Allegro allocation with a destroy call.
- Be careful with per-frame bitmap loading; repeated load/destroy behavior can affect performance.
- Keep asset path assumptions synchronized with build/run documentation.
- Avoid changing resource lifetime and event-loop behavior in the same patch unless necessary.

## Runtime dependencies

The executable depends on the `Assets/` directory at runtime. It does not embed assets into the binary. See [Assets and levels](./ASSETS_AND_LEVELS.md) for the expected structure.

## Extension points

Common project changes usually touch these areas:

| Goal | Likely files/docs to update |
| --- | --- |
| Add or rename an asset | `Assets/`, `Source/Graphics.cpp` or `Source/Sounds.cpp`, `docs/ASSETS_AND_LEVELS.md` |
| Add a level | `Assets/Maps/`, level progression logic, `docs/ASSETS_AND_LEVELS.md` |
| Change controls | `Source/Game.cpp`, `docs/USER_GUIDE.md` |
| Change build flags/dependencies | `Makefile` or CMake files, `README.md`, `docs/BUILDING.md` |
| Change gameplay scoring | `Source/Game.cpp`, `docs/USER_GUIDE.md` |

## Maintenance cautions

- The game uses raw pointers and manual memory management; changes should be validated carefully.
- The current map format is simple and has no schema validation beyond file reads.
- Asset file names are case-sensitive on some systems.
- Fullscreen display behavior can differ by OS and window manager.


