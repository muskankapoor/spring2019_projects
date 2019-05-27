/*
  Title: spell_check.cc 
  Muskan Kapoor
  April 3, 2019
  Description: This is the main function to do spell checking using double hashing
*/


#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;




template <typename HashTableType>
void  TestMisspellings(HashTableType &hash_table, const string &document_filename, const string &dictionary_filename) {

  cout << "TestFunctionForHashTables..." << endl;
  cout << "Document filename: " << document_filename << endl;
  cout << "Dictionary filename: " << dictionary_filename << endl;
  

  hash_table.MakeEmpty();
  hash_table.resetCollisions();

  ifstream document_file;
  document_file.open(document_filename.c_str());
  if (document_file.fail())
    {
      cerr << "Error opening document file\n";
    }

  ifstream dictionary_file;
  dictionary_file.open(dictionary_filename.c_str());
  if (dictionary_file.fail())
    {
      cout << "Error opening dictionary file\n";
    }

  string line;
  while(dictionary_file.good()) {
    getline(dictionary_file, line);
    hash_table.Insert(line);
  }

  bool skip = false;

 
  while(document_file >> line) {
    string letter = "";
    string word = "";
        for (int i = 0; i < line.length(); i++) {

      letter = tolower(line[i]);
      if(letter == "\'") { 
	skip = true; // skip some edge cases 
      }

      if (  (letter >= "a" && letter <= "z" )  ) {
	word += letter;
      }
    }
  

    // check cases 
    string newWord = word;
    if ( !skip && !hash_table.Contains(newWord)) {

      // 1) 
      for(int i = 0; i < word.length() + 1; i++) {

	for (char ch = 'a';ch <= 'z'; ch++) {
	  newWord.insert(i, 1, ch);
                
	  if(hash_table.Contains(newWord)) {
	    cout << word << " -> " << newWord  << " (case a)"<< endl;
	  }
	  newWord = word; 
                
	}
            
      }
      newWord = word;
      // 2) 
      for(int i = 0; i < word.length(); i++) {

	newWord.erase(i,1);
	if(hash_table.Contains(newWord)) {
	  cout << word << " -> " << newWord  << " (case b)"<< endl;
	}
	newWord = word; 

      }
      // 3) 
      for(int i = 0; i < word.length() - 1; i++) {

	swap(newWord[i], newWord[i+1]);
	if(hash_table.Contains(newWord)) {
	  cout << word << " -> " << newWord  << " (case c)"<< endl;
	}
	newWord = word; 

      }
    } 
    skip = false;

  } 

 
  document_file.close();
  dictionary_file.close();


}

// Sample main for program spell check 
int main(int argc, char **argv) {

  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    
  }

  
  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);
  
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;


  
  HashTableDouble<string> double_probing_table;
  TestMisspellings(double_probing_table, document_filename, dictionary_filename);
  
}
