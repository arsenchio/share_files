#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <dirent.h>
#include "dumper.hpp"

std::vector<std::vector<float> > ReadFile(std::string path) {
  std::vector<std::vector<float> > data(6);
  std::ifstream myinput(path);
  std::string line;
  std::getline(myinput, line);
  while (std::getline(myinput, line)) {
    std::stringstream lineStream(line);
    std::string token;
    std::getline(lineStream, token, ',');
    int i = 0;
    while (std::getline(lineStream, token, ',')) {
      float val = std::stof(token);
      data[i++].push_back(val);
    }
  }
  
  return data;
}

std::vector<std::vector<std::vector<float> > > GenMatrices(std::string path) {
  DIR *dir;
  dirent *pdir;
  std::vector<std::string> files;
  
  dir = opendir(path.c_str());
  
  while ((pdir = readdir(dir))!=NULL) {
    if ((pdir->d_name)[0] >= 'A' && (pdir->d_name)[0] <= 'Z') {
      files.push_back(pdir->d_name);
    }
  }
  
  std::vector<std::vector<std::vector<float> > > matrices(6);
  
  for (int i = 0; i < files.size(); ++i) {
    std::vector<std::vector<float> > data;
    data = ReadFile(path + "/" + files[i]);
    std::cout << files[i] << ": " << data.size() << ' ' << data[0].size() << "\n";
    for (int j = 0; j < data.size(); ++j) {
      matrices[j].push_back(data[j]);
    }
  }
  
  return matrices;
}

//int main(int argc, char* argv[]) {
//  std::vector<std::vector<std::vector<float> > > matrices = GenMatrices("./data");
////  std::cout << matrices.size() << ' ' << matrices[0].size() << ' ' << matrices[0][0].size() << "\n";
//  std::ofstream outputStream("output.csv");
//  Dumper<float> dumper(6, outputStream);
//  for (int i = 0; i < matrices[0][0].size(); ++i) {
//    std::vector<float> new_values(6);
//    for (int j = 0; j < 6; ++j) {
//      new_values[j] = matrices[j][0][i];
//    }
////    dumper.update(new_values);
//  }
////  dumper.dump();
//
//  return 0;
//}
