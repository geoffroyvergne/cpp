# Mario NES

A small NES-style Mario game prototype written in C++20 with CMake and SDL2.

## Current milestone

Step 1 + Step 2:

- CMake project
- SDL2 initialization
- SDL window
- Main game loop
- InputManager
- Renderer abstraction
- Fixed 256x240 logical game resolution
- ESC / window close to quit
- Empty blue game screen

## Dependencies

SDL2 and pkg-config are required.

### macOS (Homebrew)

```bash
brew install sdl2 pkg-config
```

### Ubuntu / Debian

```bash
sudo apt install libsdl2-dev pkg-config
```

## Build

From the project root:

```bash
cmake -S . -B build
cmake --build build -j
```

Run:

```bash
./build/mario_nes
```

On macOS, the executable is normally:

```bash
./build/mario_nes
```

Press `ESC` or close the window to exit.

## Architecture

```text
src/
├── main.cpp
├── core/
│   ├── Game.h
│   └── Game.cpp
├── graphics/
│   ├── Renderer.h
│   └── Renderer.cpp
└── input/
    ├── InputManager.h
    └── InputManager.cpp
```

The intended dependency direction is:

```text
main
  ↓
Game
  ├── InputManager
  └── Renderer
```

Gameplay systems will be added later without putting SDL calls into game entities.
