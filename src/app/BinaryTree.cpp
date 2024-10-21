#include "BinaryTree.h"

#include <iomanip>
#include <iostream>
using namespace std;
#include <iomanip>
#include <iostream>

#include "BinaryTree.h"
#include "DataSet.hpp"
using namespace std;
#include "DataSet.hpp"

// Constructor
BinaryTree::BinaryTree() : root_(nullptr) {}

// Destructor
BinaryTree::~BinaryTree() { DeleteTree(root_); }

// Recursively delete tree nodes
void BinaryTree::DeleteTree(BinaryTreeNode* node) { root_ = nullptr; }

// Find the best split for the given dataset

void BinaryTree::FindBestSplit(const DataSet& data_set,
                               double* best_feature_index,
                               double* best_split_value) const {
  double best_impurity_drop = -1.0;
  for (int i = 0; i < data_set.GetNumFeatures(); i++) {
    for (int j = 0; j < data_set.GetNumObservations(); j++) {
      double split_value = data_set.GetFeatureValue(i, j);
      DataSet left, right;
      data_set.Split(i, split_value, left, right, data_set);

      double entropy_right = right.GetEntropy();
      double entropy_left = left.GetEntropy();

      double n = static_cast<double>(left.GetNumObservations()) /
                 data_set.GetNumObservations();

      double impurity_drop =
          data_set.GetEntropy() - (n)*entropy_left - (1 - n) * entropy_right;
      if (impurity_drop > best_impurity_drop) {
        best_impurity_drop = impurity_drop;
        *best_feature_index = i;
        *best_split_value = split_value;
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
  FindBestSplit(data_set, &best_feature_index, &best_split_value);

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
  static int leaf_count = 0;  // Keep track of the number of leaf nodes
  if (node == nullptr) {
    return;  // Base case: if the node is null, just return
  }

  // If the node is a leaf, print the label only
  if (node->IsLeaf()) {
    std::cout << std::string(depth * 3,
                             ' ')  // Indent based on depth (3 spaces)
              << "label: " << node->GetLabel()  // Print the label
              << std::endl;                     // End of line
    leaf_count++;                               // Increment the leaf count
  } else {
    // Print current node: split dimension, split value, and impurity
    std::cout << std::string(depth * 3,
                             ' ')  // Indent based on depth (3 spaces)
              << node->GetFeatureIndex() << ", "  // Print split dim
              << std::fixed << std::setprecision(3) << node->GetSplitValue()
              << ", "  // Print split value
              << std::fixed << std::setprecision(3) << node->GetImpurity()
              << std::endl;  // End of line
  }

  // Recursively show the left and right children
  if (!node->IsLeaf()) {
    ShowNode(node->GetLeft(), depth + 1);   // Show left child
    ShowNode(node->GetRight(), depth + 1);  // Show right child
  }

  // After the entire tree has been traversed, print the number of leaf nodes
  if (depth == 0) {  // Ensure this happens only at the root level
    std::cout << "Binary classification tree is comprised of " << leaf_count
              << " leaf node(s)." << std::endl;
    leaf_count = 0;  // Reset leaf count for the next tree printout
  }
}

// Show the classifier
// void BinaryTree::ShowClassifier() const {
//   if (root_ == nullptr) {
//     std::cout << "The classifier has not been trained." << std::endl;
//     return;
//   }
//   ShowNode(root_, 0);  // Call the helper function to print the tree
//   structure
// }

// // Recursive function to show nodes of the tree
// void BinaryTree::ShowNode(BinaryTreeNode* node, int depth) const {
//   static int leaf_count = 0;  // Keep track of the number of leaf nodes
//   if (node == nullptr) {
//     return;  // Base case: if the node is null, just return
//   }

//   // If the node is a leaf, print the label only
//   if (node->IsLeaf()) {
//     std::cout << std::string(depth * 2, ' ')  // Indent based on depth
//               << "label: " << node->GetLabel()
//               << std::endl;  // Print only the label
//     leaf_count++;            // Increment the leaf count
//   } else {
//     // Print current node: split dimension, split value, and impurity
//     std::cout << std::string(depth * 2, ' ')      // Indent based on depth
//               << node->GetFeatureIndex() << ", "  // Print split dim
//               << std::fixed << std::setprecision(3) << node->GetSplitValue()
//               << ", "  // Print split value
//               << std::fixed << std::setprecision(3) << node->GetImpurity()
//               << std::endl;  // Print impurity
//   }

//   // Recursively show the left and right children
//   if (!node->IsLeaf()) {
//     ShowNode(node->GetLeft(), depth + 1);   // Show left child
//     ShowNode(node->GetRight(), depth + 1);  // Show right child
//   }

//   // after tree has been traversed, print the number of leaf nodes
//   if (depth == 0) {
//     std::cout << "Binary classification tree is comprised of " << leaf_count
//               << " leaf node(s)." << std::endl;
//     leaf_count = 0;  // Reset leaf count for next tree
//   }
// }

// Classify an observation
int BinaryTree::Classify(double x1, double x2) const {
  BinaryTreeNode* current = root_;
  while (!current->IsLeaf()) {
    int feature_index = current->GetFeatureIndex();  // Check which feature the
                                                     // node is splitting on
    double split_value = current->GetSplitValue();

    // If the split is on feature 0 (x1)
    if (feature_index == 0) {
      if (x1 >= split_value) {
        current = current->GetRight();
      } else {
        current = current->GetLeft();
      }
    }
    // If the split is on feature 1 (x2)
    else if (feature_index == 1) {
      if (x2 >= split_value) {
        current = current->GetRight();
      } else {
        current = current->GetLeft();
      }
    }
  }

  return current->GetLabel();
}
