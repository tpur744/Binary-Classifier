#ifndef DATASET_HPP
#define DATASET_HPP
#include <vector>

class DataSet {
 public:
  DataSet();
  void AddObservation(double x1, double x2, int label);
  int GetNumObservations() const;
  int GetPositiveCount() const;
  int GetNegativeCount() const;
  const std::vector<double>& GetX1Values() const;
  const std::vector<double>& GetX2Values() const;
  const std::vector<int>& GetLabels() const;
  double GetEntropy() const;
  int GetNumFeatures() const;
  double GetFeatureValue(int feature_index, int observation_index) const;
  void Split(int feature_index, double split_value, DataSet& left,
             DataSet& right) const;

  void ShowData(void);
  void ClearData(void);
  bool IsPure() const;

 private:
  std::vector<double> x1_values_;
  std::vector<double> x2_values_;
  std::vector<int> labels_;
};

#endif