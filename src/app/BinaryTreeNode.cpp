#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(double split_value, int label) {
  split_value_ = split_value;
  label_ = label;
  left_ = nullptr;
  right_ = nullptr;
}

BinaryTreeNode* BinaryTreeNode::GetLeft() const { return left_; }
BinaryTreeNode* BinaryTreeNode::GetRight() const { return right_; }
double BinaryTreeNode::GetSplitValue() const { return split_value_; }
int BinaryTreeNode::GetLabel() const { return label_; }
void BinaryTreeNode::SetLeft(BinaryTreeNode* left) { left_ = left; }
void BinaryTreeNode::SetRight(BinaryTreeNode* right) { right_ = right; }

BinaryTreeNode::~BinaryTreeNode() {}