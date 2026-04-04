# AGENTS.md

## Project

C++ Event-Driven Molecular Dynamics (EDMD) simulator.
This project implements a simulation of an idealized gas in 2D using hard spheres model.
This project is experimental and under active development.

## Build & Run

The project uses CMake.
Use the provided dev script:

* Configure: `./dev conf`
* Build: `./dev build`
* Test: `./dev test`

## Code Structure

* `src/` — main source code of the project
* `test/` — unit tests using Google Testing Framework (GTest)
* `CMakeLists.txt` — build configuration

## Code style notes

* Prefer simple and minimal code
* Avoid unecessary abstractions
