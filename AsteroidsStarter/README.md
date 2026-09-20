# Asteroids — Starter Skeleton

A structural starting point for Assignment 3. It shows the required
inheritance / abstract-class / polymorphism layout with declarations (`.h`)
separated from definitions (`.cpp`). Fill in the `TODO`s and tune the physics.

## Files

| File            | What it is                                             |
|-----------------|--------------------------------------------------------|
| `Rigidbody.h/.cpp` | Abstract base class. Pure virtual `Draw()` = 0.     |
| `Asteroid.h/.cpp`  | `: public Rigidbody`. Adds scale, spin, sprite.     |
| `Ship.h/.cpp`      | `: public Rigidbody`. Adds thrust + keyboard input. |
| `MainGame.cpp`     | Only 3 functions: Entry / Update / Exit.            |

## Setup (recommended: Visual Studio 2022 Community, free)

1. New project → **Empty Project (C++)**.
2. Add the **PlayBuffer** framework to the project: `Play.h` and `Play.cpp`
   (get them from the PlayBuffer repo). PlayBuffer is a single-header C++
   game framework — it *is* the "Playbuffer"/`Play.h` the assignment refers to.
3. Add these 7 source files to the project.
4. Download `ship.png` and `asteroid.png` and put them in `data/sprites/`.
5. Build & run (F5).

> The email says "VS code 2022" but means **Visual Studio 2022** — PlayBuffer
> is built around Visual Studio's project setup, which is far smoother for a
> first-time C++ user than configuring VS Code by hand.

## Notes / verify before submitting

- API names (`Play::KEY_LEFT`, `Play::GetSpriteId`, `Play::DrawSpriteRotated`,
  `Play::Point2D`, `Play::Vector2D`) follow the current PlayBuffer API — if your
  copy of `Play.h` differs, adjust the calls. Check `Play.h` lines ~133–157 for
  the exact `Point2D` / `Vector2D` names (the brief points you there).
- Remove the `LoadBackground(...)` line if you don't add a background image.
- Don't commit binaries (`.exe`, `.pdb`) or temp files to GitHub.
