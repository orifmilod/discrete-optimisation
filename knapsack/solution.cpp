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

void dynamic_programming_recursive(int W, vector<int> &wt, vector<int> &val,
                                   int n) {
  vector<vector<int>> cache(n, vector<int>(W + 1, -1));

  auto result = solve1(W, wt, val, n, 0, cache);
  cout << "Result: " << result << endl;
}

// Solution 2
void solve2(vector<vector<int>> &dp, vector<int> &weights,
            vector<int> &values) {
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
  map<int, bool> choosen;
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

void dynamic_programming_tabular(int &W, vector<int> &weights,
                                 vector<int> &values, int n) {
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  solve2(dp, weights, values);
}

struct Node {
  int value;
  int weight;
  float upper_bound;

  Node(int _value, int _weight, float _upper_bound)
      : value(_value), weight(_weight), upper_bound(_upper_bound) {}
};

struct Item {
  int weight;
  int value;
  float value_weight_ratio;

  Item(int _weight, int _value, float _value_weight_ratio)
      : weight(_weight), value(_value),
        value_weight_ratio(_value_weight_ratio) {}

  Item() {}
};

float get_upper_bound(Node &node, int knapsack_capacity, int index,
                      vector<Item> &items) {
  // We can't fit it in the knapsack
  if (node.weight > knapsack_capacity)
    return INT_MIN;

  // int total_weight = node.weight;
  // float result = node.value;
  //
  // while (j < n && total_weight + items[j].weight <= W) {
  // total_weight = total_weight + items[j].weight;
  // result += items[j].value;
  // j++;
  // }
  //
  // if (j < n) {
  // result += items[j].value_weight_ratio;
  // }
  //
  // return result;
}

// Branch and bound -> Best first search using priority queue
void branch_bound_bfs(int W, vector<int> &weights, vector<int> &values, int n) {
  vector<Item> items;

  for (int i = 0; i < n; i++) {
    items.push_back(Item(weights[i], values[i], values[i] / (float)weights[i]));
  }

  sort(begin(items), end(items), [](const Item &A, const Item &B) {
    return A.value_weight_ratio < B.value_weight_ratio;
  });

  auto cmp = [](const Node &a, const Node &b) {
    return a.upper_bound < b.upper_bound;
  };
  priority_queue<Node, vector<Node>, decltype(cmp)> queue(cmp);

  Node dummy{-1, 0, 0, get_upper_bound(v, W, n, items)};

  // queue.push(dummy);

  int max_value = INT_MIN;
  while (queue.size() > 0) {
    Node item = queue.top();
    queue.pop();

    // Found a node whose upper bound is larger that the best solution found so
    // far
    // if (v.upper_bound > max_value) {
    // queue.emplace(Node{.upper_bound = })
    // }
  }

  cout << "Best First Search result: " << max_value;
}

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

  // Uncomment start and end variable lines in order to calculate performance
  auto start = high_resolution_clock::now();

  // dynamic_programming_recursive(w, weights, values, n);
  // dynamic_programming_tabular(w, weights, values, n);
  // branch_bound_bfs(total_capacity, weights, values, n);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "\n \n";
  cout << "Duration: " << duration.count() << " ms" << endl;

  return 0;
}
