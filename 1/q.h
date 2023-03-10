#include <iostream>
#include <map>
#include <string>
#include <vector>
// TODO: Don't modify this file. Your implementation should go in q.cc file.
//
// A struct for tree nodes.
// No need to modify this struct.
struct TreeNode {
  char data;        // The data stored in the node
  TreeNode *left;   // Pointer to the left child node
  TreeNode *right;  // Pointer to the right child node

  // Constructor for a node with no children
  TreeNode(char x) : data(x), left(nullptr), right(nullptr) {}

  // Constructor for a node with two children
  TreeNode(char x, TreeNode *left_ptr, TreeNode *right_ptr)
      : data(x), left(left_ptr), right(right_ptr) {}
};

// A class for binary trees.
// TODO: Implement the methods of this class in the q.cc file.
class Tree {
 public:
  // Constructor - Already implemented. No need to change.
  Tree() : root_(nullptr) {}
  // Constructor - Already implemented. No need to change.
  Tree(TreeNode *root) : root_(root) {}
  //-----------------------------------------------------------------------------
  // TODO: Implement the rest of the functions in q.cc file.
  //-----------------------------------------------------------------------------
  // Destructor: should de-allocate all allocated dynamic memory.
  ~Tree();
  // Hint: Use recursion to de-allocate the entire tree. In your destructor call
  // DestroySubtree function that given a root of a tree recursively
  // de-allocates its nodes.
  void DestroySubtree(TreeNode *root);
  //-----------------------------------------------------------------------------
  // Checks whether the tree is a full binary tree
  //
  // Example input:        A
  //                      / \
  //                     B   C
  // Output: true
  //
  // Example input:        A
  //                      / \
  //                     B   C
  //                    /
  //                   D
  // Output: false
  // 👉Note: IsFull is not a recursive function. Instead, it should call
  // IsFull_helper which is a recursive function. Use the same pattern for
  // other functions below and only make the helper function recursive.
  bool IsFull();
  void IsFull_helper(TreeNode *root, bool &is_full);
  //-----------------------------------------------------------------------------
  // Creates a histogram of the characters in the tree, where the keys of the
  // map represent the characters and the values represent their frequency.
  //
  // Example input:        A
  //                      / \
  //                     B   C
  //                        / \
  //                       D   A
  // Output: {'A': 2, 'B': 1, 'C': 1, 'D': 1}
  std::map<char, int> CreateHistogram();
  void CreateHistogram_helper(TreeNode *root, std::map<char, int> &map);
  //-----------------------------------------------------------------------------
  // Counts the number of nodes in the tree
  //
  // Example input:        A
  //                      / \
  //                     B   C
  //                        / \
  //                       D   A
  // Output: 5
  int CountNodes();
  int CountNodesHelper(TreeNode *root);
  //-----------------------------------------------------------------------------
  // Converts the tree to a vector using postorder traversal.
  //
  // Example input:        A
  //                      / \
  //                     B   C
  //                        / \
  //                       D   A
  // Output: {'B', 'D', 'A', 'C', 'A'}
  std::vector<char> ToVectorPostOrder();
  void ToVectorPostOrderHelper(TreeNode *root, std::vector<char> &vec);
  //-----------------------------------------------------------------------------
  // Assumes the tree is a binary search tree and data in its correct place in
  // the binary search tree
  //
  // Example input:        '4'
  //                      / \
  //                     '2' '7'
  //                    / \
  //                   '1'  '3'
  // Output (after inserting '5'):
  //                      '4'
  //                      / \
  //                    '2'   '7'
  //                    / \   /
  //                  '1''3' '5'
  void Insert(char data);
  void Insert_helper(TreeNode *&root, char data);
  //-----------------------------------------------------------------------------
  // Checks if a binary tree is left skewed.
  // A binary tree is left skewed if each node has at most one child and all
  // the nodes in the tree are in the left subtree of the root node. return
  // true if the tree is left skewed, false otherwise. Sample input/output:
  // Input:
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
  // Output:
  // true
  // Example 2:
  // Input:
  /*
               F
              /
             E
            / \
           D   Z
  */
  // Output:
  // false
  bool IsLeftSkewed();
  bool IsLeftSkewed_helper(TreeNode *root);

 private:
  TreeNode *root_;
};