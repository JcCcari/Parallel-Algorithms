CC=gcc
CFLAGS=-g -Wall 
OPENMP_LIBS=-fopenmp
OTHER_FLAG=-I.

SOURCE_EVEN1=omp_odd_even1.c
OBJ_EVEN1=omp_odd_even1.out

SOURCE_EVEN2=omp_odd_even2.c
OBJ_EVEN2=omp_odd_even2.out

make:
	$(CC) $(CFLAGS) $(OPENMP_LIBS) $(SOURCE_EVEN1) -o $(OBJ_EVEN1)
	$(CC) $(CFLAGS) $(OPENMP_LIBS) $(OTHER_FLAG) $(SOURCE_EVEN2) -o $(OBJ_EVEN2)

clean: 
	rm *.out

test-oddeven1:
	./$(OBJ_EVEN1) 1 20000 g
	./$(OBJ_EVEN1) 2 20000 g
	./$(OBJ_EVEN1) 3 20000 g
	./$(OBJ_EVEN1) 4 20000 g

test-oddeven2:
	./$(OBJ_EVEN2) 1 20000 g
	./$(OBJ_EVEN2) 2 20000 g
	./$(OBJ_EVEN2) 3 20000 g
	./$(OBJ_EVEN2) 4 20000 g
