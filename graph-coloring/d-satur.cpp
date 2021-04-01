#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int getAvailableColor(unordered_map<int, int> &currentlyColored,
                      unordered_map<int, set<int>> &graph, int currentNode) {
  set<int> neighbours = graph[currentNode];

  set<int> neighboursColor;
  unordered_map<int, int>::const_iterator it;

  for (const int &neighbour : neighbours) {
    it = currentlyColored.find(neighbour);
    if (it != currentlyColored.end()) {
      neighboursColor.insert(it->second);
    }
  }

  int colorCode = 0;
  set<int>::const_iterator setIterator;

  // Increase the color code until we find a color which the neighbours does not
  // use
  while (true) {
    setIterator = neighboursColor.find(colorCode);
    if (setIterator == neighboursColor.end()) {
      break;
    }
    colorCode++;
  }

  return colorCode;
}

int main(int argc, char *argv[]) {
  // Read all the nodes and their edges and insert in the adjacency list
  unordered_map<int, set<int>> adjList;

  string file_name = argv[1];
  int n, e;

  n = strtol(argv[1], NULL, 10);
  e = strtol(argv[2], NULL, 10);

  int nodeA, nodeB;
  for (int i = 3; i < argc - 1; i += 2) {
    nodeA = strtol(argv[i], NULL, 10);
    nodeB = strtol(argv[i + 1], NULL, 10);
    adjList[nodeA].insert(nodeB);
    adjList[nodeB].insert(nodeA);
  }

  // Make a vector of pairs which will be sorted by saturation level

  vector<pair<int, set<int>>> items;
  items.reserve(n);

  for (const auto &item : adjList) {
    items.emplace_back(item);
  }

  auto cmp = [](const pair<int, set<int>> &item1,
                const pair<int, set<int>> &item2) -> bool {
    return item1.second.size() > item2.second.size();
  };

  sort(items.begin(), items.end(), cmp);

  set<int> allColors;
  unordered_map<int, int> colored;
  // iterater from the most saturated nodes to the least and color them
  for (const auto &item : items) {
    cout << item.first << ": " << item.second.size() << endl;
    int color = getAvailableColor(colored, adjList, item.first);
    colored[item.first] = color;
    allColors.insert(color);
  }

  cout << allColors.size() << " 1" << endl;

  for (int i = 0; i < n; i++) {
    cout << colored[i] << " ";
  }

  return 0;
}
