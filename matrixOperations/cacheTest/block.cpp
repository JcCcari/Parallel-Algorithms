#include "../mtime.hpp"
#include <iostream>
#include <random>

#define TEST 7
using namespace std;

void block_matrix_mult(int** a, int** b, int** c);
void printMatrix(int** A);
int getRandomNumber(int min, int max);

int SIZE ;

//Testing time executing each tamTest[i] matrix
int main(int argc, char const *argv[]){
    int tamTest[TEST] = {8,16,32,64,128,256,512};

    SIZE = tamTest[6];

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
            a[i][j] = getRandomNumber(0,100);
            b[i][j] = getRandomNumber(0,100);
        }
    }

    auto time = mtime::mTime([&] { block_matrix_mult( a, b, res); });

        //printMatrix(c);
    cout << SIZE <<"  : " <<time/1000.0 << endl; // printing milliseconds
	return 0;
}

void block_matrix_mult(int** a, int** b, int** c){
    
    int block_size = 64/sizeof(int); // depende del cache line
    int temp;
    for(int jj=0;jj< SIZE;jj+= block_size){
        for(int kk=0;kk< SIZE;kk+= block_size){
                for(int i=0;i< SIZE;i++){
                        for(int j = jj; j<((jj+block_size)>SIZE?SIZE:(jj+block_size)); j++){
                                temp = 0;
                                for(int k = kk; k<((kk+block_size)>SIZE?SIZE:(kk+block_size)); k++){
                                        temp += a[i][k]*b[k][j];
                                }
                                c[i][j] += temp;
                        }
                }
        }
    }
}

void printMatrix(int** a){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE ; j++){
            cout << a[i][j] << " " ;
        }
        cout << endl;
    }
}

int getRandomNumber(int min, int max) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist( min, max); // distribution in range [min, max]

    return static_cast<int>( dist(rng) );
};