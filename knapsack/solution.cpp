#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::chrono;

// Solution 1
// unsigned int solve(unsigned int W, vector<unsigned int> &wt, vector<unsigned
// int> &val, unsigned int &n, unsigned int index, vector<vector<unsigned int>>
// &cache) { if (W <= 0 || index >= n) { return 0;
// }
//
// if (cache[index][W] != -1) {
// return cache[index][W];
// } else if (W - wt[index] < 0) {
// cache[index][W] = solve(W, wt, val, n, index + 1, cache);
// } else {
// cache[index][W] =
// max(val[index] + solve(W - wt[index], wt, val, n, index + 1, cache),
// solve(W, wt, val, n, index + 1, cache));
// }
//
// return cache[index][W];
// }

// void solution1(unsigned int W, vector<unsigned int> wt, vector<unsigned int>
// val, unsigned int &n) { vector<vector<unsigned int>> cache(n, vector<unsigned
// int>(W + 1, -1)); auto result = solve(W, wt, val, n, 0, cache);
// cout << result << "1" << endl;
// }

void solve2(vector<vector<unsigned int>> &dp, vector<unsigned int> weights,
            vector<unsigned int> values) {
  for (unsigned int item = 1; item < dp.size(); item++) {
    for (unsigned int weight = 1; weight < dp[0].size(); weight++) {
      // Cant put it in the bag, not enough space
      if (weights[item - 1] > weight) {
        dp[item][weight] = item == 0 ? 0 : dp[item - 1][weight];
        continue;
      }

      // If we can put it in the bag, we check if it is worth it to put it, put
      // it and get the max previous value subtracting this weight
      unsigned int leftWeight = weight - weights[item - 1];
      if (leftWeight == 0) {
        if (item == 0) {
          dp[item][weight] = values[item - 1];
        } else {
          dp[item][weight] = max(values[item - 1], dp[item - 1][weight]);
        }

      } else {
        if (item == 0) {
          dp[item][weight] = dp[item][weight - 1];
        } else {
          dp[item][weight] = max(dp[item - 1][leftWeight] + values[item - 1],
                                 dp[item - 1][weight]);
        }
      }
    }
  }
  // for (auto &a : dp) {
  // for (auto &b : a) {
  // cout << b << " ";
  // }
  // cout << endl;
  // }
  cout << dp[dp.size() - 1][dp[0].size() - 1] << " 1" << endl;

  // Track down the dp table in order to get the choosen items
  unordered_map<int, bool> choosen;
  int weight = dp[0].size() - 1;
  int item = dp.size() - 1;

  while (weight > 0 && item > 0) {
    // We have taken this item
    if (dp[item][weight] != dp[item - 1][weight]) {
      choosen[item] = true;
      weight -= weights[item - 1];
    }
    item--;
  }

  for (int i = 1; i < dp.size(); i++) {
    cout << (choosen[i] ? 1 : 0) << " ";
  }
}

void solution2(unsigned int &W, vector<unsigned int> weights,
               vector<unsigned int> values, unsigned int &n) {
  // auto start = high_resolution_clock::now();

  vector<vector<unsigned int>> dp(n + 1, vector<unsigned int>(W + 1, 0));
  solve2(dp, weights, values);

  // auto stop = high_resolution_clock::now();
  // auto duration = duration_cast<microseconds>(stop - start);
  // cout << "Duration: " << duration.count() << " ms" << endl;
}

int main(int argc, char *argv[]) {
  string file_name = argv[1];
  unsigned int n, w;

  n = strtol(argv[1], NULL, 10);
  w = strtol(argv[2], NULL, 10);

  vector<unsigned int> weights;
  vector<unsigned int> values;

  weights.reserve(n);
  values.reserve(n);
  for (int i = 3; i < argc - 1; i++) {
    values.emplace_back(strtol(argv[i], NULL, 10));
    i++;
    weights.emplace_back(strtol(argv[i], NULL, 10));
  }

  solution2(w, weights, values, n);
  return 0;
}
