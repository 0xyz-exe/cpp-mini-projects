# Number Guessing Game

Guess the randomly generated number with hints.

## Features
- Random number generation using <random>
- Configurable difficulty levels
- Higher/lower hints
- Attempt counter
- Replay option

## Build & Run
```bash
cmake --build build --target guessing_game
./build/projects/02-number-guessing-game/guessing_game
```

## Test
```bash
./build/projects/02-number-guessing-game/guessing_test
```

## Concepts
- std::random_device, std::mt19937
- std::uniform_int_distribution
- Game loop logic
