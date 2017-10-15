#include "dumper.hpp"

//template <class T>
//Dumper<T>::Dumper()
//:params_number_(6), data_(6), outputStream_("output.csv") {}

//template <class T>
//Dumper<T>::Dumper(int params_number, std::ofstream &outputStream)
//:params_number_(params_number), data_(params_number), outputStream_(outputStream) {
//}
//
////template <class T>
////Dumper<T>::Dumper(int params_number, std::string &outputFilename,
////               std::vector<std::string> &params_names)
////:params_number_(params_number), data_(params_number), outputStream_(outputFilename.c_str()),
////params_names_(params_names) {}
//
//template <class T>
//void Dumper<T>::update(std::vector<T> &new_data) {
//  for (size_t i = 0; i < new_data.size(); ++i) {
//    data_[i].push_back(new_data[i]);
//  }
//}
//
//template <class T>
//void Dumper<T>::dump() {
//  if (params_names_.empty()) {
//    for (size_t i = 0; i < params_number_; ++i) {
//      params_names_.push_back(std::to_string(i+1) + "param");
//    }
//  }
//  for (size_t i = 0; i < params_number_; ++i) {
//    outputStream_ << params_names_[i];
//    if (i != params_number_ - 1) {
//      outputStream_ << ",";
//    } else {
//      outputStream_ << "\n";
//    }
//  }
//  for (size_t i = 0; i < data_[0].size(); ++i) {
//    for (size_t j = 0; j < params_number_; ++j) {
//      outputStream_ << data_[j][i];
//      if (j != params_number_ - 1) {
//        outputStream_ << ",";
//      } else {
//        outputStream_ << "\n";
//      }
//    }
//  }
//}
