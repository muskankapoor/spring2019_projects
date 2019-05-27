/*
  Title: TestRandomGraph.cpp 
  Muskan Kapoor
  May 3,  2019
  Description: This is Part 3. Simulating a random graph code 
*/



#include<iostream>
#include<cstdlib>
#include<ctime>
#include<stdlib.h>

using namespace std;

class UnionFind{
public:
  int data;
  UnionFind *next;
  int rank;

  UnionFind(){
    data=-1;
    next=0;
    rank=1;
  }
  
  UnionFind(int d){
    data=d;
    next=0;
    rank=1;
  }
};

 UnionFind* find(UnionFind *N){
   UnionFind *temp=N;
  while(temp->next!=NULL){
    temp=temp->next;
  }
  return temp;
}

int unionNode(UnionFind *x,  UnionFind *y){
   UnionFind *rx=find(x);
   UnionFind *ry=find(y);
  if(rx->data==ry->data)
    return rx->rank;
  if(rx->rank > ry->rank){
    ry->next=rx;
    rx->rank=rx->rank+ry->rank;
    return rx->rank;
  }
  else{
    rx->next=ry;
    ry->rank=ry->rank+rx->rank;
    return ry->rank;
  }
}

class Graph{
private:
  int **G;
  int V;
  int E;
   UnionFind **N;
public:
  
  Graph(int V){
    E=0;
    this->V=V;
    G=(int **)malloc(sizeof(int *)*V);
    for(int i=0;i<V;i++)
      G[i]=(int *)malloc(sizeof(int)*V);
    for(int i=0;i<V;i++)
      for(int j=0;j<V;j++)
	G[i][j]=0;
          
    N=( UnionFind **)malloc(sizeof( UnionFind *)*V);
    for(int i=0;i<V;i++)
      N[i]=new  UnionFind(i);
          
  }

  bool addEdge(int u, int v){
    int connectedVertex;
    if(G[u][v]==0 && u!=v){
      G[u][v]=1;
      G[v][u]=1;
      E++;
      connectedVertex=unionNode(N[u],N[v]);
    }
          
    if(connectedVertex==V)
      return true;
    else
      return false;
  }

  int totalEdge(){
    return E;
  }

  int smallestOutDegree(){
    int small=9999999;
    int count=0;
    for(int i=0;i<V;i++){
      count=0;
      for(int j=0;j<V;j++){
	if(G[i][j]==1)
	  count++;
      }
      if(count<small)
	small=count;
                  
    }
    return small;
  }

  int largestOutDegree(){
    int largest=-1;
    int count=0;
    for(int i=0;i<V;i++){
      count=0;
      for(int j=0;j<V;j++){
	if(G[i][j]==1)
	  count++;
      }
      if(count>largest)
	largest=count;
                  
    }return largest;
  }
 
  float averageOutDegree(){
    int count=0;
    for(int i=0;i<V;i++){
      for(int j=0;j<V;j++){
	if(G[i][j]==1)
	  count++;
      }  
    }
    return (float)count/V;
  }
  
      
};


int main(int argc,char **argv){
  srand(time(0));
  const int maximum_value=stoi(argv[1]);
  Graph G(maximum_value);
  bool flag=false;
  
  while(!flag){
    const int random_variable1=rand()%maximum_value ;
    const int random_variable2=rand()%maximum_value;
    flag=G.addEdge(random_variable1, random_variable2);
  }
  cout<<"Number of edges: "<<G.totalEdge()<<endl;
  cout<<"Smallest out degree: "<<G.smallestOutDegree()<<endl;
  cout<<"Largest out degree: "<<G.largestOutDegree()<<endl;
  cout<<"Average out degree: "<<G.averageOutDegree()<<endl;
  return 0;
  
}
