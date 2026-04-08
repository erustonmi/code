# Calendar Solver

This project is a C++ application for solving calendar-based puzzles. It is organized with CMake and includes modular source files for blocks and boards, as well as unit tests.

## Project Structure

- main.cpp — Test entry point for the application
- src/ — Source files for core logic
  - block.cpp, block.h — Block logic
  - board.cpp, board.h — Board logic
  - colormod.h — Color utilities
- test/ — Unit tests
  - block.t.cpp - Entry point to the calendar puzzle solver
- CMakeLists.txt — Build configuration

## Building

This project uses CMake for building. To build the project:
cd to cpp/calendar
```sh
cmake -S .
make
```
## Running
```sh
mj@DESKTOP-VICT:~/code/cpp/calendar$ test/blockTest
provide month(first 3 letter, eg. jan for January, feb for Feburary, etc), day, day of the week(first 3 letter, eg. mon for Monday, etc)
```
mj@DESKTOP-VICT:~/code/cpp/calendar$ test/blockTest apr 7 tue
initial board:
+++X++X
++++++X
++++++X
+++++++
+++++++
+++++++
+++++X+
XXXX+++

solved
...

## License

[Specify your license here]
