# Security Policy

## Reporting Vulnerabilities

If you discover a security issue, please:
1. **Do NOT** open a public issue
2. Email details to repository maintainers
3. Allow time for fixes before disclosure

## Educational Disclaimer

This repository contains **educational implementations**. Projects labeled as educational are NOT intended for production use.

## Known Limitations

### Project 07 - Password Generator
- Uses `std::random_device` and `std::mt19937`
- **NOT cryptographically secure**
- For learning only
- Production systems should use:
  - Windows: `BCryptGenRandom`
  - Linux: `/dev/urandom` or `getrandom()`

### Project 08 - File Organizer
- Basic path traversal check
- Dry-run mode by default
- User confirmation required
- Does not follow symlinks outside target directory

### Project 12 - Local HTTP Server
- Educational implementation
- Binds to 127.0.0.1 only (localhost)
- Limited HTTP/1.0 subset
- No TLS/HTTPS
- No authentication
- Basic input validation
- Request size limits
- **NOT production-ready**

### General Security Practices

All projects follow:
- Input validation at trust boundaries
- Proper error handling
- No hardcoded credentials
- Safe file operations
- Const-correctness
- RAII for resource management

## Secure Coding Checklist

When contributing:
- [ ] Validate all user input
- [ ] Handle errors explicitly
- [ ] Use RAII for resources
- [ ] Avoid buffer overflows
- [ ] Check array bounds
- [ ] Use smart pointers
- [ ] Document security assumptions
- [ ] Add warnings for educational code

## Dependencies

This project uses only standard C++17 library and OS APIs. No external dependencies minimizes supply chain risks.
