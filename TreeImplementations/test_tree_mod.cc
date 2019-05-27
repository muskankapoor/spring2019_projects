// Muskan Kapoor
// Assignment 2: March 12, 2019
// Main file for Part2(c) of Homework 2.


#include "avl_tree_modified.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

namespace {

  
  template <typename TreeType>
  int find(const string file, TreeType &a_tree, int *queries){
    int count = 0;
    fstream readin(file);
    string sequence;
    while(readin >> sequence){
      if(a_tree.containsString(sequence)) {
	count++;
      }
      *queries += a_tree.findCalls(sequence);
    }
 
    readin.close();
    return count;
  }

  
  template <typename TreeType>
  int removing(const string file, TreeType &a_tree){
    int i= 0, remove = 0;
    string seq;
    fstream readin(file);

    while(readin >> seq){
      if(i % 2 == 0){
	SequenceMap temp;
	a_tree.containsString(seq, &temp);
	remove += a_tree.removeCalls(temp);
      }
      i++;
    }

    readin.close();
    return remove;
  }

  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {

    // Code for running Part2(a)
    ifstream file;
    file.open(db_filename);
    if (file.fail()) {
      cout << "error" << endl;
    }

    string db_line;

    while (getline(file, db_line)) {
      if(!db_line.empty()) {
	stringstream read(db_line);
	string an_enz_acro; 
	getline(read, an_enz_acro, '/');

	string a_rec_seq;
	while (getline(read, a_rec_seq, '/')) {
	  SequenceMap new_sequence_map { a_rec_seq, an_enz_acro};
	  a_tree.insert(new_sequence_map);
	}

      }
    }
    file.close();
    
    // 2
    int node_count = a_tree.nodeCount();
    cout << "2: " << node_count << endl;

    // 3
    float average_depth = a_tree.internalPath()/a_tree.nodeCount();
    cout << "3a: " << average_depth << endl;

    cout << "3b: " << (average_depth/log2(node_count)) << endl;
    
    
    // 4 
    int calls = 0;
    int success_queries = find(seq_filename, a_tree, &calls);
    cout << "4a: " << success_queries << endl;

    float average_find_calls = (float)calls/(float)success_queries;
    cout << "4b: " << average_find_calls << endl;
      
    // 5 
    int remove_calls = removing(seq_filename, a_tree);
    cout <<"5a: " << a_tree.getRemoves() << endl;
      
      
    float average_removes = (float)remove_calls/210;
    cout << "5b: " << average_removes << endl;

      
    // 6
    node_count = a_tree.nodeCount();
    cout << "6a: " << node_count << endl;

      
    average_depth = a_tree.internalPath()/a_tree.nodeCount();
    cout << "6b: " << average_depth << endl;

    cout << "6c: " << (average_depth/log2(node_count)) << endl;
  }



  
} // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }


  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);

  cout << "Input files are " << db_filename << " and " << seq_filename << endl;
  cout << "Type of tree is " << "AVL" << endl;

  AvlTree<SequenceMap> a_tree;
  TestTree(db_filename, seq_filename, a_tree);

  
  return 0;
}

