#include "DataSet.h"

DataSet::DataSet() {}

void DataSet::AddObservation(double x1, double x2, int label) {
  x1_values_.push_back(x1);
  x2_values_.push_back(x2);
  labels_.push_back(label);
}

int DataSet::GetNumObservations() const { return x1_values_.size(); }

int DataSet::GetPositiveCount() const {
  int count = 0;
  for (int label : labels_) {
    if (label == 1) {
      count++;
    }
  }
  return count;
}

int DataSet::GetNegativeCount() const {
  int count = 0;
  for (int label : labels_) {
    if (label == -1) {
      count++;
    }
  }
  return count;
}

const std::vector<double>& DataSet::GetX1Values() const { return x1_values_; }

const std::vector<double>& DataSet::GetX2Values() const { return x2_values_; }

const std::vector<int>& DataSet::GetLabels() const { return labels_; }
