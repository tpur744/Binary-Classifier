#include "BinaryTreeNode.h"

BinaryTreeNode::BinaryTreeNode(int label)
    : split_value_(-1),
      label_(label),
      feature_index_(-1),
      impurity_(0.0),
      left_child_(nullptr),
      right_child_(nullptr) {}

BinaryTreeNode::BinaryTreeNode(double split_value, int feature_index,
                               double impurity)
    : split_value_(split_value),
      label_(-1),
      feature_index_(feature_index),
      impurity_(impurity),
      left_child_(nullptr),
      right_child_(nullptr) {}

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

bool BinaryTreeNode::IsLeaf() const {
  return left_child_ == nullptr && right_child_ == nullptr;
}

int BinaryTreeNode::GetFeatureIndex() const { return feature_index_; }
double BinaryTreeNode::GetImpurity() const { return impurity_; }

BinaryTreeNode::~BinaryTreeNode() {
  if (left_child_ != nullptr) {
    delete left_child_;
    left_child_ = nullptr;
  }
  if (right_child_ != nullptr) {
    delete right_child_;
    right_child_ = nullptr;
  }
}
