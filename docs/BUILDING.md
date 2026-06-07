# Build and development setup

Donkey Wukong is a C++11 project that uses the Allegro 5 game programming library for windowing, graphics, keyboard input, audio, fonts, and image loading.

## Supported build entry points

This checkout contains a `Makefile` build that uses `pkg-config` to discover Allegro compiler and linker flags. If a branch or future checkout also contains CMake build files, keep the CMake section below synchronized with the real `CMakeLists.txt` targets.

## Requirements

Install these tools before building:

- A C++ compiler with C++11 support.
- `make` for the Makefile workflow.
- `pkg-config`.
- Allegro 5 development files exposing these `pkg-config` modules:
  - `allegro_main-5`
  - `allegro-5`
  - `allegro_font-5`
  - `allegro_ttf-5`
  - `allegro_image-5`
  - `allegro_audio-5`
  - `allegro_acodec-5`

### macOS dependency example

Using Homebrew:

```sh
brew install pkg-config allegro
```

### Debian/Ubuntu dependency example

```sh
sudo apt update
sudo apt install build-essential make pkg-config liballegro5-dev
```

Package names can differ across distributions. If the package manager uses split Allegro packages, install the image, font, TTF, audio, and audio codec development packages as well.

## Verify dependencies

From the repository root:

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

No output and exit status `0` means the required modules are visible to `pkg-config`.

For diagnostic details, run:

```sh
pkg-config --cflags --libs \
  allegro_main-5 \
  allegro-5 \
  allegro_font-5 \
  allegro_ttf-5 \
  allegro_image-5 \
  allegro_audio-5 \
  allegro_acodec-5
```

## Makefile workflow

Build from the repository root:

```sh
make
```

This creates:

```text
build/donkey-wukong
```

Run the game through the Make target:

```sh
make run
```

The `run` target changes into `build/` before starting the executable. This is important because runtime asset paths are relative to `build/`.

Clean generated files:

```sh
make clean
```

## CMake workflow

If your checkout includes a `CMakeLists.txt`, use an out-of-source build directory so generated files do not mix with source files:

```sh
cmake -S . -B build
cmake --build build
```

Run the executable from `build/` unless the CMake configuration copies assets beside the executable or configures a different working directory:

```sh
cd build
./donkey-wukong
```

If the CMake target name or output executable name differs, update this guide and `README.md` at the same time.

## Runtime working directory

The game loads assets using paths like:

```text
../Assets/Bitmaps/...
../Assets/Audio/...
../Assets/Fonts/...
../Assets/Maps/...
```

That means the executable should be launched from `build/` in the current layout. Running `./build/donkey-wukong` from the repository root may fail to load assets because `../Assets` would point outside the repository.

## Common build problems

### `pkg-config is required but was not found`

Install `pkg-config` and ensure it is available on `PATH`.

### Missing Allegro modules

If the Makefile reports missing Allegro modules, verify Allegro development packages are installed and that `PKG_CONFIG_PATH` includes the directory containing Allegro `.pc` files.

Example diagnostic command:

```sh
pkg-config --list-all | grep allegro
```

### Asset loading failures at runtime

Symptoms include a blank screen, missing sprites, missing audio, or initialization failures around fonts/images/audio.

Check that:

1. You launched the game from `build/` or via `make run`.
2. The `Assets/` directory exists one level above the working directory.
3. File names and capitalization match exactly. This matters on case-sensitive file systems.

### Fullscreen/window issues

The current game creates a fullscreen Allegro display. If the display cannot be created, verify that the OS allows fullscreen windows for the terminal or IDE process starting the game.

## Validation checklist

Before submitting build-related changes:

- [ ] Dependency checks pass.
- [ ] `make` completes successfully.
- [ ] `make run` launches the game from the expected working directory.
- [ ] `make clean` removes generated build output.
- [ ] Documentation is updated if build commands, dependency names, or runtime paths change.

