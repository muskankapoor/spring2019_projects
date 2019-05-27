/*
  Title: create_and_test.cc 
  Muskan Kapoor
  April 3, 2019
  Description: This is the main function to test the statisitcs of the quadradic, linear, and double probing
*/

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  
  hash_table.MakeEmpty();
  ifstream file;
  file.open(words_filename);
  if (file.fail()) {
    cout << "error" << endl;
  }

  ifstream other_file;
  other_file.open(query_filename);
  if (other_file.fail()) {
    cout << "error" << endl;
  }

  string db_line;


  // part 1 readin file and statistics
  while (getline(file, db_line)) {
  

    if(!db_line.empty()) {
      hash_table.Insert(db_line);
    }
  }
  file.close();

  

  cout << "Collisions: " <<  hash_table.counterReturn()<< endl;
  cout << "Number of items: " << hash_table.countElements() << endl;
  cout << "Size of hash table: " << hash_table.sizeofTable() << endl;
  double count = hash_table.countElements();
  double load_factor = count/hash_table.sizeofTable();
  cout << "Load factor: " << load_factor << endl;
  double average = hash_table.counterReturn()/count;
  cout << "Avg. number of collisions: " << average <<  endl;


  // part 2 readin file and checking number of probes
  
  while (getline(other_file, db_line)){
 
    if (hash_table.Contains(db_line)){
      cout << db_line << " Found "  << hash_table.otherCounterReturn() << " probes";
      
      cout << endl;
    }
    else{
      cout << db_line << " Not Found in " << hash_table.otherCounterReturn() << " probes";
      cout << endl;
    }
  }
  other_file.close();
}


//double hashing 
template <typename HashTableType>
void TestFunctionForHashTable1(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  

  hash_table.MakeEmpty();
  hash_table.resetCollisions();

  ifstream other_file;
  other_file.open(query_filename);
  if (other_file.fail()) {
    cout << "error" << endl;
  }
  
  ifstream all_words_file;
  all_words_file.open(words_filename.c_str());
  if (all_words_file.fail())
    {
      cout << "Error opening words file\n";
    }

  string db_line;
    
  string line;
  while(all_words_file.good()) {
    getline(all_words_file, line);
    hash_table.Insert(line);

  }

  cout << "Number of elements: " << hash_table.getNumElements() << endl;
  cout << "Size of hash table: " << hash_table.getSize() << endl;
  cout << "Load factor: " << (hash_table.getNumElements() / (double)hash_table.getSize()) << endl;

  cout << "Total collisions: " << hash_table.getNumCollisions() << endl;
  cout << "Avg. number of collisions: " << (hash_table.getNumCollisions()/(double)hash_table.getNumElements()) << endl;



  hash_table.resetCollisions();
  while (getline(other_file, db_line)){
 
    if (hash_table.Contains(db_line)){
      cout << line << db_line << " Found " << hash_table.getNumCollisions() + 1 << " probes "<<  endl;
      hash_table.resetCollisions();
    } else {
      cout << line << db_line << " Not Found " << hash_table.getNumCollisions() + 1 << " probes " << endl;
      hash_table.resetCollisions();
    }
  }


  all_words_file.close();
  other_file.close();


}


// Sample main for program create_and_test_hash
int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable1(double_probing_table, words_filename, query_filename);    
  } else {
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
