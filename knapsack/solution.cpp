#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using namespace std::chrono;

// Solution 1
int solve1(int W, vector<int> &wt, vector<int> &val, int &n, int index,
           vector<vector<int>> &cache) {
  if (W == 0 || index == n) {
    return 0;
  }

  if (cache[index][W] != -1) {
    return cache[index][W];
  } else if (W - wt[index] < 0) {
    cache[index][W] = solve1(W, wt, val, n, index + 1, cache);
  } else {
    cache[index][W] =
        max(val[index] + solve1(W - wt[index], wt, val, n, index + 1, cache),
            solve1(W, wt, val, n, index + 1, cache));
  }

  return cache[index][W];
}

void dynamic_programming_recurse(int W, vector<int> wt, vector<int> val,
                                 int &n) {
  vector<vector<int>> cache(n, vector<int>(W + 1, -1));

  auto result = solve1(W, wt, val, n, 0, cache);
  cout << "Result: " << result << endl;
}

// Solution 2
void solve2(vector<vector<int>> &dp, vector<int> weights, vector<int> values) {
  for (int item = 1; item < dp.size(); item++) {
    for (int weight = 1; weight < dp[0].size(); weight++) {
      // Cant put it in the bag, not enough space
      if (weights[item - 1] > weight) {
        dp[item][weight] = item == 0 ? 0 : dp[item - 1][weight];
        continue;
      }

      // If we can put it in the bag, we check if it is worth it to put it, put
      // it and get the max previous value subtracting this weight
      int leftWeight = weight - weights[item - 1];
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

  cout << "Result: " << dp[dp.size() - 1][dp[0].size() - 1] << endl;

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

  cout << "Choosen items: ";
  for (auto &item : choosen) {
    cout << item.first << " ";
  }
}

void dynamic_programming_tabular(int &W, vector<int> weights,
                                 vector<int> values, int &n) {
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  solve2(dp, weights, values);
}

void solution3(int &W, priority_queue<int> queue, vector<int> weights,
               vector<int> values, double lower_bound, double upper_bound) {
  // Start with the "root node"
  queue.push(0);
}

// Branch and bound -> Best first search using priority queue
void branch_bound_bfs(int &W, vector<int> weights, vector<int> values, int &n) {
  priority_queue<int> queue;
  vector<double> weight_to_value_ratio;

  // Make a weight value pair in order to sort them and use the best first
  // approach or Linear relaxation.
  // We are going to take an optimistic evaluation and use that as our upper
  // bound.
  for (int i = 0; i < weights.size(); i++) {
    weight_to_value_ratio.push_back(values[i] / (double)weights[i]);
  }

  sort(begin(weight_to_value_ratio), end(weight_to_value_ratio),
       greater<double>());

  for (auto &a : weight_to_value_ratio) {
    cout << a << endl;
  }

  int index = 0;
  double upper_bound;

  // Getting our optimistic evaluation
  while (W > 0 && index < weight_to_value_ratio.size()) {
    if (weight_to_value_ratio[index] <= W) {
      W -= weight_to_value_ratio[index];
      upper_bound += weight_to_value_ratio[index];
    }
    index++;
  }

  solution3(W, queue, weights, values, INT_MIN, upper_bound);
}

int main(int argc, char *argv[]) {
  string file_name = argv[1];
  int n, w;

  n = strtol(argv[1], NULL, 10);
  w = strtol(argv[2], NULL, 10);

  vector<int> weights;
  vector<int> values;

  weights.reserve(n);
  values.reserve(n);
  for (int i = 3; i < argc - 1; i++) {
    values.emplace_back(strtol(argv[i], NULL, 10));
    i++;
    weights.emplace_back(strtol(argv[i], NULL, 10));
  }
  // Uncomment start and end variable lines in order to calculate performance
  auto start = high_resolution_clock::now();

  // dynamic_programming_recurse(w, weights, values, n);
  // dynamic_programming_tabular(w, weights, values, n);
  branch_bound_bfs(w, weights, values, n);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\n \n";
  cout << "Duration: " << duration.count() << " ms" << endl;

  return 0;
}
