#ifndef dump_hpp
#define dump_hpp

#include <iostream>
#include <fstream>
#include <vector>

template <class T>
class Dumper {
public:
//  Dumper();
  Dumper(int params_number, std::ofstream &outputStream);
//  Dumper(int params_number, std::string &outputFilename, std::vector<std::string> &params_names);
  void update(std::vector<T> &new_data);
  void dump();
  
private:
  std::vector<std::vector<T> > data_;
  std::vector<std::string> params_names_;
  std::ofstream & outputStream_;
  int params_number_;
};


template <class T>
Dumper<T>::Dumper(int params_number, std::ofstream &outputStream)
        :params_number_(params_number), data_(params_number), outputStream_(outputStream) {
}

//template <class T>
//Dumper<T>::Dumper(int params_number, std::string &outputFilename,
//               std::vector<std::string> &params_names)
//:params_number_(params_number), data_(params_number), outputStream_(outputFilename.c_str()),
//params_names_(params_names) {}


template <class T>
void Dumper<T>::update(std::vector<T> &new_data) {
  for (size_t i = 0; i < new_data.size(); ++i) {
    data_[i].push_back(new_data[i]);
  }
}


template <class T>
void Dumper<T>::dump() {
  if (params_names_.empty()) {
    for (size_t i = 0; i < params_number_; ++i) {
      params_names_.push_back(std::to_string(i+1) + "param");
    }
  }
  for (size_t i = 0; i < params_number_; ++i) {
    outputStream_ << params_names_[i];
    if (i != params_number_ - 1) {
      outputStream_ << ",";
    } else {
      outputStream_ << "\n";
    }
  }
  for (size_t i = 0; i < data_[0].size(); ++i) {
    for (size_t j = 0; j < params_number_; ++j) {
      outputStream_ << data_[j][i];
      if (j != params_number_ - 1) {
        outputStream_ << ",";
      } else {
        outputStream_ << "\n";
      }
    }
  }
}

#endif /* dump_hpp */
