/*
  Title: Graph.h
  Muskan Kapoor
  May 3,  2019
  Description: This is Part 2. Simulating a random graph code. The graph class 
*/


#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <iostream>
#include <list>       
#include <utility>       
#include <float.h>      
#include <climits>      
#include <queue>

template<typename Object>
class Graph;

template <typename Object>
class Vertex{
 public:
  friend class Graph<Object>;
  Vertex() = default;
  Vertex(Object key){
    id_ = key;
    distance_ = DBL_MAX;
    known_ = false;
    path_prev_ = nullptr;
    starting_vertex_ = false;
  }

  int distance() const {
    return distance_;
  }
 private:
  Object id_;
  double distance_;
  bool known_;
  Vertex<Object> * path_prev_;
  bool starting_vertex_;
  std::list<std::pair< Vertex<Object>*, double>  > adjacent_nodes_;
};


template <typename Object>
class Compare{
 public:
  bool operator()(const Vertex<Object> *lhs, const Vertex<Object> * rhs) const{
   
    return lhs->distance() > rhs->distance();
  }
};

template <typename Object>
class Graph{
 public:
  Graph() = default;
  ~Graph() = default;

  Graph(const Graph & rhs) = delete;
  Graph(Graph && rhs) = delete;
  Graph & operator=(const Graph & rhs) = delete;
  Graph & operator=(Graph && rhs) = delete;
 
  bool addingvertex(Object a);

  void addingconnection(Object a, Object b, double weight);
  
  double Edge(const Object &a, const Object &b) const;

  bool connected(const Object &v1, const Object &v2);

  void Dijkstra(Object start);
 
  void shortest_path(const Object & graph_node) const;

  bool Contains(const Object & vertex_node) const;
  
  size_t Get_size() const;

  void Print_stats() const;
 private:
 
  void Print_shortest_path_internal(const Vertex<Object> * graph_node) const;

  void rvertex(Vertex<Object> v);
  std::unordered_map<Object, Vertex<Object> > vertex_map_;  
  size_t edge_count_;
};

#include "Graph.cpp"
#endif
