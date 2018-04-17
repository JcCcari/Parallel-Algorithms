#include <stdio.h>
adfasdf#include <math.h>
#include <time.h>
#include <mpi.h>

const int MAX=16;

int main(int argc, char **argv) {
  int tamArray = atoi(argv[1]);
  int rank, size;
  MPI_Status status;
  int  arr[MAX]={16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int *arr = (int*) malloc(tamArray*sizeof(int));
  int i, count;
  int A, B,value[1];
  srand(time(0));	
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size); 
  
  /*THIS VERSION GENERATES "MAX" RANDOM VALUES AND USES MPI_SCATTER
   * TO DISTRIBUTE THESE TO EACH PROCESS.  HERE, EACH PROCESS RECEIVES
   * ONE VALUE
  */
	
  if(rank==0) {
    printf("Initial array: ");
    for (i=0;i<tamArray;i++) {
      arr[i]=rand()%100;
      printf("%d ", arr[i]);
    }
    printf("\n");
  }

  MPI_Scatter(&arr,1,MPI_INT,&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //printf("Rank %d receives %d\n", rank, value[0]);
  for(i=0;i<tamArray;i++) {
    if(i%2 == 0) {
      if(rank%2 == 0) {
        MPI_Send(&value[0],1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        MPI_Recv(&value[1],1,MPI_INT,rank+1,0,MPI_COMM_WORLD,&status);
        if(value[1]<value[0]) {
          value[0] = value[1];
        }
        //printf("Rank %d i: %d, %d\n", rank,i, value[0]);
      }
      else {
        MPI_Recv(&value[1],1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
        MPI_Send(&value[0],1,MPI_INT,rank-1,0,MPI_COMM_WORLD);
        if(value[1]>value[0]) {
          value[0] = value[1];
        }
        //printf("Rank %d i: %d, %d\n", rank,i, value[0]);
      }
    }
    else {
      if((rank%2 == 1) && (rank != (tamArray-1))) {
        MPI_Send(&value[0],1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        MPI_Recv(&value[1],1,MPI_INT,rank+1,0,MPI_COMM_WORLD,&status);
        if(value[1]<value[0]) {
          value[0] = value[1];
        }
        //printf("Rank %d i: %d, %d\n", rank,i, value[0]);
      }
      else if(rank != 0 && rank != (tamArray-1)) {
        MPI_Recv(&value[1],1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
        MPI_Send(&value[0],1,MPI_INT,rank-1,0,MPI_COMM_WORLD);
        if(value[1]>value[0]) {
          value[0] = value[1];
        }
        //printf("Rank %d i: %d, %d\n", rank,i, value[0]);
      }
    }
  } 
  //if(rank == 0) {
    //printf("%d: meow!\n", rank);
  //}		
  //MPI_Scatter(&arr,1,MPI_INT,&value, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Gather(&value[0],1,MPI_INT,&arr[0],1,MPI_INT,0,MPI_COMM_WORLD);
  if(rank==0) {
    printf("Sorted array: ");
    for (i=0;i<tamArray;i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");
  }
  MPI_Finalize();

  return 0;
}
