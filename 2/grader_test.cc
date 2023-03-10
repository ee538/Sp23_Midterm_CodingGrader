#include <iostream>
#include <string>
#include <stdexcept>

#include "gtest/gtest.h"
#include "q.h"

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------

TEST(SizedMapTest, CopyConstructorTest) {
  SizedMap sm1(2);
  sm1.Put(1, "one");
  sm1.Put(2, "two");
  SizedMap sm2(sm1);

  EXPECT_EQ(sm1.Size(), sm2.Size());

  EXPECT_EQ(sm1.Get(1), sm2.Get(1));
  EXPECT_EQ(sm1.Get(2), sm2.Get(2));

  sm1.Put(3, "three");

  EXPECT_EQ(sm2.Get(3), "INVALID_KEY");
}

TEST(SizedMapTest, SizeTest) {
  SizedMap sm(3);

  sm.Put(1, "one");
  sm.Put(2, "two");

  EXPECT_EQ(sm.Size(), 2);

  sm.Put(3, "three");

  EXPECT_EQ(sm.Size(), 3);

  sm.Put(4, "four");

  EXPECT_EQ(sm.Size(), 3);

  sm.Put(3, "new three");

  EXPECT_EQ(sm.Size(), 3);

  sm.Get(2);
  sm.Get(3);

  EXPECT_EQ(sm.Size(), 3);
}

TEST(SizedMapTest, PutAndGetTest) {
  SizedMap sm(2);

  sm.Put(1, "one");
  sm.Put(2, "two");

  EXPECT_EQ(sm.Get(1), "one");
  EXPECT_EQ(sm.Get(2), "two");

  sm.Put(3, "three");

  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
  EXPECT_EQ(sm.Get(3), "three");

  sm.Put(3, "new three");

  EXPECT_EQ(sm.Get(3), "new three");
}

TEST(SizedMapTest, InvalidKeyTest) {
  SizedMap sm(1);

  EXPECT_EQ(sm.Get(1), "INVALID_KEY");
}

TEST(SizedMapTest, AddTwoSizedMaps) {
  // Create two SizedMaps
  SizedMap sm1(2);
  sm1.Put(1, "hello");
  sm1.Put(2, "world");

  SizedMap sm2(2);
  sm2.Put(3, "foo");
  sm2.Put(4, "bar");

  // Add the two SizedMaps
  SizedMap sm3 = sm1 + sm2;

  // Check that the new SizedMap has the correct size.
  EXPECT_EQ(sm3.Size(), 4);

  // Check that the new SizedMap has the correct values.
  EXPECT_EQ(sm3.Get(1), "hello");
  EXPECT_EQ(sm3.Get(2), "world");
  EXPECT_EQ(sm3.Get(3), "foo");
  EXPECT_EQ(sm3.Get(4), "bar");
}

TEST(SizedMapTest, AddTwoSizedMaps_WithDuplicates) {
  // Create two SizedMaps
  SizedMap sm1(2);
  sm1.Put(1, "hello");
  sm1.Put(2, "world");

  SizedMap sm2(2);
  sm2.Put(1, "foo");
  sm2.Put(4, "bar");

  // Add the two SizedMaps
  SizedMap sm3 = sm1 + sm2;

  // Check that the new SizedMap has the correct size.
  EXPECT_EQ(sm3.Size(), 3);

  // Check that the new SizedMap has the correct values.
  EXPECT_EQ(sm3.Get(1), "foo");
  EXPECT_EQ(sm3.Get(2), "world");
  EXPECT_EQ(sm3.Get(4), "bar");

  sm3.Put(5, "capacity");
  EXPECT_EQ(sm3.Size(), 4);
}

TEST(SizedMapTest, PlusOperator_EvictionPolicy) {
  SizedMap map1(2);
  map1.Put(1, "one");
  map1.Put(2, "two");

  SizedMap map2(2);
  map2.Put(3, "three");
  map2.Put(4, "four");

  SizedMap combinedMap = map1 + map2;

  // Make sure the capacity of the combined map is correct
  EXPECT_EQ(combinedMap.Size(), 4);

  // Check the eviction policy by attempting to insert a new item into the
  // combined map
  combinedMap.Put(5, "five");

  // Make sure the size of the combined map is still 4.
  EXPECT_EQ(combinedMap.Size(), 4);

  // Make sure the oldest item has been removed.
  EXPECT_EQ(combinedMap.Get(1), "INVALID_KEY");
}

TEST(SizedMapTest, Reverse) {
  // Create a SizedMap with capacity 3 and insert some values
  SizedMap sm(3);
  sm.Put(1, "one");
  sm.Put(2, "two");
  sm.Put(3, "three");

  // Reverse the keys
  sm.Reverse();
  sm.Put(4, "four");

  // Verify the reversed order of keys
  EXPECT_EQ(sm.Get(4), "four");
  EXPECT_EQ(sm.Get(3), "INVALID_KEY");
  EXPECT_EQ(sm.Get(2), "two");
  EXPECT_EQ(sm.Get(1), "one");
}
