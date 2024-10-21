#include "BinaryTree.h"

#include <iomanip>
#include <iostream>
using namespace std;
#include "DataSet.hpp"

/*
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
      if (left.IsEmpty() || right.IsEmpty()) {
        continue;  // Skip this split if it results in empty datasets
      }

      double entropy_left = left.GetEntropy();
      double entropy_right = right.GetEntropy();

      double impurity_drop =
          data_set.GetEntropy() -
          (left.GetNumObservations() / data_set.GetNumObservations()) *
              entropy_left -
          (right.GetNumObservations() / data_set.GetNumObservations()) *
              entropy_right;

      if (impurity_drop > best_impurity_drop) {
        best_impurity_drop = impurity_drop;
        best_feature_index = i;
        best_split_value = split_value;
      }
    }
  }
}

void BinaryTree::Grow(const DataSet& data_set) {
  // Base case: If the dataset is pure (no more splits possible), create a leaf
  // node
  if (data_set.IsPure()) {
    int label = data_set.GetMajorityLabel();
    root_ =
        new BinaryTreeNode(-1, label);  // -1 for split_value, as it's a leaf
    return;
  }

  double best_feature_index = -1;
  double best_split_value = 0;

  DataSet left, right;
  FindBestSplit(data_set, best_feature_index, best_split_value);

  if (best_feature_index == -1) {
    return;
  }

  data_set.Split(best_feature_index, best_split_value, left, right);

  root_ = new BinaryTreeNode(best_split_value, -1);

  BinaryTree* left_tree = new BinaryTree();
  BinaryTree* right_tree = new BinaryTree();

  left_tree->Grow(left);    // Recursively grow the left subtree
  right_tree->Grow(right);  // Recursively grow the right subtree

  // Set the left and right subtrees in the current node
  root_->SetLeft(left_tree->GetRoot());
  root_->SetRight(right_tree->GetRoot());
}

BinaryTreeNode* BinaryTree::GetRoot() const { return root_; }

void BinaryTree::Show() const { ShowNode(root_, 0); }

void BinaryTree::ShowClassifier() const {
  if (root_ == nullptr) {
    std::cout << "The classifier has not been trained." << std::endl;
    return;
  }

  ShowNode(root_, 0);  // Call the helper function to print the tree structure
}

void BinaryTree::ShowNode(BinaryTreeNode* node, int depth) const {
  if (node == nullptr) {
    return;  // Base case: if the node is null, just return
  }

  // If the node is a leaf, print the label
  if (node->IsLeaf()) {
    std::cout << std::string(depth * 2, ' ')  // Indent based on depth
              << "label: " << node->GetLabel() << std::endl;
  } else {
    // Print current node: split dimension, split value, and impurity
    std::cout << std::string(depth * 2, ' ')  // Indent based on depth
              << "split dim: " << node->GetFeatureIndex()
              << ", split value: " << std::fixed << std::setprecision(3)
              << node->GetSplitValue() << ", impurity: " << std::fixed
              << std::setprecision(3) << node->GetImpurity() << std::endl;
  }

  // Recursively show the left and right children
  if (!node->IsLeaf()) {
    ShowNode(node->GetLeft(), depth + 1);   // Show left child
    ShowNode(node->GetRight(), depth + 1);  // Show right child
  }
}
*/

#include <iomanip>
#include <iostream>

#include "BinaryTree.h"
using namespace std;
#include "DataSet.hpp"

// Constructor
BinaryTree::BinaryTree() : root_(nullptr) {}

// Destructor
BinaryTree::~BinaryTree() { DeleteTree(root_); }

// Recursively delete tree nodes
void BinaryTree::DeleteTree(BinaryTreeNode* node) {
  root_ = nullptr;
  // if (node == nullptr) {
  //   return;
  // }
  // DeleteTree(node->GetLeft());
  // DeleteTree(node->GetRight());
  // delete node;
}

// Find the best split for the given dataset

void BinaryTree::FindBestSplit(const DataSet& data_set,
                               double& best_feature_index,
                               double& best_split_value) const {
  double best_impurity_drop = -1.0;
  for (int i = 0; i < data_set.GetNumFeatures(); i++) {
    for (int j = 0; j < data_set.GetNumObservations(); j++) {
      double split_value = data_set.GetFeatureValue(i, j);
      DataSet left, right;
      data_set.Split(i, split_value, left, right, data_set);

      double entropy_left = left.GetEntropy();

      double entropy_right = right.GetEntropy();

      int n = left.GetNumObservations() / data_set.GetNumObservations();

      double impurity_drop =
          data_set.GetEntropy() - (n)*entropy_left - (1 - n) * entropy_right;
      cout << impurity_drop << endl;
      if (impurity_drop > best_impurity_drop) {
        best_impurity_drop = impurity_drop;
        best_feature_index = i;
        best_split_value = split_value;
      }
    }
  }
}

void BinaryTree::Grow(const DataSet& data_set) {
  // Base case: If the dataset is pure (no more splits possible), stop recursion

  if (data_set.IsPure()) {
    int label = data_set.GetMajorityLabel();
    root_ = new BinaryTreeNode(
        label);               // Create a leaf node with the majority label
    root_->SetLeft(nullptr);  // Ensure no children are set for leaf nodes
    root_->SetRight(nullptr);
    return;
  }

  double best_feature_index = -1.0;
  double best_split_value = 0.0;

  // Find the best feature and value for splitting
  FindBestSplit(data_set, best_feature_index, best_split_value);
  cout << "best_split_value: " << best_split_value << endl;

  if (best_feature_index == -1) {
    std::cout << "No best split found. Stopping recursion." << std::endl;
    return;
  }

  // Split the dataset based on the best split
  DataSet left, right;

  data_set.Split(best_feature_index, best_split_value, left, right, data_set);

  // If either side of the split is empty, stop recursion to avoid infinite
  // loops
  if (left.IsEmpty() || right.IsEmpty()) {
    std::cout << "One of the datasets is empty. Stopping recursion."
              << std::endl;
    return;
  }

  // Create an internal node with the split value and impurity
  double impurity = data_set.GetEntropy();
  root_ = new BinaryTreeNode(best_split_value, best_feature_index, impurity);

  // Recursively grow the left and right subtrees
  if (!left.IsEmpty()) {
    BinaryTree* left_tree =
        new BinaryTree();   // Create a new tree for the left subtree
    left_tree->Grow(left);  // Recursively grow the left subtree
    root_->SetLeft(left_tree->GetRoot());  // Attach the left subtree
    // delete left_tree;  // Clean up temporary tree after attaching
  }

  if (!right.IsEmpty()) {
    BinaryTree* right_tree =
        new BinaryTree();     // Create a new tree for the right subtree
    right_tree->Grow(right);  // Recursively grow the right subtree
    root_->SetRight(right_tree->GetRoot());  // Attach the right subtree
    // delete right_tree;  // Clean up temporary tree after attaching
  }
}

// Get the root of the tree
BinaryTreeNode* BinaryTree::GetRoot() const { return root_; }

// Show the binary tree
void BinaryTree::Show() const { ShowNode(root_, 0); }

// Show the classifier
void BinaryTree::ShowClassifier() const {
  if (root_ == nullptr) {
    std::cout << "The classifier has not been trained." << std::endl;
    return;
  }
  ShowNode(root_, 0);  // Call the helper function to print the tree structure
}

// Recursive function to show nodes of the tree
void BinaryTree::ShowNode(BinaryTreeNode* node, int depth) const {
  if (node == nullptr) {
    return;  // Base case: if the node is null, just return
  }

  // If the node is a leaf, print the label only
  if (node->IsLeaf()) {
    std::cout << std::string(depth * 2, ' ')     // Indent based on depth
              << node->GetLabel() << std::endl;  // Print only the label
  } else {
    // Print current node: split dimension, split value, and impurity
    std::cout << std::string(depth * 2, ' ')      // Indent based on depth
              << node->GetFeatureIndex() << ", "  // Print split dim
              << std::fixed << std::setprecision(3) << node->GetSplitValue()
              << ", "  // Print split value
              << std::fixed << std::setprecision(3) << node->GetImpurity()
              << std::endl;  // Print impurity
  }

  // Recursively show the left and right children
  if (!node->IsLeaf()) {
    ShowNode(node->GetLeft(), depth + 1);   // Show left child
    ShowNode(node->GetRight(), depth + 1);  // Show right child
  }
}

// Classify an observation
int BinaryTree::Classify(int x1, int x2) const {
  BinaryTreeNode* current = root_;
  while (!current->IsLeaf()) {
    if (x1 >= current->GetSplitValue()) {
      current = current->GetRight();
    } else {
      current = current->GetLeft();
    }
  }
  return current->GetLabel();
}
