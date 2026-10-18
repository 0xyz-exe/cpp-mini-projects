# JSON Mini Parser

Parse and display JSON structures.

## Features
- null, boolean, number, string, array, object
- Escape sequence handling
- Nested structures
- Pretty printing
- Basic error detection

## Build & Run
```bash
cmake --build build --target json_parser
./build/projects/13-json-mini-parser/json_parser
```

## Test
```bash
./build/projects/13-json-mini-parser/json_test
```

## Limitations
- Single-line input
- Limited error messages
- No Unicode escapes
- Basic number parsing

## Concepts
- Recursive descent parsing
- Smart pointers
- Polymorphic data structures
- String escaping
