# File Organizer

Organize files by extension into category folders.

## Features
- Organize by file extension
- Dry-run mode (preview only, default)
- Collision detection
- Safe error handling
- Explicit confirmation before moving

## Build & Run
```bash
cmake --build build --target file_organizer
./build/projects/08-file-organizer/file_organizer
```

## Test
```bash
./build/projects/08-file-organizer/organizer_test
```

## Safety
- Dry-run by default (preview changes)
- Never overwrites files
- Skips inaccessible files
- User must confirm execution

## Concepts
- Filesystem operations (C++17 <filesystem>)
- Path manipulation
- Error handling with exceptions
- Safe file operations
