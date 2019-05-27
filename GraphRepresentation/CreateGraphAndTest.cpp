/*
  Title: CreateGraphAndTest.cpp 
  Muskan Kapoor
  May 3,  2019
  Description: This is Part 1. creating a list and checking connectivity.  
*/




#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;


void createList(string const & graph_file, string const & graph_file1){
  int sum = 0;
  double x;
  ifstream inFile, in;
  inFile.open(graph_file);
  in.open(graph_file1);
  int n;
  if (!inFile) {
    cout << "Unable to open file";
    exit(1);
  }
  inFile >> n;
  double AdjacencyList[n + 1][n + 1];
  for(int i = 0; i < n + 1; i++){
    for(int j = 0; j < n + 1; j++)
      AdjacencyList[i][j] = -1;
  }
  string s;
  double p;
  while(getline(inFile, s)){
    stringstream ss(s);
    int c = 0;
    int u;
    ss >> u;
    int v;
    double wt;
    while(ss >> p){
      if(c == 0)
	v = int(p);
      if(c == 1)
	wt = p;
      if(c == 1){
	AdjacencyList[u][v] = wt;
      }
      c++;
      c %= 2;
    }
  }
  if(!in){
    cout << "Unable to open file1";
    exit(2);
  }
  int a,b;
  while(in >> a >> b){
    double wt = AdjacencyList[a][b];
    cout << a << " " << b << ": ";
    if(wt == -1){
      cout << "Not connected\n";
    }
    else{
      cout << "Connected, weight of edge is " << wt << endl;
    }
  }
  inFile.close();
  in.close();
}


int main(int argc, char **argv){
  if(argc != 3){
    std::cout << "Usage: " << argv[0] << " <graphFile> <graphfile1> " << std::endl;
    return 0;
  }
  const std::string graph_file(argv[1]);
  const std::string graph_file1(argv[2]);
  createList(graph_file, graph_file1);

  return 0;
}
