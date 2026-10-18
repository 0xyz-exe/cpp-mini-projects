# Text File Analyzer

Analyze text files for word/line/character counts and frequency.

## Features
- Count lines, words, characters
- Word frequency analysis
- Case-insensitive matching
- Punctuation stripping
- Top 10 most common words
- UTF-8 support (byte-level)

## Build & Run
```bash
cmake --build build --target text_analyzer
./build/projects/09-text-analyzer/text_analyzer
```

## Test
```bash
./build/projects/09-text-analyzer/analyzer_test
```

## Word Processing Rules
- Alphanumeric characters only (punctuation stripped)
- Case-insensitive (converted to lowercase)
- Empty tokens ignored

## Concepts
- File I/O
- String streams
- Maps for frequency counting
- Sorting with custom comparators
- Character classification
