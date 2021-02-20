#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;


// Solution 1
// int solve(int W, vector<int> &wt, vector<int> &val, int &n, int index,
// vector<vector<int>> &cache) {
// if (W <= 0 || index >= n) {
// return 0;
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

// void solution1(int W, vector<int> wt, vector<int> val, int &n) {
// vector<vector<int>> cache(n, vector<int>(W + 1, -1));
// auto result = solve(W, wt, val, n, 0, cache);
// cout << result << "1" << endl;
// }

void solve2(vector<vector<int>> &dp, vector<int> weights, vector<int> values) {
  cout << "items" << dp.size() << " " << dp[0].size() << endl;
  for (int item = 0; item < dp.size(); item++) {
    for (int weight = 0; weight <= dp[0].size(); weight++) {
      // Cant put it in the bag, not enough space
      cout << "item " << item << "with weight" << weights[item]
           << " checking weights " << weight << endl;

      if (weights[item] > weight)
        continue;

      // If we can put it in the bag, we check if it is worth it to put it, put
      // it and get the max previous value subtracting this weight

      int leftWeight = weight - weights[item];
      cout << "left" << leftWeight << endl;
      if (leftWeight <= 0) {
        dp[item][weight + 1] = values[item];
        cout << "Set value to " << values[item] << endl;
      } else {
        if (item == 0) {
          dp[item][weight + 1] = dp[item][weight];
        } else {

          dp[item][weight + 1] =
              max(dp[item - 1][leftWeight + 1] + values[item],
                  dp[item - 1][weight + 1]);
        }
      }
    }
  }

  cout << "HERE" << endl;
  cout << dp[dp.size()][dp[0].size()] << endl;
}

void solution2(int &W, vector<int> weights, vector<int> values, int &n) {
  vector<vector<int>> dp(n, vector<int>(W + 1, 0));

  solve2(dp, weights, values);
}

int main(int argc, char *argv[]) {
  string file_name = argv[1];

  std::ifstream infile(file_name);

  int n, w;
  infile >> n >> w;

  vector<int> weights;
  vector<int> values;

  weights.reserve(n);
  values.reserve(n);
  int t1, t2;

  for (int i = 0; i < n; i++) {
    infile >> t1 >> t2;
    values.emplace_back(t1);
    weights.emplace_back(t2);
  }
  solution2(w, weights, values, n);

  infile.close();
  return 0;
}
