#ifndef DATASET_H
#define DATASET_H
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

 private:
  std::vector<double> x1_values_;
  std::vector<double> x2_values_;
  std::vector<int> labels_;
};

#endif