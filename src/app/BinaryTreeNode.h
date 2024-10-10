#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

#pragma once

class BinaryTreeNode {
 public:
  BinaryTreeNode(double split_value, int label);
  BinaryTreeNode* GetLeft() const;
  BinaryTreeNode* GetRight() const;
  double GetSplitValue() const;
  int GetLabel() const;
  void SetLeft(BinaryTreeNode* left);
  void SetRight(BinaryTreeNode* right);
  void SetLabel(int label);
  void SetSplitValue(double split_value);

  ~BinaryTreeNode();

 private:
  double split_value_;
  int label_;
  BinaryTreeNode* left_child_;
  BinaryTreeNode* right_child_;
};

#endif
