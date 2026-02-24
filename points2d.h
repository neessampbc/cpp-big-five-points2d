// Neessam Moustafa
// Points2D: A template class that stores a dynamically allocated sequence of
// 2D points. Supports deep copy, move semantics, element-wise addition,
// and formatted I/O. Each point is an std::array<Object, 2>.

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace teaching_project {

template<typename Object>
class Points2D {
 public:
  // Zero-parameter constructor.
  // Initializes an empty sequence with no points.
  Points2D() : sequence_{nullptr}, size_{0} {}

  // Destructor. Frees the dynamically allocated sequence.
  ~Points2D() {
    delete[] sequence_;
  }

  // Copy constructor. Performs a deep copy of rhs.
  // @rhs: the Points2D object to copy from.
  Points2D(const Points2D &rhs) : sequence_{nullptr}, size_{rhs.size_} {
    if (size_ > 0) {
      sequence_ = new std::array<Object, 2>[size_];
      std::copy(rhs.sequence_, rhs.sequence_ + size_, sequence_);
    }
  }

  // Copy assignment operator using the copy-and-swap idiom.
  // @rhs: the Points2D object to assign from.
  // @return reference to this object after assignment.
  Points2D& operator=(const Points2D &rhs) {
    Points2D copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  // Move constructor. Transfers ownership of rhs's resources.
  // Leaves rhs in a valid empty state.
  // @rhs: the Points2D object to move from.
  Points2D(Points2D &&rhs) : sequence_{rhs.sequence_}, size_{rhs.size_} {
    rhs.sequence_ = nullptr;
    rhs.size_ = 0;
  }

  // Move assignment operator. Swaps all members with rhs, so
  // rhs receives the old data of *this (not zeroed out).
  // @rhs: the Points2D object to move-assign from.
  // @return reference to this object after assignment.
  Points2D& operator=(Points2D &&rhs) {
    std::swap(size_, rhs.size_);
    std::swap(sequence_, rhs.sequence_);
    return *this;
  }

  // One-parameter constructor. Creates a sequence containing a single point.
  // @item: a 2D point to store.
  Points2D(const std::array<Object, 2>& item)
      : sequence_{new std::array<Object, 2>[1]}, size_{1} {
    sequence_[0] = item;
  }

  // @return the number of points in the sequence.
  size_t size() const {
    return size_;
  }

  // Subscript operator (const). Returns the point at the given index.
  // Aborts if index is out of range.
  // @location: index into the sequence.
  // @return const reference to the point at that index.
  const std::array<Object, 2>& operator[](size_t location) const {
    if (location >= size_) {
      abort();
    }
    return sequence_[location];
  }

  // Element-wise addition of two point sequences.
  // If sizes differ, the extra points from the longer sequence are appended.
  // @c1: first sequence.
  // @c2: second sequence.
  // @return a new Points2D containing the element-wise sum.
  friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
    Points2D result;
    const size_t max_size = std::max(c1.size_, c2.size_);
    const size_t min_size = std::min(c1.size_, c2.size_);

    if (max_size == 0) return result;

    result.size_ = max_size;
    result.sequence_ = new std::array<Object, 2>[max_size];

    for (size_t i = 0; i < min_size; ++i) {
      result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
      result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
    }

    const Points2D &larger = (c1.size_ > c2.size_) ? c1 : c2;
    for (size_t i = min_size; i < max_size; ++i) {
      result.sequence_[i] = larger.sequence_[i];
    }

    return result;
  }

  // Stream insertion operator. Outputs the sequence in the format:
  // (x, y) (x, y) ... followed by std::endl.
  // An empty sequence outputs "()" followed by std::endl.
  // @out: the output stream.
  // @some_points: the Points2D object to output.
  // @return reference to the output stream.
  friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
    if (some_points.size_ == 0) {
      out << "()" << std::endl;
      return out;
    }
    for (size_t i = 0; i < some_points.size_; ++i) {
      out << "(" << some_points.sequence_[i][0]
          << ", " << some_points.sequence_[i][1] << ")";
      if (i + 1 < some_points.size_) {
        out << " ";
      }
    }
    out << std::endl;
    return out;
  }

  // Stream extraction operator. Reads a sequence from the input stream.
  // Format: first value is the count of points, followed by that many
  // coordinate pairs. Prints "ERROR" to cerr and aborts on read failure.
  // @in: the input stream.
  // @some_points: the Points2D object to populate.
  // @return reference to the input stream.
  friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
    delete[] some_points.sequence_;
    some_points.sequence_ = nullptr;
    some_points.size_ = 0;

    size_t new_size;
    if (!(in >> new_size)) {
      std::cerr << "ERROR" << std::endl;
      abort();
    }

    some_points.size_ = new_size;
    if (new_size > 0) {
      some_points.sequence_ = new std::array<Object, 2>[new_size];
    }

    for (size_t i = 0; i < new_size; ++i) {
      Object x, y;
      if (!(in >> x >> y)) {
        std::cerr << "ERROR" << std::endl;
        abort();
      }
      some_points.sequence_[i][0] = x;
      some_points.sequence_[i][1] = y;
    }

    return in;
  }

 private:
  // Dynamically allocated array of 2D points.
  std::array<Object, 2> *sequence_;
  // Number of points in the sequence.
  size_t size_;
};

}  // namespace teaching_project
#endif  // CSCI_335_HOMEWORK1_Points2D_H_
