// Muskan Kapoor
// FIle:sequence_map.h  
// Assignment 2, March 12, 2019
// creation  of the class sequence_map.h  

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <iostream>
#include <vector>
using namespace std;

class SequenceMap{
public:
  
  //big five below
  
  //zero parameter constructor 
  SequenceMap() = default;

  //destructor 
  ~SequenceMap() = default;

  // Copy-constructor.
  SequenceMap(const SequenceMap &rhs) = default;

  // Copy-assignment.
  SequenceMap& operator=(const SequenceMap &rhs) = default;

  // Move-constructor.
  SequenceMap(SequenceMap &&rhs) = default;

  // Move-assignment.
  SequenceMap& operator=(SequenceMap &&rhs) = default;

  //assignment 1
  SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
  }

  bool operator<(const SequenceMap &rhs) const{
    return recognition_sequence_ < rhs.recognition_sequence_;
  }
  
  friend ostream &operator<<(ostream &out, const SequenceMap &map){
    for(unsigned int i = 0; i < map.enzyme_acronyms_.size(); ++i){
      cout << map.enzyme_acronyms_[i] << " ";
    }
    return out;
  }

  // getter 
  const string GetRecognitionSequence(){
    return recognition_sequence_;
  }

  void Merge(const SequenceMap &other_sequence){
    for(unsigned int i = 0; i < other_sequence.enzyme_acronyms_.size(); ++i){
      enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
    }
  }

  
  
private:
  string recognition_sequence_;                  
  vector<string> enzyme_acronyms_;  

};

#endif
