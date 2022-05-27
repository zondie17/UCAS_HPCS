#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"

typedef struct 
{
	int a;
	float b[2];
	char c[3];
} abc;

void mesh( int iam,  int np, MPI_Comm comm, int p, int q, int* myrow, int* mycol, \
           MPI_Comm * rowcom, MPI_Comm *colcom );

void mybegin(int *, char***, MPI_Comm*, int*, int*);

void myend();

void ring(int, int *, MPI_Comm, int, int);

void datatype(char, MPI_Datatype *);

void mpistruct(MPI_Datatype *);

void init_a(int m, int k, int lda,float *a ,int iam);
void init_b(int k, int n,int ldb, float *b,int iam);

void matmul(int m, int k , int n, int lda, float *  ,int ldb, float *b , int ldc, float *c);

void rcmatmul(MPI_Comm comm,int np, int iam,int m, int k, int n,int lda,float * a, int ldb,float *b ,int ldc, float *c,int ldw, float *w);

void snglscan(MPI_Comm comm,int np, int iam,int root, float a,float *b);

void typemat( int m, int n, int lda, MPI_Datatype *newtp );

void scopy(int m, int k, float * a, int lda, float *t, int ldt);

void setinitab(int p, int myrow, int mycol, int m, int k, int n, float *a, int lda, float * b, int ldb);


void cannon(MPI_Comm rowcom,MPI_Comm colcom,int p, int myrow,int mycol, int m, int k, int n,float *a, int lda,float* b, int ldb, float *c, int ldc, 
            float* at/*临时存储ab块的空间*/, int ldaw, float* bt, int ldbw);