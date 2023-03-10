
#ifndef SIZEDMAP_H
#define SIZEDMAP_H

#include <map>
#include <queue>
#include <string>
// TODO: Don't modify this file. Your implementation should go in q.cc file.
//
// Design a wrapper class around std::map<int, std::string> called SizedMap. The
// main job of this wrapper is to ensure the size of the map is limited: Given
// an integer value called capacity, the total number of entries in the map
// should never be greater than capacity.
class SizedMap {
 public:
  // Constructs a new SizedMap object with the given capacity.
  // You can assume the input capacity is always positive.
  // Sample input: SizedMap(5)
  // Sample output: New SizedMap object with capacity of 5
  SizedMap(int capacity);

  // Constructs a new SizedMap object that is a copy of the given SizedMap
  // object.
  // Sample input: SizedMap sm(5);
  //               sm.Put(1, "one");
  //               sm.Put(2, "two");
  //               SizedMap copy(sm);
  // Sample output: New SizedMap object with capacity of 5 and contains keys 1
  // and 2 with their corresponding values
  SizedMap(const SizedMap& other);

  // Returns the value associated with the given key.
  // If the value does not exists, it returns a string with value "INVALID_KEY".
  // Sample input: SizedMap sm(5);
  //               sm.Put(1, "one");
  //               sm.Get(1);
  // Output: "one"
  //               sm.Get(2);
  // output: "INVALID_KEY"
  std::string Get(int key) const;

  // Inserts a new key-value pair into the map.
  // If the map is at capacity, removes the oldest key-value pair before adding
  // the new one: The entry that is removed first should be the entry
  // that was inserted first, i.e. the entries are removed in a FIFO format.
  // If the input key already exists in the map, update the value only.
  // Sample input: SizedMap sm(2); // A SizedMap with capacity 2.
  //               sm.Put(1, "one");
  //               sm.Put(2, "two");
  //               sm.Put(3, "three");
  // Sample output: The map now contains key-value pairs (2, "two") and (3,
  // "three"). The entry (1, "one") was evicted when we called sm.Put(3,
  // "three") since the map was at maximum capacity.
  void Put(int key, std::string value);

  // Returns the current size of the map (i.e. the number of key-value pairs).
  // Sample input: SizedMap sm(5);
  //               sm.Put(1, "one");
  //               sm.Put(2, "two");
  //               sm.Size();
  // Sample output: 2
  int Size() const;

  // Combines two SizedMap objects by concatenating their key-value pairs.
  // If the two maps contain the same key, the value from the second map is
  // used, but the position of that key in the FIFO should be decided by the
  // position of the key in the first map, i.e., in this case, the position
  // would not be updated.
  //
  // The resulting map has a capacity equal to the sum of
  // the capacities of the two input maps. Sample input: SizedMap sm1(2);
  //               sm1.Put(1, "one");
  //               SizedMap sm2(3);
  //               sm2.Put(2, "two");
  //               sm2.Put(3, "three");
  //               SizedMap sm3 = sm1 + sm2;
  // Sample output: A new SizedMap object with capacity of 5 and contains
  // key-value pairs (1, "one"), (2, "two"), and (3, "three").
  //
  // The FIFO order of the result: The insertion partial order of the entries in
  // each map should be preserved, but all the entries of the first map should
  // be considered before the entries of the second map.
  //
  // Example: Let the keys in
  // sm1 with capacity 2 be {1, 2}, where 1 entered before 2 and keys in sm2
  // with capacity 2 be {4, 5}, where 4 entered before 5.
  // Let sm3 = sm1 + sm2.
  // The order of the keys in sm3 should be {1, 2, 4, 5}, i.e., if we have
  // sm3.Put(6, 6), the entry with the key of 1 should be evicted before the
  // entry with key of 6 is inserted.
  SizedMap operator+(const SizedMap& sm2);

  // Reverses the arrival order of the the keys in the map. E.g.
  // if the keys in sm1 are {1, 2}, where the entry with key 1 entered
  // before the entry with key 2, after sm1.Reverse(), the order of the keys
  // in sm1 should be {2, 1}, i.e. the next sm1.Put(3, 3) should evict the
  // entry with key 2.
  void Reverse();

 private:
  int capacity_;
  std::map<int, std::string> map_;
  std::queue<int> keys_;
};

#endif  // SIZEDMAP_H