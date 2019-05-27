/*
  Title: FindPaths.cpp 
  Muskan Kapoor
  May 3,  2019
  Description: This is Part 2. implementing Dijkstra. 
*/




#include <iostream>
#include "Graph.h"
#include <fstream>
#include <sstream>
#include <cstdlib>


template <typename Object>
void createGraph(std::string const & graph_file, Graph<Object> & graph){
  std::ifstream input;
  input.open(graph_file);
  if(input.fail()){
    std::cout << "Error: " << graph_file << std::endl;
    exit(1);
  }
  std::string line;
  Object this_vertex;
  Object a_new_vertex;
  double a_new_weight;
  std::getline(input, line);
  while(std::getline(input, line)){
    if(!line.empty()){
      std::stringstream ss(line);
      ss >> this_vertex;
      graph.addingvertex(this_vertex);
      while(ss >> a_new_vertex && ss >> a_new_weight){
	graph.addingconnection(this_vertex, a_new_vertex, a_new_weight);
      }
    }
  }
  input.close();
}


int main(int argc, char **argv){
  if(argc != 3){
    std::cout << "Usage: " << argv[0] << " <graphFile> <Vertex> " << std::endl;
    return 0;
  }
  const std::string graph_file(argv[1]);
  const int vertex = atoi(argv[2]);
  Graph<int> test;
  createGraph<int>(graph_file, test);  
  test.Dijkstra(vertex);
  int count = 1;
  while(test.Contains(count)){
    test.shortest_path(count);
    ++count;
  }
  return 0;
}
