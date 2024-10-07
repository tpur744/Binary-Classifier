#include "app.hpp"

#include <iostream>

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

  x1_values_.push_back(x1);
  x2_values_.push_back(x2);
  labels_.push_back(label);
}

void App::ClearData() {
  x1_values_.clear();
  x2_values_.clear();
  labels_.clear();
}

void App::ShowData() {
  if (x1_values_.size() == 0) {
    std::cout << "No observations in training data set." << std::endl;
    return;
  }

  for (size_t i = 0; i < x1_values_.size(); ++i) {
    // Format each feature to three decimal places
    double x1_formatted = std::round(x1_values_[i] * 1000) / 1000;
    double x2_formatted = std::round(x2_values_[i] * 1000) / 1000;

    // Output the observation
    std::cout << i << "\t" << x1_formatted << "\t" << x2_formatted << "\t"
              << labels_[i] << std::endl;
  }
}

void App::TrainClassifier() {
  int positive_count = data_set_.GetPositiveCount();
  int negative_count = data_set_.GetNegativeCount();

  if (positive_count == 0 || negative_count == 0) {
    cout << "Cannot perform that operation without at least one observation "
            "from each category in training data set."
         << endl;
    return;
  }
  // delete classifier_;
  // classifier_ = new BinaryClassifier();
}

void App::Classify(std::string x_in_, std::string y_in_) {
  // TODO
}

void App::ShowClassifier() {
  // TODO
}
