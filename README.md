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

- **C++**
- **PlayBuffer**
- **Visual Studio 2022**
- Object-Oriented Programming
- Inheritance
- Abstract Classes
- Polymorphism
- Dynamic Memory Allocation
- Basic 2D Physics
- Collision Detection

## Project Structure

```text
Asteroids/
│
├── data/
│   └── sprites/
│       ├── asteroid.png
│       └── ship.png
│
├── Asteroid.h
├── Asteroid.cpp
│
├── Rigidbody.h
├── Rigidbody.cpp
│
├── Ship.h
├── Ship.cpp
│
├── MainGame.cpp
│
├── Play.h
├── Play.cpp
│
├── build.bat
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

## Building the Project

### Visual Studio 2022

1. Install **Visual Studio 2022** with the C++ development workload.
2. Open/create a C++ project.
3. Add the following source files:

```text
MainGame.cpp
Rigidbody.cpp
Rigidbody.h
Ship.cpp
Ship.h
Asteroid.cpp
Asteroid.h
Play.cpp
Play.h
```

4. Make sure the following sprites are available:

```text
data/sprites/ship.png
data/sprites/asteroid.png
```

5. Build the project.
6. Run the application.

### MinGW / MSYS2

A `build.bat` file is also included for building the project with MinGW.

The current batch file expects the compiler at:

```text
C:\msys64\ucrt64\bin\g++.exe
```

If MinGW is installed in another location, update the `GPP` path in `build.bat`.

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

## Author

**Hirantha Priyadarshana**

## Assignment

**Assignment 3 — Asteroids**

C++ / Object-Oriented Programming
