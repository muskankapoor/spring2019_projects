/*
  Title: double_hashing.h
  Muskan Kapoor
  April 3, 2019
  Description: This is the dobule hashing file 
*/


#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H
#include <vector>
#include <algorithm>
#include <functional>


namespace {
  // Internal method to test if a positive number is prime.
  bool IsPrimeing(size_t n) {
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
  int NextPrimeing(size_t n) {
    if (n % 2 == 0)
      ++n;  
    while (!IsPrimeing(n)) n += 2;  
    return n;
  }

}  // namespace

// double probing implementation.
template <typename HashedObj>
class HashTableDouble {
public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrimeing(size))
  { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
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
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }

  // set collisions to 0
  void resetCollisions() {
    num_collisions_ = 0;
  }

  int getNumCollisions() {
    return num_collisions_;
  }
  int getNumElements() {
    return current_size_;
  }
  int getSize() {
    return array_.size();
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
    

  std::vector<HashEntry> array_;
  size_t current_size_;

  mutable size_t num_collisions_;


  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

 
  size_t FindPos(const HashedObj & x) const {
   

    size_t offset = InternalHashSecond(x);
    size_t current_pos = InternalHash(x);
    

    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {

      num_collisions_++;

      current_pos += offset;

      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeing(2 * old_array.size()));
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
    return hf(x) % array_.size();

  }
  //second function to calcualte 
  size_t InternalHashSecond(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return (191 - ( hf(x) )  % 191) % array_.size();
  }

};

#endif  // DOUBLE_PROBING_H
