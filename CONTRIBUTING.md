# Contributing

Thank you for helping improve Donkey Wukong. This guide describes the expected workflow for code, asset, and documentation changes.

## Scope of the project

Donkey Wukong is a C++11/Allegro 5 arcade game. Contributions should preserve the existing gameplay style and keep the repository easy to build for students and maintainers.

## Before making changes

1. Read `README.md` for quick setup.
2. Read `docs/BUILDING.md` for the full build and runtime working-directory details.
3. For gameplay or source changes, read `docs/ARCHITECTURE.md`.
4. For asset or map changes, read `docs/ASSETS_AND_LEVELS.md`.
5. For control or player-facing behavior changes, read `docs/USER_GUIDE.md`.

## Development workflow

Use small, focused changes. A typical workflow is:

```sh
git status --short
make
make run
```

After validating your change, check the working tree again:

```sh
git status --short
```

## Build validation

Before submitting changes that affect source, build files, assets, or maps:

- [ ] `make` succeeds from the repository root.
- [ ] `make run` starts the game from the expected working directory.
- [ ] The main menu renders correctly.
- [ ] At least one gameplay level starts correctly.
- [ ] Relevant audio, image, font, and map assets load correctly.
- [ ] `make clean` removes generated build output.

If CMake build files are present in your checkout, also validate the documented CMake workflow in `docs/BUILDING.md`.

## Documentation expectations

Update documentation in the same change when behavior changes:

| Change type | Documentation to update |
| --- | --- |
| Build commands, dependencies, output paths | `README.md`, `docs/BUILDING.md` |
| Controls, scoring, menus, options | `docs/USER_GUIDE.md` |
| Architecture, class responsibilities, runtime flow | `docs/ARCHITECTURE.md` |
| Assets, map format, file naming, level rules | `docs/ASSETS_AND_LEVELS.md` |
| Contribution process | `CONTRIBUTING.md` |

Documentation should describe what is true in the repository. Avoid documenting planned behavior as if it already exists.

## Source style guidance

The existing code uses a compact C++ style and Allegro C APIs. When changing code:

- Prefer minimal, targeted edits over broad rewrites.
- Keep public class interfaces stable unless the change requires an interface update.
- Keep source and header changes synchronized.
- Be careful with raw pointers and Allegro resource ownership.
- Avoid reformatting unrelated code.
- Keep asset paths and level-number assumptions consistent with documentation.

## Asset contribution guidance

When adding or replacing assets:

- Use file names that are stable and easy to reference from source.
- Preserve case-sensitive file names where possible.
- Place files in the existing category directories under `Assets/`.
- Avoid committing generated editor metadata or OS-specific files.
- Verify assets load on a clean build/run.

## Level contribution guidance

When editing `Assets/Maps/*.txt`:

- Keep the first line dimensions accurate.
- Keep tile values limited to those supported by the code unless the renderer and movement logic are also updated.
- Test player traversal, ladder behavior, barrel movement, scoring opportunities, and level completion.

## Commit guidance

Use clear, descriptive commit messages. Examples:

```text
docs: add gameplay controls guide
build: update Allegro dependency notes
assets: replace player jump sprite
level: adjust level 2 ladder layout
```

## Review checklist

Reviewers should check:

- The change matches the stated goal.
- Build/run instructions still work.
- Runtime asset paths are still valid.
- Documentation and behavior are consistent.
- Generated files, IDE files, and local build artifacts are not included.

