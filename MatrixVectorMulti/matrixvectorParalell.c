/* Product of a vector by a matrix */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int rank, numprocs, M, N, count, remainder, myRowsSize;
	int* matrix = NULL;
	int* vector;
	int* result = NULL;
	int* sendcounts = NULL;
	int* senddispls = NULL;
	int* recvcounts = NULL;
	int* recvdispls = NULL;

	MPI_Init (&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (0 == rank)
	{
		printf("Product of a vector by a matrix\n");
		printf("Enter the number of matrix rows:" );
		scanf("%i",&M);
		if (M < 1)	return EXIT_FAILURE;
		printf("Enter the number of matrix columns:");
		scanf("%i",&N);
		if (N < 1)	return EXIT_FAILURE;

		printf("\n");
		matrix = (int*) malloc( M*N*sizeof(int) );//new int[M * N];
		// generate matrix
		printf("matrix:");
		for (int i = 0; i < M; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				matrix[N * i + j] = rand() % 100;
				//cout << matrix[N * i + j] << '\t';
			}
			//cout << endl;
		}
		//cout << endl;

		vector = (int*) malloc( N*sizeof(int) ); //vector = new int[N];
		// generate vector
		printf("vector");
		for (int i = 0; i < N; ++i)
		{
			vector[i] = rand() & 100;
			//cout << vector[i] << ' ';
		}
		printf("\n");

		sendcounts = (int*) malloc( numprocs *sizeof(int) ); //new int[numprocs];
		senddispls = (int*) malloc( numprocs*sizeof(int) ); //new int[numprocs];
		recvcounts = (int*) malloc( numprocs*sizeof(int) ); //new int[numprocs];
		recvdispls = (int*) malloc( numprocs*sizeof(int) ); //new int[numprocs];
		
		count = M / numprocs;
		remainder = M - count * numprocs;
		int prefixSum = 0;
		for (int i = 0; i < numprocs; ++i)
		{
			recvcounts[i] = (i < remainder) ? count + 1 : count;
			sendcounts[i] = recvcounts[i] * N;
			recvdispls[i] = prefixSum;
			senddispls[i] = prefixSum * N;
			prefixSum += recvcounts[i];
		}
	}

	MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (0 != rank)
		vector = (int*) malloc( N*sizeof(int) ); // new int[N];
	MPI_Bcast(vector, N, MPI_INT, 0, MPI_COMM_WORLD);

	if (0 != rank){
		count = M / numprocs;
		remainder = M - count * numprocs;
	}
	myRowsSize = rank < remainder ? count + 1 : count;
	int* matrixPart = (int*) malloc(myRowsSize*N*sizeof(int) ); //new int[myRowsSize * N];
	MPI_Scatterv(matrix, sendcounts, senddispls, MPI_INT, matrixPart, myRowsSize * N, MPI_INT, 0, MPI_COMM_WORLD);

	if (0 == rank){
		free(sendcounts); //delete[] sendcounts;
		free(senddispls); //delete[] senddispls;
		free(matrix); //delete[] matrix;
	}

	int* resultPart = (int*) malloc( myRowsSize*sizeof(int) ); // new int[myRowsSize];
#pragma omp parallel for
	for (int i = 0; i < myRowsSize; ++i)
	{
		resultPart[i] = 0;
		for (int j = 0; j < N; ++j)
		{
			resultPart[i] += matrixPart[i * N + j] * vector[j];
		}
	}
	free(matrixPart); //delete[] matrixPart;
	free(vector);//delete[] vector;

	if (0 == rank)
		result = (int*) malloc( myRowsSize*sizeof(int) ); //result = new int[M];

	MPI_Gatherv(resultPart, myRowsSize, MPI_INT, result, recvcounts, recvdispls, MPI_INT, 0, MPI_COMM_WORLD); 
	free(resultPart); //delete[] resultPart;
	if (0 == rank){
		free(recvcounts); //delete[] recvcounts;
		free(recvdispls); //delete[] recvdispls;
	}

	MPI_Finalize();

	if (0 == rank) {
		printf("result: \n");
		for (int i = 0; i < M; ++i)
			printf("%i ",result[i]);
			
		printf("\n");
		free(result); //delete[] result;
//#if _DEBUG  system("pause"); #endif

	}
	return 0;
}
