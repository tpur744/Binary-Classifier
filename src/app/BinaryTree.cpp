#include "BinaryTree.h"

#include <iomanip>
#include <iostream>

BinaryTree::BinaryTree() : root_(nullptr) {}

BinaryTree::~BinaryTree() { DeleteTree(root_); }

void BinaryTree::DeleteTree(BinaryTreeNode* node) {
  if (node == nullptr) {
    return;
  }
  DeleteTree(node->GetLeft());
  DeleteTree(node->GetRight());
  delete node;
}

void BinaryTree::FindBestSplit(const DataSet& data_set,
                               double& best_feature_index,
                               double& best_split_value) const {
  double best_impurity_drop = -1.0;
  for (int i = 0; i < data_set.GetNumFeatures(); i++) {
    for (int j = 0; j < data_set.GetNumObservations(); j++) {
      double split_value = data_set.GetFeatureValue(i, j);
      DataSet left, right;
      data_set.Split(i, split_value, left, right);
      double entropy_left = left.GetEntropy();
      double entropy_right = right.GetEntropy();
      double impurity_drop =
          data_set.GetEntropy() - (left.GetNumObservations() * entropy_left +
                                   right.GetNumObservations() * entropy_right) /
                                      data_set.GetNumObservations();
      if (impurity_drop > best_impurity_drop) {
        best_impurity_drop = impurity_drop;
        best_feature_index = i;
        best_split_value = split_value;
      }
    }
  }
}

void BinaryTree::Grow(const DataSet& data_set) {
  if (data_set.IsPure()) {
    return;
  }
  double best_feature_index = -1;
  double best_split_value = 0;

  FindBestSplit(data_set, best_feature_index, best_split_value);

  DataSet left, right;
  data_set.Split(best_feature_index, best_split_value, left, right);
}
/*
// Check if the dataset has observations from both categories
if (data_set.GetPositiveCount() == 0 || data_set.GetNegativeCount() == 0) {
  // If all observations belong to one category, create a leaf node
  int label = data_set.GetPositiveCount() > 0 ? 1 : -1;
  root_ =
      new BinaryTreeNode(-1, label);  // -1 for split_value, as it's a leaf
  return;
}

// Initialize variables for the best split
double best_feature_index = -1;
double best_split_value = 0;

// Find the best split for the current dataset
FindBestSplit(data_set, best_feature_index, best_split_value);

// Create left and right datasets based on the best split
DataSet left, right;
data_set.Split(best_feature_index, best_split_value, left, right);

// Create the root node with the best split value
root_ = new BinaryTreeNode(best_split_value,
                           -1);  // -1 for label, as it's not a leaf yet

// Grow left subtree if there are observations in the left dataset
if (left.GetNumObservations() > 0) {
  BinaryTree* left_tree =
      new BinaryTree();                  // Create new tree for left subtree
  left_tree->Grow(left);                 // Recursively grow left subtree
  root_->SetLeft(left_tree->GetRoot());  // Set the left child
  delete left_tree;                      // Clean up temporary tree
}

// Grow right subtree if there are observations in the right dataset
if (right.GetNumObservations() > 0) {
  BinaryTree* right_tree =
      new BinaryTree();     // Create new tree for right subtree
  right_tree->Grow(right);  // Recursively grow right subtree
  root_->SetRight(right_tree->GetRoot());  // Set the right child
  delete right_tree;                       // Clean up temporary tree
}
} */

BinaryTreeNode* BinaryTree::GetRoot() const { return root_; }

void BinaryTree::Show() const { ShowNode(root_, 0); }

void BinaryTree::ShowNode(BinaryTreeNode* node, int depth) const {
  if (node == nullptr) {
    return;  // Base case: if the node is null, just return
  }

  // Print the right subtree first
  ShowNode(node->GetRight(), depth + 1);

  // Print current node (with its split value)
  std::cout << std::string(depth * 2, ' ');  // Indentation based on depth
  std::cout << std::fixed << std::setprecision(3);
  std::cout << depth << ", " << node->GetSplitValue() << ", "
            << node->GetLabel() << std::endl;

  // Print the label of the current node
  std::cout << std::string(depth * 2 + 2, ' ') << "label: " << node->GetLabel()
            << std::endl;

  // Print the left subtree
  ShowNode(node->GetLeft(), depth + 1);
}