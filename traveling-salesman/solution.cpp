#include <chrono>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;
using namespace std::chrono;

int read_data_from_file(string file_name, vector<int> &weights,
                        vector<int> &values) {
  ifstream datafile(file_name);
  int n, total_capacity;
  string line;

  // First line of the data file contains the capacity constraint of the
  // knapsack
  std::getline(datafile, line);
  auto space_iter = line.find(' ');
  n = stoi(line.substr(0, space_iter));
  total_capacity = stoi(line.substr(space_iter + 1));

  weights.reserve(n);
  values.reserve(n);

  // Read the values and weights from the file
  while (std::getline(datafile, line)) {
    auto space_iter = line.find(' ');
    values.emplace_back(stoi(line.substr(0, space_iter)));
    weights.emplace_back(stoi(line.substr(space_iter + 1)));
  }

  datafile.close();
  return total_capacity;
}

int main(int argc, char *argv[]) {
  string file_name = argv[1];
  vector<int> weights;
  vector<int> values;

  int total_capacity = read_data_from_file(file_name, weights, values);
  int n = weights.size();

  auto start = high_resolution_clock::now();

  // solve();

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\n \n";
  cout << "Duration: " << duration.count() << " ms" << endl;

  return 0;
}
