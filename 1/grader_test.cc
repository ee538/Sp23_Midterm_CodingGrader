#include <iostream>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "q.h"
using ::testing::ElementsAreArray;

//-----------------------------------------------------------------------------
// Write some test cases for each function.
//-----------------------------------------------------------------------------
// GTEST for IsFull
TEST(TreeTest, IsFullReturnsTrueForFullBinaryTree) {
  Tree tree;
  tree.Insert('B');
  tree.Insert('A');
  tree.Insert('C');
  EXPECT_TRUE(tree.IsFull());
}

TEST(TreeTest, IsFullReturnsFalseForBinaryTreeWithOneChild) {
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  EXPECT_FALSE(tree.IsFull());
}

TEST(TreeTest, IsFullReturnsFalseForBinaryTreeWithTwoChildren) {
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  EXPECT_FALSE(tree.IsFull());
}

TEST(TreeTest, IsFullReturnsFalseForLeftSkewed) {
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  tree.Insert('E');
  EXPECT_FALSE(tree.IsFull());
}

TEST(TreeTest, IsFullReturnsTrueForFullTree) {
  Tree tree;
  tree.Insert('D');
  tree.Insert('B');
  tree.Insert('A');
  tree.Insert('C');
  tree.Insert('F');

  EXPECT_TRUE(tree.IsFull());
}

TEST(TreeTest, IsFullReturnsTrueForFullTreeComplex) {
  Tree tree;
  tree.Insert('F');
  tree.Insert('B');
  tree.Insert('G');
  tree.Insert('A');
  tree.Insert('D');
  tree.Insert('C');
  tree.Insert('E');

  EXPECT_TRUE(tree.IsFull());
}

TEST(TreeTest, IsFullReturnsTrueForPerfectTree) {
  Tree tree;
  tree.Insert('D');
  tree.Insert('B');
  tree.Insert('A');
  tree.Insert('C');
  tree.Insert('F');
  tree.Insert('E');
  tree.Insert('G');

  EXPECT_TRUE(tree.IsFull());
}

// GTEST for CreateHistogram

TEST(CreateHistogramTest, SimpleTree) {
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  tree.Insert('A');
  std::map<char, int> expected = {{'A', 1}, {'B', 1}, {'C', 1}, {'D', 1}};
  std::map<char, int> actual = tree.CreateHistogram();
  EXPECT_EQ(expected, actual);
}

TEST(CreateHistogramTest, WithDuplicates) {
  Tree tree(new TreeNode('A', new TreeNode('B', nullptr, nullptr),
                         new TreeNode('B', new TreeNode('C', nullptr, nullptr),
                                      new TreeNode('C', nullptr, nullptr))));

  std::map<char, int> expected = {{'A', 1}, {'B', 2}, {'C', 2}};
  std::map<char, int> actual = tree.CreateHistogram();
  EXPECT_EQ(expected, actual);
}

TEST(CreateHistogramTest, EmptyTree) {
  Tree tree;
  std::map<char, int> expected = {};
  std::map<char, int> actual = tree.CreateHistogram();
  EXPECT_EQ(expected, actual);
}

TEST(CreateHistogramTest, SingleNodeTree) {
  Tree tree;
  tree.Insert('A');
  std::map<char, int> expected = {{'A', 1}};
  std::map<char, int> actual = tree.CreateHistogram();
  EXPECT_EQ(expected, actual);
}

// GTEST for CountNodes
TEST(TreeTest, CountNodesEmptyTree) {
  Tree tree;
  EXPECT_EQ(tree.CountNodes(), 0);
}

TEST(TreeTest, CountNodesSingleNode) {
  Tree tree;
  tree.Insert('A');
  EXPECT_EQ(tree.CountNodes(), 1);
}

TEST(TreeTest, CountNodesFullTree) {
  /*
           A
         /   \
        B     C
       / \   / \
      D   E F   G
  */
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  tree.Insert('E');
  tree.Insert('F');
  tree.Insert('G');
  EXPECT_EQ(tree.CountNodes(), 7);
}

TEST(TreeTest, CountNodesIncompleteTree) {
  /*
           A
         /   \
        B     C
       /     /
      D     F
  */
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  tree.Insert('F');
  EXPECT_EQ(tree.CountNodes(), 5);
}

TEST(TreeTest, CountNodesLeftSkewedTree) {
  /*
           A
          /
         B
        /
       C
      /
     D
  */
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  EXPECT_EQ(tree.CountNodes(), 4);
}

TEST(TreeTest, CountNodesRightSkewedTree) {
  /*
           A
            \
             B
              \
               C
                \
                 D
  */
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  EXPECT_EQ(tree.CountNodes(), 4);
}

TEST(TreeTest, ToVectorPostOrderEmptyTree) {
  Tree tree;
  EXPECT_EQ(tree.ToVectorPostOrder(), std::vector<char>{});
}

TEST(TreeTest, ToVectorPostOrderSingleNode) {
  Tree tree;
  tree.Insert('A');
  EXPECT_EQ(tree.ToVectorPostOrder(), std::vector<char>{'A'});
}

TEST(TreeTest, ToVectorPostOrderFullTree) {
  Tree tree;
  tree.Insert('D');
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('E');
  tree.Insert('F');
  tree.Insert('G');
  auto expected = std::vector<char>{'C', 'B', 'A', 'G', 'F', 'E', 'D'};
  EXPECT_EQ(tree.ToVectorPostOrder(), expected);
}

TEST(TreeTest, ToVectorPostOrderSkewedTree) {
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  auto expected = std::vector<char>{'D', 'C', 'B', 'A'};
  EXPECT_EQ(tree.ToVectorPostOrder(), expected);
}

TEST(IsLeftSkewedTest, EmptyTree) {
  Tree tree;
  EXPECT_TRUE(tree.IsLeftSkewed());
}

TEST(IsLeftSkewedTest, OneNodeTree) {
  Tree tree;
  tree.Insert('A');
  EXPECT_TRUE(tree.IsLeftSkewed());
}

TEST(IsLeftSkewedTest, BalancedTree) {
  Tree tree;
  tree.Insert('D');
  tree.Insert('B');
  tree.Insert('F');
  tree.Insert('A');
  tree.Insert('C');
  tree.Insert('E');
  tree.Insert('G');
  EXPECT_FALSE(tree.IsLeftSkewed());
}

TEST(IsLeftSkewedTest, LeftSkewedTree) {
  Tree tree;
  tree.Insert('D');
  tree.Insert('C');
  tree.Insert('B');
  tree.Insert('A');
  EXPECT_TRUE(tree.IsLeftSkewed());
}

TEST(IsLeftSkewedTest, RightSkewedTree) {
  Tree tree;
  tree.Insert('A');
  tree.Insert('B');
  tree.Insert('C');
  tree.Insert('D');
  EXPECT_FALSE(tree.IsLeftSkewed());
}

TEST(IsLeftSkewedTest, LeftSkewedTree2) {
  /*
                       F
                      /
                      E
                    /
                    D
                  /
                  C
                /
                B
                /
                A
  */
  Tree tree;
  tree.Insert('F');
  tree.Insert('E');
  tree.Insert('D');
  tree.Insert('C');
  tree.Insert('B');
  tree.Insert('A');
  EXPECT_TRUE(tree.IsLeftSkewed());
}
