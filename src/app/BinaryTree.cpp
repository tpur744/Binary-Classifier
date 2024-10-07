#include "BinaryTree.h"

BinaryTree::BinaryTree() { root_ = nullptr; }

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
                               double& best_split_value) {
  double best_impurity_drop = -1.;
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