# Asteroids — C++ / PlayBuffer

A simple **Asteroids-style arcade game developed in C++ using the PlayBuffer framework**.

This project was created for **Assignment 3: Asteroids**, with a focus on demonstrating **inheritance, abstract classes, polymorphism, dynamic allocation, physics simulation, and collision detection**.

## Overview

The game features a player-controlled spaceship and multiple asteroids moving around the screen.

The player can:

- Rotate the spaceship using the **Left** and **Right Arrow** keys.
- Apply thrust using the **Spacebar**.
- Move around the game area with physics-based movement.
- Collide with asteroids, which resets the spaceship to its starting position.
- Observe asteroids moving with randomized velocities, scales, and rotation speeds.
- Exit the game using the **Escape** key.

The assignment requires game objects to be implemented using inheritance and polymorphism rather than PlayBuffer GameObjects.

## Technologies

- **C++ (C++17)**
- **PlayBuffer**
- **VS Code + MSYS2 / MinGW (g++)** — also builds with **Visual Studio 2022**
- Object-Oriented Programming
- Inheritance
- Abstract Classes
- Polymorphism
- Dynamic Memory Allocation
- Basic 2D Physics
- Collision Detection

## Project Structure

```text
asteroids-cpp-playbuffer/
│
├── .vscode/                 # VS Code build/debug configuration
│   ├── tasks.json           #   Build Asteroids / Run Asteroids tasks
│   ├── launch.json          #   F5 debug configuration (gdb)
│   ├── c_cpp_properties.json
│   └── settings.json
│
├── data/
│   └── sprites/
│       ├── asteroid.png
│       └── ship.png
│
├── Rigidbody.h              # Abstract base class
├── Rigidbody.cpp
├── Asteroid.h               # : public Rigidbody
├── Asteroid.cpp
├── Ship.h                   # : public Rigidbody
├── Ship.cpp
├── MainGame.cpp             # Entry / Update / Exit (only 3 functions)
│
├── Play.h                   # PlayBuffer framework (single header)
├── Play.cpp                 # PlayBuffer implementation shim
│
├── build.bat                # Command-line build (MSYS2/MinGW)
├── .gitignore
└── README.md
```

## Class Design

The project uses `Rigidbody` as the abstract base class for physical game objects.

### Rigidbody

`Rigidbody` is the abstract base class containing the common physics properties and behaviour shared by game objects.

It contains:

- Position
- Velocity
- Acceleration
- Rotation
- Collision radius

It also provides virtual functions for:

- `Simulate()`
- `Collide()`
- `Draw()`

`Draw()` is a pure virtual function, making `Rigidbody` an abstract class.

```text
              Rigidbody
              (Abstract)
                  │
          ┌───────┴───────┐
          │               │
       Ship           Asteroid
```

### Asteroid

`Asteroid` inherits from `Rigidbody`.

Additional properties include:

- Sprite identifier
- Scale
- Rotation speed

Asteroids are initialized with randomized:

- Velocity
- Scale
- Rotation speed

The `Simulate()` method extends the base physics simulation by applying rotational movement.

### Ship

`Ship` also inherits from `Rigidbody`.

Additional properties include:

- Thrust
- Sprite identifier

The ship responds to keyboard input:

| Key | Action |
|---|---|
| Space | Apply thrust |
| Left Arrow | Rotate left |
| Right Arrow | Rotate right |
| Escape | Exit game |

When the ship collides with an asteroid, its position, velocity, acceleration, and rotation are reset.

## Polymorphism

The game stores all game objects through `Rigidbody*` pointers.

```cpp
Rigidbody** g_rigidbody;
```

The collection contains both the player ship and asteroids.

The game loop calls:

```cpp
g_rigidbody[i]->Simulate(elapsedTime);
g_rigidbody[i]->Draw();
```

Because these functions are virtual, C++ dynamic dispatch automatically calls the appropriate implementation for the actual object.

For example:

```text
Rigidbody pointer
       │
       ├── Ship
       │     └── Ship::Simulate()
       │
       └── Asteroid
             └── Asteroid::Simulate()
```

This demonstrates runtime polymorphism.

## Physics

The game uses a simple frame-independent physics simulation.

Each frame, the object's:

1. Position is updated using velocity.
2. Velocity is updated using acceleration.
3. Acceleration is reset.

Conceptually:

```text
position += velocity × timeStep
velocity += acceleration × timeStep
acceleration = 0
```

The `timeStep` is based on the elapsed time supplied by the game update function, helping keep movement independent of frame rate.

## Collision Detection

Collision detection uses a simple circle-to-circle approach.

Each `Rigidbody` has a collision radius.

Two objects are considered colliding when the distance between their centres is less than the sum of their radii.

```text
distance < radius1 + radius2
```

When a collision occurs, the objects' `Collide()` methods are called through `Rigidbody*` pointers.

The `Ship` class uses polymorphism and type checking to determine whether the object it collided with is an `Asteroid`.

## Screen Wrapping

Objects that move beyond the edge of the screen wrap around to the opposite side.

For example:

```text
             Screen
     ┌─────────────────────┐
     │                     │
     │      ASTEROID       │
     │                     │
     │                     │
     └─────────────────────┘
             ▲
             │
        leaves screen
             │
             ▼
        reappears
        on opposite side
```

This behaviour is implemented in the base `Rigidbody` physics simulation so that both the ship and asteroids can use it.

## Getting Started (VS Code + MSYS2 — recommended)

Follow these steps to build and run the game from source after cloning. No
executable is committed to the repo — each developer builds their own `Asteroids.exe`.

### 1. Prerequisites (one-time per machine)

1. **MSYS2** — install from <https://www.msys2.org>. Then open the
   **MSYS2 UCRT64** terminal and install the compiler (and gdb for debugging):

   ```bash
   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb
   ```

2. **Visual Studio Code** with the **C/C++ extension** (`ms-vscode.cpptools`).

> The build expects the compiler at `C:\msys64\ucrt64\bin\g++.exe`.
> If your MSYS2 is installed elsewhere, update that path in `build.bat` and in the
> four `.vscode` files: `tasks.json`, `launch.json`, `settings.json`,
> `c_cpp_properties.json`.

### 2. Clone the repository

```bash
git clone <repository-url>
```

### 3. Open the project in VS Code

Open the cloned repository folder in VS Code (File → Open Folder → select the
project folder). All source files, the `.vscode` build tasks, and `data/sprites/`
are at the root, so everything works out of the box.

### 4. Build

Press **Ctrl+Shift+B** (runs the **Build Asteroids** task). This compiles every
`.cpp` file into `Asteroids.exe`.

### 5. Run

Use **Terminal → Run Task → Run Asteroids**, or type in the VS Code terminal:

```bash
./Asteroids.exe
```

### 6. Debug (optional)

Press **F5** to build a debug version (`Asteroids_debug.exe`) and step through the
code with breakpoints (requires gdb from the prerequisites).

### Alternative: build from the command line

Double-click **`build.bat`** (or run it from a terminal) to produce `Asteroids.exe`
without VS Code.

### Alternative: Visual Studio 2022

1. Install **Visual Studio 2022** with the C++ development workload.
2. Create an **Empty C++ project** and add: `MainGame.cpp`, `Rigidbody.cpp/.h`,
   `Ship.cpp/.h`, `Asteroid.cpp/.h`, `Play.cpp/.h`.
3. Ensure `data/sprites/ship.png` and `data/sprites/asteroid.png` are present.
4. Build and run (F5).

> Note: `Play.h` in this repo contains a one-line MinGW-compatibility fix. It still
> builds cleanly under Visual Studio 2022.

## Controls

| Key | Function |
|---|---|
| **Space** | Thrust |
| **Left Arrow** | Rotate counter-clockwise |
| **Right Arrow** | Rotate clockwise |
| **Escape** | Exit |

## Assignment Requirements Addressed

The implementation follows the major structural requirements of the assignment:

- Abstract `Rigidbody` base class
- `Asteroid` derived class
- `Ship` derived class
- Virtual functions
- Pure virtual drawing function
- Inheritance
- Runtime polymorphism
- Dynamic allocation of rigid bodies
- Physics simulation
- Collision detection
- Randomized asteroid movement
- Separate `.h` and `.cpp` files
- Three functions in `MainGame.cpp`

## Assets

The project uses:

- `ship.png`
- `asteroid.png`

These sprites are stored in:

```text
data/sprites/
```

The assignment specifies that sprites should be placed in the `data/sprites` folder.

## Important

Build and test the project before submission.

The assignment specifically recommends cloning the repository again into a separate folder after pushing to GitHub and verifying that the project compiles and runs correctly.

Do **not** commit generated binaries or temporary files such as:

```text
*.exe
*.pdb
*.obj
```

A `.gitignore` file should be used to prevent these files from being committed.
