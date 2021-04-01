#include "./Graph.cpp"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int getAvailableColor(map<int, int> &currentlyColored, Graph &graph,
                      int &currentNode) {

  set<int> neighbours = graph.adjList[currentNode];

  set<int> neighboursColor;
  map<int, int>::const_iterator it;

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

void backtrack(Graph &graph, map<int, int> &currentlyColored,
               int currentNode) {
  // Get all possible colors for this node.
  int newColor = getAvailableColor(currentlyColored, graph, currentNode);

  // assign the color to the current vertex
  currentlyColored[currentNode] = newColor;

  // If colored all the nodes, then we are done!
  if (currentlyColored.size() == graph.numberOfNodes()) {
    return;
  }

  map<int, int>::const_iterator it;
  for (const auto &neighbour : graph.adjList[currentNode]) {
    it = currentlyColored.find(neighbour);
    // If already colored the neighbouring node, dont go there
    if (it != currentlyColored.end()) {
      continue;
    }
    backtrack(graph, currentlyColored, neighbour);
  }
}

map<int, int> color(Graph graph) {
  int startingNode = 1;

  map<int, int> currentlyColored;
  backtrack(graph, currentlyColored, startingNode);

  return currentlyColored;
}

map<int, set<int>> kPartite(Graph &graph) {

  int startingNode = 1;
  map<int, int> currentlyColored;

  backtrack(graph, currentlyColored, startingNode);

  map<int, set<int>> kPartite;
  for (auto &it : currentlyColored) {
    kPartite[it.second].insert(it.first);
  }

  return kPartite;
}
// Get minimin number of colors needed to color the graph
int minColor(Graph &graph) {
  return kPartite(graph).size();
}

int main(int argc, char *argv[]) {
  Graph graph(false);
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
          graph.addEdge(nodeA, nodeB);
          nodeA = INT_MIN;
          nodeB = INT_MIN;
        }
        c++;
      }
    }
    myfile.close();
  }

  // Minim number need to colors this graph is 2
  cout << minColor(graph) << " 1" << endl;

  // Split the graph into k partition
  map<int, set<int>> kPartition = kPartite(graph);

  map<int, int> nodesColored = color(graph);
  for (auto vertex : nodesColored) {
    cout << vertex.second << " ";
  }

  return 0;
}
