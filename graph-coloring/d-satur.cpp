#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
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
  int n, e, c = 0;
  int nodeA = INT_MIN, nodeB = INT_MIN;
  string line;
  ifstream myfile("data.txt");
  string temp;

  if (myfile.is_open()) {
    while (getline(myfile, line, '\n')) {
      // construct a stream from the string
      std::stringstream ss(line);
      std::string s;
      while (getline(ss, temp, ' ')) {
      if (c == 0) {
        n = stoi(temp);
      } else if (c == 1) {
        e = stoi(temp);
      } else if (c % 2 == 1) {
        nodeB = stoi(temp);
      } else {
        nodeA = stoi(temp);
      }

      if (nodeA != INT_MIN && nodeB != INT_MIN) {
        adjList[nodeA].insert(nodeB);
        adjList[nodeB].insert(nodeA);
        // cout << nodeA << " " << nodeB << '\n';
        nodeA = INT_MIN;
        nodeB = INT_MIN;
      }
      c++;
      }
    }
    myfile.close();
  }

  // Make a vector of pairs which will be sorted by saturation level
  vector<pair<int, int>> items;
  items.reserve(n);

  for (const auto &item : adjList) {
    items.emplace_back(make_pair(item.first, item.second.size()));
  }

  auto cmp = [](const pair<int, int> &item1,
                const pair<int, int> &item2) -> bool {
    return item1.second > item2.second;
  };

  sort(items.begin(), items.end(), cmp);

  set<int> allColors;
  unordered_map<int, int> colored;
  // iterater from the most saturated nodes to the least and color them
  for (const auto &item : items) {
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
