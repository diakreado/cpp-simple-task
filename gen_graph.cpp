#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

class Graph {
private:
  std::vector<std::vector<int> * > * table;
  static const int MAX_NODES = 15;

public:
  Graph();
  ~Graph();

  int  add_node();
  void add_connection(int node, int connect_to);

  std::string toString() const;

  int count_connected_components() const;

  static Graph* generate_random_graph();
};

Graph::Graph() {
  this->table = new std::vector<std::vector<int> * >();
}

void Graph::add_connection(int node, int connect_to) {
  if (node < 1 || node > this->table->size() ||
      connect_to < 1 || connect_to > this->table->size()) {
    throw std::invalid_argument("args shoud be more then 0 and less then number of nodes in the graph");
  }
  if (node == connect_to ||
      std::find(this->table->at(node - 1)->begin(),
                this->table->at(node - 1)->end(),
                connect_to)
      != this->table->at(node - 1)->end()) {
    throw std::invalid_argument("args should be not equal and 'connect_to' shouldn't contains in the graph");
  }
  this->table->at(node - 1)->push_back(connect_to);
}

int Graph::add_node() {
  this->table->push_back(new std::vector<int>());
  return this->table->size();
}

Graph::~Graph() {
  for (size_t i = 0; i < this->table->size(); i++) {
    delete this->table->at(i);
  }
  delete this->table;
}

std::string Graph::toString() const {
  std::stringstream ss;
  for (int i = 0; i < this->table->size(); i++) {
    ss << i+1 << ": ";
    for (auto j : *(this->table->at(i))) {
      ss << j << " ";
    }
    ss << std::endl;
  }
  return ss.str();
}

int Graph::count_connected_components() const {
  int connected_components = 0;  
  for (auto i : *(this->table)) {
    connected_components += i->size();
  }
  return connected_components;
}

Graph* Graph::generate_random_graph() {
  Graph * g = new Graph();

  srand((unsigned)time(NULL));
  int nodes = rand() % Graph::MAX_NODES + 2;
  
  for (int node = 1; node <= nodes; node++) {
    g->add_node();
  }
  for (int node = 1; node <= nodes; node++) {
    int connections = rand() % nodes + 1;
    for (int connection = 1; connection <= connections; connection++) {
      int connect_to = rand() % nodes + 1;
      try {
        g->add_connection(node, connect_to);
      } catch(...) { }
    }
  }
  return g;
}

int main() {
  // Graph * g = new Graph();
  Graph * g = Graph::generate_random_graph();

  // g->add_node();
  // g->add_node();
  // g->add_node();

  // g->add_connection(1,3);

  std::cout << g->toString();

  std::cout << "connected_components: " << g->count_connected_components() << std::endl;

  delete(g);
  return 0;
}