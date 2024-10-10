#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(double split_value, int label) {
  split_value_ = split_value;
  label_ = label;
  left_child_ = nullptr;
  right_child_ = nullptr;
}

BinaryTreeNode* BinaryTreeNode::GetLeft() const { return left_child_; }
BinaryTreeNode* BinaryTreeNode::GetRight() const { return right_child_; }
double BinaryTreeNode::GetSplitValue() const { return split_value_; }
int BinaryTreeNode::GetLabel() const { return label_; }
void BinaryTreeNode::SetLeft(BinaryTreeNode* left) { left_child_ = left; }
void BinaryTreeNode::SetRight(BinaryTreeNode* right) { right_child_ = right; }
void BinaryTreeNode::SetLabel(int label) { label_ = label; }
void BinaryTreeNode::SetSplitValue(double split_value) {
  split_value_ = split_value;
}

BinaryTreeNode::~BinaryTreeNode() {}