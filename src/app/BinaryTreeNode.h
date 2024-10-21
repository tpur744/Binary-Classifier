#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

#pragma once

class BinaryTreeNode {
 public:
  // Constructor for internal nodes with split value, feature index, and
  // impurity
  BinaryTreeNode(double split_value, int feature_index, double impurity);

  // Constructor for leaf nodes with only a label
  BinaryTreeNode(int label);

  // Getters
  BinaryTreeNode* GetLeft() const;
  BinaryTreeNode* GetRight() const;
  double GetSplitValue() const;
  int GetLabel() const;
  int GetFeatureIndex() const;
  double GetImpurity() const;

  // Setters
  void SetLeft(BinaryTreeNode* left);
  void SetRight(BinaryTreeNode* right);
  void SetLabel(int label);
  void SetSplitValue(double split_value);

  // Check if the node is a leaf
  bool IsLeaf() const;

  // Destructor
  ~BinaryTreeNode();

 private:
  double split_value_;           // Value to split the data at this node
  int label_;                    // Label for leaf nodes (-1 for internal nodes)
  BinaryTreeNode* left_child_;   // Left child of the current node
  BinaryTreeNode* right_child_;  // Right child of the current node
  int feature_index_;            // The feature index for the split
  double impurity_;              // The impurity at this node
};

#endif
