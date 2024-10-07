#include "DataSet.hpp"

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

double DataSet::GetEntropy() const {
  int n = GetNumObservations();
  int n1 = GetPositiveCount();
  int n2 = GetNegativeCount();
  if (n1 == 0 || n2 == 0) {
    return 0.0;
  }
  double p1 = (double)n1 / n;
  double p2 = (double)n2 / n;

  return -(p1 * log2(p1) - p2 * log2(p2));
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
                    DataSet& right) const {
  for (int i = 0; i < GetNumObservations(); i++) {
    if (GetFeatureValue(feature_index, i) < split_value) {
      left.AddObservation(x1_values_[i], x2_values_[i], labels_[i]);
    } else {
      right.AddObservation(x1_values_[i], x2_values_[i], labels_[i]);
    }
  }
}