/* Muskan Kapoor
Assignment 5
optimal_multiplications.cpp
This is the function to perform optimal multipilications and perform extra credit*/


#include<iostream>
#include <fstream>
using namespace std;

void printFUNCTION(int , int , int ,int *, char &) ;
void matrixMultiplication(int *, int );


void matrixMultiplication(int arr[], int n){
  int matrix[n][n];
  int matrix2[n][n];
  for (int i=1; i<n; i++)
    matrix[i][i] = 0;
  

  for (int L=2; L<n; L++)
    {
      for (int i=1; i<n-L+1; i++)
	{
	  int j = i+L-1;
	  matrix[i][j] = INT_MAX;
	  for (int k=i; k<=j-1; k++)
	    {
	      int q = matrix[i][k] + matrix[k+1][j] + arr[i-1]*arr[k]*arr[j];
	      if (q < matrix[i][j])
		{
		  matrix[i][j] = q;
		  matrix2[i][j] = k;
		}
	    }
	}
    }
  
  cout<<"Optimal multiplication: "<<matrix[1][n-1]<<"\n";
  char name = 'A';
  cout << "Optimal order is: ";
  printFUNCTION(1, n-1, n, (int *)matrix2, name);
}
  

void printFUNCTION(int i, int j, int n,int *matrix2, char &name){
  
  if (i == j)
    {
      cout << name++;
      return;
    }
  
  cout << "{";

  printFUNCTION(i, *((matrix2+i*n)+j), n,matrix2, name);
  
  printFUNCTION(*((matrix2+i*n)+j) + 1, j,n, matrix2, name);
  cout << ")";
}



int main()
{ ifstream in;
  in.open("dimensions_file.txt");
  if(!in){
    cout<<"file not opened\n";
    return 0;
  }
  int n=0;
  int arr[100];
  while(!in.eof()){
    in>>arr[n++];
  }
  
  matrixMultiplication(arr, n);
  return 0;
}

