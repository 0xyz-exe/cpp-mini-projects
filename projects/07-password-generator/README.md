# Password Generator

Generate random passwords with configurable character sets.

## Features
- Configurable length (8-64)
- Character set selection (upper/lower/digits/symbols)
- Input validation
- Exclusion options

## Build & Run
```bash
cmake --build build --target passgen
./build/projects/07-password-generator/passgen
```

## Test
```bash
./build/projects/07-password-generator/passgen_test
```

## Security Note
Uses `std::random_device` and `std::mt19937`. **NOT cryptographically secure**.
Educational use only. Production systems should use platform-specific secure RNG:
- Windows: `BCryptGenRandom`
- Linux/Unix: `/dev/urandom`

## Concepts
- Random number generation
- String manipulation
- Configuration validation
