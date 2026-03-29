# edgas
Event-Driven Molecular Dynamics Gas Simulator in 2D


## Building the project

Configure the project in a subdirectory `build`:

```bash
cmake -S . -B build
```

Build the project and it's unit-tests:

```bash
cmake --build build
```

Run unit tests:

```bash
ctest --test-dir build
```
