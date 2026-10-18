# Local HTTP Server

**Educational HTTP server - NOT production-ready**

## Features
- Bind to 127.0.0.1 only (localhost)
- Serve static HTML response
- Basic HTTP/1.0 parsing
- Request logging
- Safe error handling

## Security Limitations
- Educational implementation only
- Limited HTTP subset
- No TLS/HTTPS
- No authentication
- Path traversal protection basic
- Request size limits basic

## Build & Run
```bash
cmake --build build --target http_server
./build/projects/12-local-http-server/http_server
```

## Test
```bash
./build/projects/12-local-http-server/http_test
```

## Usage
Server runs on http://127.0.0.1:8080
Test with: `curl http://localhost:8080/`

## Concepts
- Socket programming (platform-specific)
- HTTP basics
- Network I/O
- String parsing
