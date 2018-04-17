#include <iostream>
#include "matrix.cpp"
#include "mtime.hpp"
#define TEST 10
using namespace std;

int main(int argc, char const *argv[])
{
	int tamTest[TEST] = {2,4,8,16,32,64,128,256,512,1024};

//	for (int i = 0; i < TEST ; ++i){

		int SIZE = 100; // tamTest[i];

		int** a = new int*[SIZE];
		int** b = new int*[SIZE];
	    int** res = new int*[SIZE];

		for (int i = 0; i < SIZE; i++){
			a[i] = new int[SIZE];
			b[i] = new int[SIZE];
	        res[i] = new int[SIZE];
		}
	    
	    for (int i = 0; i < SIZE ; i++){
	        for (int j = 0; j < SIZE ; j++){
	            a[i][j] = 1;
	            b[i][j] = 1;
	        }
	    }

	    auto time = mtime::mTime([&] { block_matrix_mult( a, b, res); });

	    cout << time/1000.0 << endl;
//	}

	return 0;
}