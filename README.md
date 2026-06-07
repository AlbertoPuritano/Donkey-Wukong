# Donkey Wukong

"Donkey Kong"-like game developed in 2019 by Alberto Puritano and Giuseppe Moscato as a project for the Object-Oriented Programming course.

## Documentation

Project documentation is available in [`docs/README.md`](docs/README.md):

- [`docs/BUILDING.md`](docs/BUILDING.md) for build, run, dependency, and troubleshooting details.
- [`docs/USER_GUIDE.md`](docs/USER_GUIDE.md) for menu navigation, controls, scoring, and gameplay notes.
- [`docs/ARCHITECTURE.md`](docs/ARCHITECTURE.md) for the source layout and runtime architecture.
- [`docs/ASSETS_AND_LEVELS.md`](docs/ASSETS_AND_LEVELS.md) for asset organization and map editing rules.
- [`CONTRIBUTING.md`](CONTRIBUTING.md) for contribution and validation guidelines.

## Build and run

This project uses the Allegro 5 game programming library. The build is handled
by a small `Makefile` that discovers compiler and linker flags through
`pkg-config`.

### Requirements

- `make`
- a C++ compiler with C++11 support
- `pkg-config`
- Allegro 5 development files providing these `pkg-config` modules:
  - `allegro_main-5`
  - `allegro-5`
  - `allegro_font-5`
  - `allegro_ttf-5`
  - `allegro_image-5`
  - `allegro_audio-5`
  - `allegro_acodec-5`

You can check whether the required Allegro modules are visible with:

```sh
pkg-config --exists \
  allegro_main-5 \
  allegro-5 \
  allegro_font-5 \
  allegro_ttf-5 \
  allegro_image-5 \
  allegro_audio-5 \
  allegro_acodec-5
```

If that command exits successfully, the project should be buildable with the
included `Makefile`.

### Dependency installation examples

Package names vary by operating system and distribution. Common examples:

```sh
# macOS, using Homebrew
brew install pkg-config allegro
```

```sh
# Debian/Ubuntu
sudo apt install build-essential make pkg-config liballegro5-dev
```

For other systems, install the Allegro 5 development package from your package
manager and make sure the `pkg-config` modules listed above are available.

### Build

From the project root:

```sh
make
```

The executable is created at `build/donkey-wukong`.

### Run

```sh
make run
```

The `run` target starts the executable from the `build/` directory because the
game loads assets through relative paths such as `../Assets/...`.

### Clean

```sh
make clean
```
