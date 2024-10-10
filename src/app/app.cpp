#include "app.hpp"

#include <iostream>

#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include "DataSet.hpp"
#include "message.hpp"
#include "utils.hpp"

using namespace std;

/*
*****************************
  This is where you start!
  However, make sure you do not not write all your code in a single file!
*****************************
*/

App::App() {
  classifier_ = nullptr;
  // TODO
}

App::~App() {
  // TODO
}

void App::AddData(std::string x_in_, std::string y_in_, std::string label_in_) {
  double x1 = stod(x_in_);
  double x2 = stod(y_in_);
  int label = stoi(label_in_);

  if (label != -1 && label != 1) {
    cout << "Label must be either -1 or 1." << endl;
    return;
  }

  data_set_.AddObservation(x1, x2, label);
}

void App::ClearData() {
  data_set_.ClearData();
  if (classifier_) {
    delete classifier_;
    classifier_ = nullptr;
  }
}

void App::ShowData() { data_set_.ShowData(); }

void App::TrainClassifier() {
  int positive_count = 0;
  int negative_count = 0;
  positive_count = data_set_.GetPositiveCount();
  negative_count = data_set_.GetNegativeCount();

  // Ensure there is at least one observation from both categories
  if (positive_count == 0 || negative_count == 0) {
    std::cout << "Cannot train classifier without at least one observation "
                 "from each category."
              << std::endl;
    return;
  }

  // Delete the old classifier if it exists
  if (classifier_) {
    delete classifier_;
    classifier_ = nullptr;
  }

  // Create a new classifier and grow the tree
  classifier_ = new BinaryTree();
  classifier_->Grow(data_set_);

  std::cout << "Classifier trained successfully!" << std::endl;
}

void App::Classify(std::string x_in_, std::string y_in_) {
  // TODO
}

void App::ShowClassifier() {
  if (!classifier_) {
    std::cout << "Cannot perform that operation without first training a "
                 "classifier."
              << std::endl;
    return;
  }
  classifier_->Show();
}
