#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

// Double Hashing 
// Implemented functions
//
// number_of_elements () - > To find the number of elements in the table 
// size_of_table ()      - > To find the size of the table
// collisions ()         - > To find the nubmer of collision
// setcollison ()        - > To reset collison
// findPos               - > Was modififed to count collision 
// DoubleHash ()         - > Added for double hashing based on formula given hash2 (x) = R – (x mod R), in our case Rvalue = 89;
// DoubleHash ()         - > Used in the findPos as the second InternalHash(x) function DoubleHash(x) in our case x = 89;

#include <vector>
#include <algorithm>
#include <functional>


namespace {

// Internal method to test if a positive number is prime.
bool IsPrimeDouble(size_t n) {
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
int NextPrimeDouble(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeDouble(n)) n += 2;  
  return n;
}

}  // namespace


// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrimeDouble(size))
    { MakeEmpty();}
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    number_Of_Collision = 0;
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

  size_t total_Number_Of_Elements (){ // To find total number of elements in the table
    return current_size_;   // current size of the elements
  }
  size_t size_Of_Table(){    // To find the table size
    return array_.size();   // Return size of the array
  }
  size_t Collision(){  // to Get the number of collisions
    return number_Of_Collision;
  }

  void setCollision(){  // to set collison
    number_Of_Collision = 0 ;

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
  int Rvalue = 89;    // R-value 89
  mutable size_t number_Of_Collision;  // mutable to allow modification of const obj

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      current_pos += DoubleHash(x);  // Compute ith probe. with the second internalhash function DoubleHash()
      if (current_pos >= array_.size()) current_pos -= array_.size();
      number_Of_Collision++; // increment collision
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeDouble(2 * old_array.size()));
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
  size_t DoubleHash(const HashedObj & x) const { // Double hash function to calculate R - (x % R)
    static std::hash<HashedObj> hf;
    return (89 - (hf(x) % 89));   // Since R = 89 using 89 as the value 
  }
  
};

#endif  // DOUBLE_HASHING_H
