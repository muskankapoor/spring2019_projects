/*
  Title: linear_probing.h
  Muskan Kapoor
  April 3, 2019
  Description: This is the linear probing file 
*/


#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>


namespace {

  // Internal method to test if a positive number is prime.
  bool IsPrimer(size_t n) {
    if( n == 2 || n == 3 )
      return true;
  
    if( n == 1 || n % 2 == 0 )
      return false;
  
    for( int i = 3; i * i <= n; i += 2 )
      if( n % i == 0 )
	return false;
  
    return true;
  }


  // Internal method to return a prime number at least as large as n.
  int NextPrimer(size_t n) {
    if (n % 2 == 0)
      ++n;  
    while (!IsPrimer(n)) n += 2;  
    return n;
  }

}  // namespace


// linear probing implementation.
template <typename HashedObj>
class HashTableLinear{
public:

  
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableLinear(size_t size = 101) : array_(NextPrimer(size))
  { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) {
    return IsActive(FindPos(x, this->counter, this->other_counter));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x, this->counter, this->other_counter);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
    
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x, this->counter, this->other_counter);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }


  //elements 
  size_t countElements() const{
    return current_size_;
  }


  //table
  size_t sizeofTable(){
    return array_.size();
  }



  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }


  // number of collisons 
  int counterReturn(){
    return counter;
  }


  //get number of probes
  int otherCounterReturn(){
    return 1 + other_counter;
  }

  
private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
      :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
      :element_{std::move(e)}, info_{ i } {}
  };

  int counter; 
  int other_counter;

  std::vector<HashEntry> array_;
  size_t current_size_;


  bool IsActive(size_t current_pos) 
  { return array_[current_pos].info_ == ACTIVE; }


  //find positon 
  size_t FindPos(const HashedObj & x, int & counter_, int & other_counter_) const {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);
    other_counter_ = 0; 
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      counter_++;
      other_counter_++;
      current_pos += offset;  // Compute ith probe.
      //     offset += 1; 
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
    
  }



  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimer(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

};

#endif  // linear
