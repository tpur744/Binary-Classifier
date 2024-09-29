#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "app/launcher.hpp"
#include "app/utils.hpp"

using namespace std;

/*
*****************************
  DO NOT MODIFY EXISTING METHODS
  However, you are welcome to add additional test cases.
*****************************
*/

enum TestResult { TEST_RESULT_PASS, TEST_RESULT_FAIL };

#define RUN_COMMAND(command_with_args)                         \
  cout << app.GetCommandPrefix() << command_with_args << endl; \
  app.ProcessCommand(command_with_args);

#define __FILENAME__ \
  (std::strrchr(__FILE__, '/') ? std::strrchr(__FILE__, '/') + 1 : __FILE__)

#define EXPECT_CONTAINS(expected)                                              \
  if (still_capturing_cout) {                                                  \
    still_capturing_cout = false;                                              \
    output = buffer.str();                                                     \
    std::cout.rdbuf(old);                                                      \
    std::cout << output << std::endl;                                          \
  }                                                                            \
  if (output.find(expected) == std::string::npos) {                            \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__            \
         << " on line " << __LINE__ << endl                                    \
         << "\tExpected '" << expected                                         \
         << "' in the output, but it was not found." << endl                   \
         << endl                                                               \
         << "----------------------------------------------------------------" \
            "------------"                                                     \
         << endl                                                               \
         << endl;                                                              \
    return TEST_RESULT_FAIL;                                                   \
  }

#define EXPECT_DOES_NOT_CONTAINS(expected, ignore_case)             \
  output = buffer.str();                                            \
  if (Utils::Contains(output, expected, ignore_case)) {             \
    cerr << "FAILED Test " << test_number << " in " << __FILENAME__ \
         << " on line " << __LINE__ << endl                         \
         << "\tExpected '" << expected                              \
         << "' to NOT be in the output, but it was." << endl        \
         << endl;                                                   \
    return TEST_RESULT_FAIL;                                        \
  }

int main(int argc, char *argv[]) {
  Launcher app;
  string output = "";
  bool still_capturing_cout = true;
  std::stringstream buffer;
  std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

  int test_number = std::stoi(argv[1]);
  switch (test_number) {
    case 1:  // Show_Data1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("No observations in training data set.");
      break;

    case 2:  // Add_Data1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0\t0.907\t0.549\t-1\n"
          "1\t0.953\t0.639\t-1");
      break;

    case 3:  // Add_Data2
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 2");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS("Label must be either -1 or 1.");
      EXPECT_CONTAINS("0\t0.953\t0.639\t-1");
      break;

    case 4:  // Clear_Data1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9567 0.9788 -1");
      RUN_COMMAND("add-data 0.8162 0.9824 -1");
      RUN_COMMAND("add-data 0.3279 0.3789 -1");
      RUN_COMMAND("show-data");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0\t0.907\t0.549\t-1\n"
          "1\t0.953\t0.639\t-1");
      EXPECT_CONTAINS(
          "0\t0.957\t0.979\t-1\n"
          "1\t0.816\t0.982\t-1\n"
          "2\t0.328\t0.379\t-1");
      break;

    case 5:  // Show_Data2
      RUN_COMMAND("add-data 0.4246 0.1961 -1")
      RUN_COMMAND("add-data 0.4670 0.3277 -1")
      RUN_COMMAND("add-data 0.3394 0.0856 -1")
      RUN_COMMAND("add-data 0.0788 0.5709 1")
      RUN_COMMAND("add-data 0.4853 0.7109 1")
      RUN_COMMAND("add-data 0.4786 0.9579 1")
      RUN_COMMAND("show-data")
      RUN_COMMAND("clear-data")
      RUN_COMMAND("show-data")
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0\t0.425\t0.196\t-1\n"
          "1\t0.467\t0.328\t-1\n"
          "2\t0.339\t0.086\t-1\n"
          "3\t0.079\t0.571\t1\n"
          "4\t0.485\t0.711\t1\n"
          "5\t0.479\t0.958\t1");
      EXPECT_CONTAINS("No observations in training data set");
      break;

    case 6:  // Show_Classifier1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "Cannot perform that operation without first training a classifier");
      break;

    case 7:  // Show_Classifier2
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("add-data 0.5635 0.7734 -1");
      RUN_COMMAND("add-data 0.9567 0.9788 -1");
      RUN_COMMAND("add-data 0.8162 0.9824 -1");
      RUN_COMMAND("add-data 0.3279 0.3789 -1");
      RUN_COMMAND("add-data 0.0179 0.3716 -1");
      RUN_COMMAND("add-data 0.4246 0.1961 -1");
      RUN_COMMAND("add-data 0.4670 0.3277 -1");
      RUN_COMMAND("add-data 0.3394 0.0856 -1");
      RUN_COMMAND("add-data 0.0788 0.5709 1");
      RUN_COMMAND("add-data 0.4853 0.7109 1");
      RUN_COMMAND("add-data 0.4786 0.9579 1");
      RUN_COMMAND("add-data 0.2427 0.8961 1");
      RUN_COMMAND("add-data 0.4001 0.9797 1");
      RUN_COMMAND("add-data 0.8530 0.4117 1");
      RUN_COMMAND("add-data 0.5159 0.3474 1");
      RUN_COMMAND("add-data 0.6385 0.1585 1");
      RUN_COMMAND("add-data 0.5231 0.4751 1");
      RUN_COMMAND("add-data 0.5486 0.0172 1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("classify 0.99 0.99");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0, 0.907, 1.000\n"
          "   0, 0.479, 0.977\n"
          "      1, 0.571, 0.954\n"
          "         label: -1\n"
          "         label: 1\n"
          "      1, 0.773, 0.764\n"
          "         label: 1\n"
          "         0, 0.564, 0.918\n"
          "            label: 1\n"
          "            label: -1\n"
          "   label: -1\n"
          "Binary classification tree is comprised of 6 leaf node(s).");
      break;

    case 8:  // Train_Classifier1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "Cannot perform that operation without at least one observation from "
          "each category in training data set.");
      break;

    case 9:  // Classify1
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("add-data 0.5635 0.7734 -1");
      RUN_COMMAND("add-data 0.9567 0.9788 -1");
      RUN_COMMAND("add-data 0.8162 0.9824 -1");
      RUN_COMMAND("add-data 0.3279 0.3789 -1");
      RUN_COMMAND("add-data 0.0179 0.3716 -1");
      RUN_COMMAND("add-data 0.4246 0.1961 -1");
      RUN_COMMAND("add-data 0.4670 0.3277 -1");
      RUN_COMMAND("add-data 0.3394 0.0856 -1");
      RUN_COMMAND("add-data 0.0788 0.5709 1");
      RUN_COMMAND("add-data 0.4853 0.7109 1");
      RUN_COMMAND("add-data 0.4786 0.9579 1");
      RUN_COMMAND("add-data 0.2427 0.8961 1");
      RUN_COMMAND("add-data 0.4001 0.9797 1");
      RUN_COMMAND("add-data 0.8530 0.4117 1");
      RUN_COMMAND("add-data 0.5159 0.3474 1");
      RUN_COMMAND("add-data 0.6385 0.1585 1");
      RUN_COMMAND("add-data 0.5231 0.4751 1");
      RUN_COMMAND("add-data 0.5486 0.0172 1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("classify 0.99 0.99");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0, 0.907, 1.000\n"
          "   0, 0.479, 0.977\n"
          "      1, 0.571, 0.954\n"
          "         label: -1\n"
          "         label: 1\n"
          "      1, 0.773, 0.764\n"
          "         label: 1\n"
          "         0, 0.564, 0.918\n"
          "            label: 1\n"
          "            label: -1\n"
          "   label: -1\n"
          "Binary classification tree is comprised of 6 leaf node(s).");
      EXPECT_CONTAINS("Observation classified as: -1");
      break;

    case 10:  // Classify2
      RUN_COMMAND("clear-data");
      RUN_COMMAND("add-data 0.9074 0.5488 -1");
      RUN_COMMAND("add-data 0.9529 0.6392 -1");
      RUN_COMMAND("add-data 0.5635 0.7734 -1");
      RUN_COMMAND("add-data 0.9567 0.9788 -1");
      RUN_COMMAND("add-data 0.8162 0.9824 -1");
      RUN_COMMAND("add-data 0.3279 0.3789 -1");
      RUN_COMMAND("add-data 0.0179 0.3716 -1");
      RUN_COMMAND("add-data 0.4246 0.1961 -1");
      RUN_COMMAND("add-data 0.4670 0.3277 -1");
      RUN_COMMAND("add-data 0.3394 0.0856 -1");
      RUN_COMMAND("add-data 0.0788 0.5709 1");
      RUN_COMMAND("add-data 0.4853 0.7109 1");
      RUN_COMMAND("add-data 0.4786 0.9579 1");
      RUN_COMMAND("add-data 0.2427 0.8961 1");
      RUN_COMMAND("add-data 0.4001 0.9797 1");
      RUN_COMMAND("add-data 0.8530 0.4117 1");
      RUN_COMMAND("add-data 0.5159 0.3474 1");
      RUN_COMMAND("add-data 0.6385 0.1585 1");
      RUN_COMMAND("add-data 0.5231 0.4751 1");
      RUN_COMMAND("add-data 0.5486 0.0172 1");
      RUN_COMMAND("train-classifier");
      RUN_COMMAND("show-classifier");
      RUN_COMMAND("classify 0.99 0.99");
      RUN_COMMAND("classify 0.01 0.99");
      RUN_COMMAND("classify 0.99 0.01");
      RUN_COMMAND("classify 0.01 0.01");
      RUN_COMMAND("exit");
      EXPECT_CONTAINS(
          "0, 0.907, 1.000\n"
          "   0, 0.479, 0.977\n"
          "      1, 0.571, 0.954\n"
          "         label: -1\n"
          "         label: 1\n"
          "      1, 0.773, 0.764\n"
          "         label: 1\n"
          "         0, 0.564, 0.918\n"
          "            label: 1\n"
          "            label: -1\n"
          "   label: -1\n"
          "Binary classification tree is comprised of 6 leaf node(s).");
      EXPECT_CONTAINS("Observation classified as: -1");
      EXPECT_CONTAINS("Observation classified as: 1");
      EXPECT_CONTAINS("Observation classified as: -1");
      EXPECT_CONTAINS("Observation classified as: -1");
      break;

    default:
      cerr << "Test case not found: #" << test_number << endl;
      return TEST_RESULT_FAIL;
  }

  cerr << "PASSED Test " << test_number << "." << endl
       << endl
       << "--------------------------------------------------------------------"
          "--------"
       << endl
       << endl;

  return TEST_RESULT_PASS;
}
