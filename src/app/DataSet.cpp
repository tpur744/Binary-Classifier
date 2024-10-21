#include "DataSet.hpp"
using namespace std;
#include <iostream>
DataSet::DataSet()
    : x1_values_(),
      x2_values_(),
      labels_() {}  // Initialize the vectors in the constructor

void DataSet::AddObservation(double x1, double x2, int label) {
  x1_values_.push_back(x1);
  x2_values_.push_back(x2);
  labels_.push_back(label);
}

int DataSet::GetNumObservations() const { return x1_values_.size(); }

int DataSet::GetPositiveCount() const {
  int pos_count = 0;
  for (size_t i = 0; i < labels_.size();
       ++i) {  // Use size_t for the index variable
    if (labels_[i] == 1) {
      pos_count++;
    }
  }
  return pos_count;
}

int DataSet::GetNegativeCount() const {
  int neg_count = 0;
  for (size_t i = 0; i < labels_.size();
       ++i) {  // Use size_t for the index variable
    if (labels_[i] == -1) {
      neg_count++;
    }
  }
  return neg_count;
}

const std::vector<double>& DataSet::GetX1Values() const { return x1_values_; }

const std::vector<double>& DataSet::GetX2Values() const { return x2_values_; }

const std::vector<int>& DataSet::GetLabels() const { return labels_; }

double DataSet::GetEntropy() const {
  int n = GetNumObservations();
  // int n1 = GetPositiveCount();
  // int n2 = GetNegativeCount();
  float n1 = 0.0f;
  float n2 = 0.0f;
  if (n == 0) {
    return 0.0;
  }
  if (n == 1) {
    return 0.0;
  }
  for (int i = 0; i < n; i++) {
    if (labels_[i] == 1) {
      n1++;
    } else {
      n2++;
    }
  }
  if (n1 == 0 || n2 == 0) {
    return 0.0;
  }
  // double impurity = (-p1 * log2(p1)) - (p2 * log2(p2));
  double impurity = -(n1 / n) * log2(n1 / n) - (n2 / n) * log2(n2 / n);
  return impurity;
}

int DataSet::GetMajorityLabel() const {
  return GetPositiveCount() > GetNegativeCount() ? 1 : -1;
}

int DataSet::GetNumFeatures() const { return 2; }

double DataSet::GetFeatureValue(int feature_index,
                                int observation_index) const {
  if (feature_index == 0) {
    return x1_values_[observation_index];
  } else {
    return x2_values_[observation_index];
  }
}

void DataSet::Split(int feature_index, double split_value, DataSet& left,
                    DataSet& right, const DataSet& data_set) const {
  double feature_value = -1.0;
  for (int i = 0; i < data_set.GetNumObservations(); i++) {
    if (feature_index == 0) {
      feature_value = x1_values_[i];
    } else {
      feature_value = x2_values_[i];
    }
    if (feature_value >= split_value) {
      right.AddObservation(x1_values_[i], x2_values_[i], labels_[i]);
    } else if (feature_value < split_value) {
      left.AddObservation(x1_values_[i], x2_values_[i], labels_[i]);
    }
  }
}

int DataSet::GetLabel(int index) const { return labels_[index]; }

void DataSet::ShowData(void) {
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

void DataSet::ClearData(void) {
  x1_values_.clear();
  x2_values_.clear();
  labels_.clear();
}

bool DataSet::IsPure() const { return GetEntropy() == 0.0; }

bool DataSet::IsEmpty() const {
  return x1_values_.empty();  // Check just one vector as all are same size
}
