# Contributing to C++ Mini Projects

Thank you for considering contributing!

## Code Standards

### C++ Style
- C++17 standard
- Modern STL usage
- RAII principles
- Clear naming conventions
- Comments for complex logic

### Formatting
- 4 spaces indentation
- 100 character line limit
- Opening brace on same line
- Consistent spacing

### Safety
- Input validation at boundaries
- Proper error handling
- No memory leaks
- Thread-safe when concurrent
- Security warnings where applicable

## Adding a New Project

1. Create `projects/XX-project-name/` directory
2. Add `main.cpp`, `test.cpp`, `CMakeLists.txt`, `README.md`
3. Update root `CMakeLists.txt`
4. Add entry to main README catalog
5. Write tests
6. Verify build and tests pass

## Pull Request Process

1. Fork the repository
2. Create feature branch
3. Make changes with clear commits
4. Add/update tests
5. Run full test suite
6. Update documentation
7. Submit PR with description

## Testing Requirements

- All projects must have tests
- Tests must pass on Windows and Linux
- Use CTest framework
- Test normal and error cases

## Documentation

- Every project needs a README
- Include build/run instructions
- Document key concepts
- Note limitations
- Add security warnings if applicable
