# Project documentation

This directory contains the maintainer and player-facing documentation for **Donkey Wukong**, a C++/Allegro 5 arcade game inspired by Donkey Kong.

## Documentation index

- [Build and development setup](./BUILDING.md) — dependencies, build commands, run commands, clean builds, and troubleshooting.
- [User guide](./USER_GUIDE.md) — menu navigation, controls, gameplay goals, scoring, and options.
- [Architecture overview](./ARCHITECTURE.md) — source layout, runtime flow, main systems, and important implementation constraints.
- [Assets and levels](./ASSETS_AND_LEVELS.md) — asset organization, runtime path expectations, map format, and safe editing rules.
- [Contributing guide](../CONTRIBUTING.md) — contribution workflow, style expectations, validation checklist, and review guidance.

## Repository layout

```text
.
├── Assets/          # Audio, bitmap, font, and level-map resources loaded at runtime
├── Headers/         # C++ class declarations and shared constants
├── Source/          # C++ implementation files and entry point
├── build/           # Local build output; ignored by Git
├── docs/            # Project documentation
├── Makefile         # Make-based build entry point
└── README.md        # Quick project introduction and build summary
```

## Documentation principles

When updating documentation:

1. Keep commands copy-pasteable and show the working directory assumptions.
2. Prefer documenting observed behavior over desired future behavior.
3. Update the relevant guide whenever controls, assets, level format, dependencies, or build commands change.
4. Do not document source-level internals as public API unless maintainers are expected to rely on them.
5. Call out platform-specific behavior, especially around Allegro dependencies and runtime asset paths.

## Known runtime assumption

The game currently loads assets using paths relative to the executable working directory, such as `../Assets/...`. For that reason, documented run commands start the executable from `build/`, where `../Assets` resolves to the repository's `Assets/` directory.


