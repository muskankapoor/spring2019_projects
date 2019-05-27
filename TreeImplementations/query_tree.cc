// Muskan Kapoor
// FIle:query_tree.cc 
// Assignment 2, March 12, 2019
// implementation of the class sequence_map.h 
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

namespace {

  // @db_filename: an input filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be empty.
  template <typename TreeType>
  void QueryTree(const string &db_filename, TreeType &a_tree) {

    // Code for running Part2(a)

    //error check 
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


    // printing out the sequence 
    string sequence;
    while (cin >> sequence) {
      SequenceMap query{sequence, ""};
      if (a_tree.contains(query)) {
	a_tree.printValue(query);
      }
      else{
	cout << "Not Found" << endl;
      }
    }
  }

} // namespace


int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  AvlTree<SequenceMap> a_tree;
  QueryTree(db_filename, a_tree);
  return 0;
}
