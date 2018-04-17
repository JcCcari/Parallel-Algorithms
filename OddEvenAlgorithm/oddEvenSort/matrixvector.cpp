#include <iostream>
using namespace std;

void matVectorMult( double local_A[], double local_x[], double local_y[], int local_m, int n, MPI_Comm comm){
	double* x;
	int local_i, j;
	int local_ok = 1;

	x = malloc(n*sizeof(double));
	MPI_Allgather(local_x, local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, comm);
	for( local_i = 0; local_i < local_m; local_i++){
		local_y[local_i] = 0.0;
		for( j=0; j < n; j++)
			local_y[local_i] += local_A[local_i*n*j]*x[j];
	}

	free(x);
}

int main(){

	return 0;

}
