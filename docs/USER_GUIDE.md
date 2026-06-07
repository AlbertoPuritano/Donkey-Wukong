# User guide

This guide explains how to start the game, navigate menus, and play.

## Starting the game

Build and run with:

```sh
make run
```

The game opens an Allegro fullscreen window and hides the mouse cursor while running.

## Main menu

Use the keyboard to navigate the main menu.

| Key | Action |
| --- | --- |
| Up / Down | Move the menu selection. |
| Enter | Confirm the selected menu item. |
| Escape | Leave the menu and quit. |

The menu entries map to these actions:

1. Start a new game.
2. Open options.
3. Show credits/static information screen.
4. Exit.

## Gameplay objective

Guide the player through each level while avoiding rolling barrels. Reach Peach or the level-specific goal to clear the stage. The game starts with three lives and advances through the available levels until all lives are lost or the final level is completed.

## In-game controls

| Key | Action |
| --- | --- |
| Left / Right | Move horizontally. |
| Up / Down | Climb ladders when aligned with one. |
| Space | Jump. |
| Left Shift | Swing the hammer while carrying it. |
| Escape | Exit the current run and return to the post-game flow. |
| Tab | Skip the current level. This is a built-in level-skip shortcut useful for testing. |

## Hammer behavior

A hammer appears in the level for a limited time. When collected:

- The player can attack barrels with Left Shift.
- Hammer hits award points.
- The hammer expires after its timer runs out.
- Some movement actions are restricted while carrying or swinging the hammer.

## Scoring

The game awards points for these actions:

| Action | Points |
| --- | ---: |
| Jumping over a barrel | 100 |
| Destroying a barrel with the hammer | 300 |

The current score is displayed during gameplay.

## Lives and level completion

- The player starts a new game with three lives.
- Colliding with a barrel causes a death sequence and removes one life.
- Clearing a level advances to the next level after a short cutscene.
- Completing all levels shows the victory screen.
- Losing all lives shows the death/game-over screen.

## Options menu

Use the options menu to adjust game settings.

| Key | Action |
| --- | --- |
| Up / Down | Move between option rows. |
| Left / Right | Change difficulty when the difficulty row is selected. |
| M | Toggle muted/unmuted audio. |
| Enter | Confirm back/return when the return row is selected. |
| Escape | Return to the main menu. |

Difficulty affects how frequently Kong throws barrels. The exact timing is controlled by the game logic.

## Static screens and cutscenes

Credits, victory, defeat, and cutscene screens wait for keyboard input or timed animation steps depending on the screen. Press a key on static screens to return.

## Troubleshooting while playing

### No assets, missing images, or missing sounds

Run the game with:

```sh
make run
```

Avoid launching the executable directly from the repository root unless the working directory is set to `build/`.

### No audio

Check that Allegro audio and audio codec add-ons are installed. Also verify that the game is not muted in the options menu.

### Keyboard input does not work

Make sure the game window has focus. On macOS, launching from an IDE or terminal may require granting accessibility/input permissions depending on system settings.

