#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]){
	
	int procs, rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	

	MPI_Finalize();
	return 0;
}

