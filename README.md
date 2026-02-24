# Assignment 1 - Points2D

Neessam Moustafa

## What I did

I implemented the full Points2D class in points2d.h. This includes the big five (destructor, copy constructor, copy assignment, move constructor, move assignment), the one-parameter constructor, size(), operator<<, operator>>, operator+, and operator[]. Everything from Part 1 and Part 2 is done.

For copy assignment I used the copy-and-swap idiom like the assignment suggested. For move assignment I used std::swap on both members. operator+ handles different sized sequences by appending the leftover points from whichever sequence is longer. operator[] calls abort() if the index is out of bounds. operator>> reads the size first then the coordinate pairs, and prints ERROR to cerr and aborts on bad input.

## Bugs

Fixed operator<< formatting — each point now prints with a trailing space after the closing paren, matching what the autograder expects. Also fixed operator>> to only delete[] the old sequence if something was actually allocated.

## How to run

make clean
make all
./test_points2d < test_input_file.txt

## Files

Input: test_input_file.txt
Expected output: expected_output.txt