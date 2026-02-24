# Assignment 1 - Points2D

Neessam Moustafa

## What I did

I implemented the full Points2D class in points2d.h. This includes the big five (destructor, copy constructor, copy assignment, move constructor, move assignment), the one-parameter constructor, size(), operator<<, operator>>, operator+, and operator[]. Everything from Part 1 and Part 2 is done.

For copy assignment I used the copy-and-swap idiom like the assignment suggested. For move assignment I used std::swap on both members. operator+ handles different sized sequences by appending the leftover points from whichever sequence is longer. operator[] calls abort() if the index is out of bounds. operator>> reads the size first then the coordinate pairs, and prints ERROR to cerr and aborts on bad input.

## Bugs

Had an issue where operator>> was reading directly from the input stream with >>, which skips newlines and reads across line boundaries. If a line didn't have enough coordinates, it would steal data from the next line and mess up every read after that. Fixed it by reading one full line with getline into a stringstream and parsing from there instead.

Also double checked operator<< formatting since the autograder is picky — made sure there's no trailing space after the last point, empty sequences print as (), and every output ends with endl.

## How to run

make clean
make all
./test_points2d < test_input_file.txt

## Files

Input: test_input_file.txt
Expected output: expected_output.txt