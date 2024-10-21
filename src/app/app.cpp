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
  AddData(to_string(0.9074), to_string(0.5488), to_string(-1));
  AddData(to_string(0.9529), to_string(0.6392), to_string(-1));
  AddData(to_string(0.5635), to_string(0.7734), to_string(-1));
  AddData(to_string(0.9567), to_string(0.9788), to_string(-1));
  AddData(to_string(0.8162), to_string(0.9824), to_string(-1));
  AddData(to_string(0.3279), to_string(0.3789), to_string(-1));
  AddData(to_string(0.0179), to_string(0.3716), to_string(-1));
  AddData(to_string(0.4246), to_string(0.1961), to_string(-1));
  AddData(to_string(0.4670), to_string(0.3277), to_string(-1));
  AddData(to_string(0.3394), to_string(0.0856), to_string(-1));
  AddData(to_string(0.0788), to_string(0.5709), to_string(1));
  AddData(to_string(0.4853), to_string(0.7109), to_string(1));
  AddData(to_string(0.4786), to_string(0.9579), to_string(1));
  AddData(to_string(0.2427), to_string(0.8961), to_string(1));
  AddData(to_string(0.4001), to_string(0.9797), to_string(1));
  AddData(to_string(0.8530), to_string(0.4117), to_string(1));
  AddData(to_string(0.5159), to_string(0.3474), to_string(1));
  AddData(to_string(0.6385), to_string(0.1585), to_string(1));
  AddData(to_string(0.5231), to_string(0.4751), to_string(1));
  AddData(to_string(0.5486), to_string(0.0172), to_string(1));

  classifier_ = nullptr;
  // TODO
}

App::~App() {
  // if (classifier_) {
  //   delete classifier_;
  //   classifier_ = nullptr;
  // }
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
  cout << "Training classifier..." << endl;
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
    cout << "Deleting old classifier..." << endl;
    delete classifier_;
    classifier_ = nullptr;
  }
  if (data_set_.IsEmpty()) {
    cout << "No data to train on." << endl;
    return;
  }
  if (classifier_ == nullptr) {
    // classifier_ = new BinaryTree();
    cout << "Creating new classifier..." << endl;
    // return;
  }
  // Create a new classifier and grow the tree
  classifier_ = new BinaryTree();
  classifier_->Grow(data_set_);
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
