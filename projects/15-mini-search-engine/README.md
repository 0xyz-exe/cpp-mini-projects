# Mini Search Engine

Index and search text files with inverted index.

## Features
- Directory indexing
- Token extraction and normalization
- Inverted index
- Term frequency scoring
- Result ranking
- File excerpts
- Safe file handling

## Build & Run
```bash
cmake --build build --target search_engine
./build/projects/15-mini-search-engine/search_engine
```

## Test
```bash
./build/projects/15-mini-search-engine/search_test
```

## Safety
- User-specified directory only
- File size limits (1MB per file)
- No symbolic links
- No command execution
- Local only (no network)

## Concepts
- Inverted index data structure
- Text tokenization
- TF scoring
- File I/O at scale
- Result ranking
