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

  x1_values.push_back(x1);
  x2_values.push_back(x2);
  labels.push_back(label);
}

void App::ClearData() {
  x1_values.clear();
  x2_values.clear();
  labels.clear();
}

void App::ShowData() {
  // TODO
}

void App::TrainClassifier() {
  // TODO
}

void App::Classify(std::string x_in_, std::string y_in_) {
  // TODO
}

void App::ShowClassifier() {
  // TODO
}
