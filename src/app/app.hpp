#ifndef APP_H
#define APP_H
#include <string>
#include <vector>

#include "BinaryTree.h"
#include "BinaryTreeNode.h"
#include "DataSet.hpp"

/*
*****************************
  This is where you start!
  However, make sure you do not not write all your code in a single file!
*****************************
*/

class App {
 private:
  std::vector<double> x1_values_;
  std::vector<double> x2_values_;
  std::vector<int> labels_;
  DataSet data_set_;
  BinaryTree* classifier_;

 public:
  App(void);
  ~App(void);
  void AddData(std::string, std::string, std::string);
  void ClearData(void);
  void ShowData(void);
  void TrainClassifier(void);
  void Classify(std::string, std::string);
  void ShowClassifier(void);
  void CreateDataSetTest(void);
};

#endif  // APP_H
