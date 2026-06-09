# Contributing

Thank you for considering contributing to the Elysian Physics Engine.

## How to Contribute

1. **Fork** the repository.
2. **Create a feature branch** (`git checkout -b feature/my-feature`).
3. **Make your changes** — follow the existing code style (no comments in source, use the `elysian` namespace).
4. **Ensure it builds** with your changes (`cmake -B build && cmake --build build`).
5. **Commit** with a clear, descriptive message.
6. **Push** to your fork and open a pull request.

## Code Style

- C++20
- No comments in source code
- Namespace `elysian`
- PascalCase for classes and methods, camelCase for parameters and local variables
- Use the existing macros and utilities (`CMP`, `CLAMP`) where applicable

## Reporting Issues

Report bugs and suggest features by opening a GitHub issue. Include:
- A minimal reproduction case or description
- Your compiler and OS
- The expected vs actual behavior
