#include "./Graph.cpp"
#include <iostream>
#include <set>
#include <string>
#include <map>
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

  string file_name = argv[1];
  int N, E;

  N = strtol(argv[1], NULL, 10);
  E = strtol(argv[2], NULL, 10);

  int nodeA, nodeB;
  for (int i = 3; i < argc - 1; i+=2) {
    nodeA = strtol(argv[i], NULL, 10);
    nodeB = strtol(argv[i + 1], NULL, 10);
    graph.addEdge(nodeA, nodeB);
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
