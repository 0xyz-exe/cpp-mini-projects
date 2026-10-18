# Basic Calculator

Console calculator supporting basic arithmetic operations.

## Features
- Addition, subtraction, multiplication, division
- Modulo for floating-point numbers
- Division-by-zero detection
- Input validation
- Repeatable calculations

## Build
```bash
cmake -B build -G Ninja
cmake --build build --target calculator
```

## Run
```bash
./build/projects/01-basic-calculator/calculator
```

## Test
```bash
./build/projects/01-basic-calculator/calculator_test
```

## Concepts
- Basic I/O with iostream
- Error handling
- Input validation with cin.fail()
- Switch statements
