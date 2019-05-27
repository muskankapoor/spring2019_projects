// Muskan Kapoor
// FIle: points2.h
// Assignment 1, Feb 11, 2019
// class Points2 describes a sequence of 2D points.
// The purpose of this assignment is to create a Points2 class and utilizing big five constructors
// and overloading operators


#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {
  // Example: (1, 3), (4, 5) is a sequence of two points, where each coordinate is an integer.
  // (1.2, 3.4), (5.6,10.1), (11.1, 12.0) is a sequence of three points where each coordinate is a double.
  // the big five constructors and overloading operators effect the 2D Points2
  template<typename Object>
  class Points2 {
  public:
    
    // Zero-parameter constructor.
    // Set size to 0.
  Points2() : sequence_(nullptr), size_(0) { }

    //Copy-constructor.
  Points2(const Points2 &rhs) {
      if (rhs.size() == 0) {
	size_ = 0;
	sequence_ = nullptr;
      }
      else { 
        size_ = rhs.size();
        sequence_ = new std::array<Object, 2>[size_];
        std::copy(rhs.sequence_, rhs.sequence_+rhs.size_, sequence_);
      }
    }

      
    //Copy-assignment.
  Points2& operator=(const Points2 &rhs) {
      Points2 copy = rhs; 
      std::swap(*this, copy);
      return *this;
    }

    
    //Move-constructor.
  Points2(Points2 &&rhs) : sequence_(std::move(rhs.sequence_)), size_(std::move(rhs.size_)) {
      rhs.sequence_ = nullptr;
      rhs.size_ = 0;
    }

    // Move-assignment. 
  Points2& operator=(Points2 &&rhs) {
      if (this != &rhs) {
	std::swap(size_, rhs.size_);
	std::swap(sequence_, rhs.sequence_);
      }
      return *this;
    }

    
    
    // Destructor
  ~Points2() {
      delete [] sequence_;
      sequence_ = nullptr;
    }

    // end of big five
    
    // One parameter constructor.
  Points2(const std::array<Object, 2>& item) {
    size_ = item.size()/2;
    sequence_ = new std::array<Object, 2>{item};
    }


  // Read a chain from standard input.
  // deals with if the input line is empty 
  void ReadPoints2() {
      std::string input_line;
      std::getline(std::cin, input_line);
      std::stringstream input_stream(input_line);
      if (input_line.empty())
	return;
      // Read size of sequence (an integer).
      int size_of_sequence;
      input_stream >> size_of_sequence;
      // Allocate space for "sequence"
      size_ = size_of_sequence;
      sequence_ = new std::array<Object, 2>[size_of_sequence];
      Object token;
      for (int i = 0 ; input_stream >> token; ++i) {
	sequence_[i][0] = token;
	input_stream >> token;
	sequence_[i][1] = token;
      }
    }


  size_t size() const {
      return size_;
    }

    
    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const {
      if (location < 0 || location >= size_) {
	abort();
      } else
        return sequence_[location];
    }

    
    // @c1: A sequence.
    // @c2: A second sequence.
    // @return their sum. If the sequences are not of the same size, append the result with the
    //remaining part of the larger sequence.
  friend Points2 operator+(const Points2 &c1, const Points2 &c2) {
      Points2<double> result;
      if (c1.size() == c2.size()) {
	result.size_ = c2.size();
	result.sequence_ = new std::array<Object, 2>[result.size_];
	for (size_t i = 0; i < result.size(); i++) {
	  result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
	  result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
	}
      }
     
      else if (c1.size() > c2.size()) {
	result.size_ = c1.size();
	result.sequence_ = new std::array<Object, 2>[result.size_];
	for (size_t i = 0; i < c2.size(); i++) {
	  result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
	  result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
	}
	
	for (size_t i = c2.size(); i < result.size_; i++) {
	  result.sequence_[i][0] = c1.sequence_[i][0];
	  result.sequence_[i][1] = c1.sequence_[i][1];
	}
      }
      else {
      
        result.size_ = c2.size();
        result.sequence_ = new std::array<Object, 2>[result.size_];
        for (size_t i = 0; i < c1.size(); i++) {
          result.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
          result.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
        }
        for (size_t i = c1.size(); i < result.size_; i++) {
          result.sequence_[i][0] = c2.sequence_[i][0];
          result.sequence_[i][1] = c2.sequence_[i][1];
        }
      }
      return result;
    }

    
    
    // Overloading the << operator.
    // post-condition: prints out the sequence in form (x, y)
    // deals with if size is 1
    // checks if the sequence is empty 
  friend std::ostream& operator<<(std::ostream &out, const Points2 &some_points2) {
      if (some_points2.sequence_ != nullptr && some_points2.size_ == 1) {
	out << "(" << some_points2.sequence_->at(0) << ", " << some_points2.sequence_->at(1) << ")";
      }
      if (some_points2.sequence_ != nullptr && some_points2.size_ > 1) {
	for (size_t i = 0; i < some_points2.size_; i++) {
	  out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ")" << " ";
	}
      }
      if (some_points2.sequence_ == nullptr) {
	out << "()";
      }
      out << std::endl;
      return out;
    }

   
  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;

  };

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
