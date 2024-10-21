#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "BinaryTreeNode.h"
#include "DataSet.hpp"

class BinaryTree {
 public:
  BinaryTree();
  ~BinaryTree();

  void Grow(const DataSet& data_set);  // Train
  void DeleteTree(BinaryTreeNode* node);
  void FindBestSplit(const DataSet& data_set, double& best_feature_index,
                     double& best_split_value) const;

  BinaryTreeNode* GetRoot() const;
  void Show() const;
  void ShowNode(BinaryTreeNode* node, int depth) const;
  void GrowSubtree(BinaryTreeNode* node, const DataSet& data_set);
  void ShowClassifier() const;
  int Classify(int x1, int x2) const;

 private:
  BinaryTreeNode* root_;
};

#endif