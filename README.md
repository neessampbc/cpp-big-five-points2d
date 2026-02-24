# Points2D: C++ Memory Management & Move Semantics

A template class that manages a dynamically allocated sequence of 2D points using raw pointers. Built to practice manual memory management in C++ without relying on STL containers like `std::vector`.

## Concepts Demonstrated

- **Rule of Five** — destructor, copy constructor, copy assignment, move constructor, move assignment all manually implemented
- **Copy-and-swap idiom** for exception-safe copy assignment
- **Move semantics** — move constructor zeroes out the source, move assignment uses `std::swap` so the source receives the old data
- **Operator overloading** — `<<`, `>>`, `+`, `[]`
- **Template programming** — works with `int`, `double`, or any arithmetic type
- **Raw pointer management** — `new[]` / `delete[]` with no smart pointers or containers

## Build & Run

```
make clean
make all
./test_points2d < test_input_file.txt
```

## Example

Given input `3 7 4 5 19 2 3`, the program reads 3 points and stores them as `(7, 4) (5, 19) (2, 3)`. Supports element-wise addition of sequences with different sizes — extra points from the longer sequence are appended unchanged.

## Files

| File | Description |
|------|-------------|
| `points2d.h` | Template class implementation (header-only) |
| `test_points2d.cc` | Test driver exercising all operations |
| `test_input_file.txt` | Sample input data |
| `expected_output.txt` | Reference output for verification |
