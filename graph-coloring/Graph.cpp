#include <iostream>
#include <set>
#include <map>

class Graph {
  bool isDirectredGraph;

public:
  std::map<int, std::set<int>> adjList;
  Graph(bool isDirectredGraph);

  void addEdge(int nodeA, int nodeB);
  void removeEdge(int nodeA, int nodeB);
  void printAllEdges();
  int numberOfNodes();
};

int Graph::numberOfNodes() { return adjList.size(); }

void Graph::addEdge(int nodeA, int nodeB) {
  adjList[nodeA].insert(nodeB);
  if (!isDirectredGraph) {
    adjList[nodeB].insert(nodeA);
  }
}

void Graph::printAllEdges() {
  for (auto &it : adjList) {
    std::cout << it.first << ": ";

    for (auto &node : adjList[it.first]) {
      std::cout << node << ", ";
    }
    std::cout << "\n";
  }
}

void Graph::removeEdge(int nodeA, int nodeB) {
  adjList[nodeA].erase(nodeB);
  if (!isDirectredGraph) {
    adjList[nodeB].erase(nodeA);
  }
}

Graph::Graph(bool _isDirectredGraph) { isDirectredGraph = _isDirectredGraph; }
