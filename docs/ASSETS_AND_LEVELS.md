# Assets and levels

This document describes the runtime asset layout and the level-map text format.

## Runtime asset root

The game expects an `Assets/` directory next to the repository root and loads files through paths relative to the executable working directory:

```text
../Assets/...
```

With the current build layout, run the executable from `build/` so `../Assets` resolves correctly.

## Asset directory structure

```text
Assets/
├── Audio/      # WAV sound effects and music loops
├── Bitmaps/    # PNG sprites, menus, UI images, cutscene images, and tiles
├── Fonts/      # TTF font files
└── Maps/       # Text level maps
```

## Audio assets

Audio files are WAV files loaded through Allegro audio/acodec APIs.

Important currently referenced files include:

| File | Usage |
| --- | --- |
| `Assets/Audio/newgame.wav` | New game/start sound. |
| `Assets/Audio/morte.wav` | Death sound. |
| `Assets/Audio/MammaMiaPizzeria.wav` | Game-over/static screen sound. |
| `Assets/Audio/walking.wav` | Walking loop/effect. |
| `Assets/Audio/jump.wav` | Jump sound. |
| `Assets/Audio/menu.wav` | Looping menu music. |
| `Assets/Audio/hammer.wav` | Hammer swing sound. |
| `Assets/Audio/press.wav` | Menu/option selection sound. |
| `Assets/Audio/back.wav` | Back/return sound. |

Some audio files may exist in the directory without being referenced by the current code. Before deleting an asset, search the source and documentation for its file name.

## Bitmap assets

Bitmap assets are PNG files grouped by role:

| Directory | Usage |
| --- | --- |
| `Assets/Bitmaps/Barrel/` | Barrel sprites, falling frames, deletion effect. |
| `Assets/Bitmaps/Cutscene/` | Kong/heart cutscene frames. |
| `Assets/Bitmaps/Kong/` | Kong gameplay animation frames. |
| `Assets/Bitmaps/Menu/` | Main menu, options, and credits screens. |
| `Assets/Bitmaps/Other/` | Fire/oilcan visuals. |
| `Assets/Bitmaps/Peach/` | Peach sprite. |
| `Assets/Bitmaps/Player/` | Player movement, jump, fall, climb, and hammer sprites. |
| `Assets/Bitmaps/Tiles/` | Tile sprites for ladders and ground. |
| `Assets/Bitmaps/*.png` | Shared UI/static images such as icon, hammer, life, victory, and death screens. |

## Font assets

The score font is loaded from:

```text
Assets/Fonts/slkscr.ttf
```

If replacing the font, keep the same path or update both source references and documentation.

## Map files

Levels are stored as text files:

```text
Assets/Maps/level0.txt
Assets/Maps/level1.txt
Assets/Maps/level2.txt
Assets/Maps/level3.txt
Assets/Maps/level4.txt
```

The game loads maps by level number using the pattern:

```text
../Assets/Maps/level<level>.txt
```

`level0.txt` is used for cutscene drawing. Gameplay levels start from `level1.txt`.

## Map format

Each map file starts with two integers:

```text
<rows> <columns>
```

The current gameplay maps use:

```text
28 25
```

The header is followed by `rows × columns` tile values. Existing tile values are:

| Value | Meaning | Rendered as |
| ---: | --- | --- |
| `0` | Empty space | Nothing/black background. |
| `1` | Ladder | `Assets/Bitmaps/Tiles/scala.png` |
| `2` | Ground/platform | `Assets/Bitmaps/Tiles/ground.png` |

Example beginning of a map:

```text
28 25
0 0 0 0 0 0 0 1 0 1 ...
...
```

Whitespace is flexible because the map is read with stream extraction, but each map should contain exactly the declared number of integers after the header.

## Coordinate conventions

- The tile size is `20 × 20` pixels.
- Entity positions are stored in pixels and converted to grid cells by dividing by `20`.
- The visible playfield is `500 × 560` pixels.
- Current maps are `25` columns wide and `28` rows tall.

## Safe level-editing checklist

Before adding or changing a level:

- [ ] Keep the header dimensions accurate.
- [ ] Ensure the number of tile values matches the header.
- [ ] Use only tile values understood by the renderer and movement logic.
- [ ] Preserve reachable routes from the player spawn to the level goal.
- [ ] Test ladder alignment carefully; climbing depends on tile alignment.
- [ ] Test barrel paths; barrels react to platforms, empty space, and ladders.
- [ ] Run the game from `build/` so map paths resolve.

## Asset-editing checklist

Before replacing or renaming assets:

- [ ] Search source files for the exact file name.
- [ ] Preserve case-sensitive names unless source references are updated.
- [ ] Keep image dimensions compatible with existing drawing positions where possible.
- [ ] Keep audio in a format supported by Allegro's configured audio codec add-on.
- [ ] Verify the game starts, the menu renders, a gameplay level renders, and relevant sounds play.

## Adding new asset categories

If a new category is added under `Assets/`, document:

1. The directory path.
2. The supported file types.
3. Which game system loads the files.
4. Any naming convention or frame-order convention.
5. Any build or packaging impact.

