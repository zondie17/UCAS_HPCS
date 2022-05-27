#include "myhead.h"
void typemat( m, n, lda, newtp )
int m, n, lda;
MPI_Datatype *newtp;
{
	MPI_Type_vector(m, n, lda, MPI_FLOAT, newtp);
}

void scopy(m, k, a, lda, t, ldt)
int m, k, lda, ldt;
float *a, *t;
{
	int i,j;
	for ( i=0; i<m; i++ )
	for ( j=0; j<k; j++ ) 
		t[i*ldt+j] = a[i*lda+j];
}

/**
 * 初始化矩阵数值， a(i,j) = i+j, b(i,j) = \case{1:i+j=even}{-1:i+j=odd}
 */
void setinitab(p, myrow, mycol, m, k, n, a, lda, b, ldb)
int p, myrow, mycol;
int m, k, n, lda, ldb;
float *a, *b;
{
	int i, j, offsizea, offsizeb;

	offsizea = m*myrow + k*mycol;
	offsizeb = k*myrow + n*mycol;

	for ( i=0; i<m; i++ )
	for ( j=0; j<k; j++ )
		a[i*lda+j] = i+j+offsizea;

	for ( i=0; i<k; i++ )
	for ( j=0; j<n; j++ )
		b[i*ldb+j] = 1;
}

/**
 * 对矩阵分的块应该分成n*n块，如果不是，需要对A和B矩阵进行不同处理，过于麻烦，干脆方块
 * a[i][j] = a[i*lda+j]
 */

// void matmul(int m, int k , int n, int lda, float *a ,int ldb, float *b, int ldc, float *c);
void cannon(MPI_Comm rowcom,MPI_Comm colcom,int p, int myrow,int mycol, int m, int k, int n,float *a, int lda,float* b, int ldb, float *c, int ldc, 
            float* at/*临时存储ab块的空间*/, int ldaw, float* bt, int ldbw)
{
	int i, j, l, front, next;
	MPI_Datatype btp, attp, bttp;
	MPI_Status st;

	typemat(k, n, ldb, &btp);
	typemat(m, k, ldaw, &attp);
	typemat(k, n, ldbw, &bttp);
	MPI_Type_commit(&btp);
	MPI_Type_commit(&attp);
	MPI_Type_commit(&bttp);

	l = myrow; //每个进程负责的列号
	
	front = (myrow-1+p)%p;
	next = (myrow+1)%p;

	for ( i=0; i<m; i++ )
	for ( j=0; j<n; j++ )
		c[i*ldc+j] = .0;

	for ( i=0; i < p ; i++ )
	{
		if ( mycol == l ) scopy(m, k, a, lda, at, ldaw);//从a copy到at
		MPI_Bcast( at, 1, attp, l, rowcom );
		matmul(m, k, n,ldaw, at, ldb,b, ldc, c);
		// gemmm(m, k, n, at, ldaw, b, ldb, c, ldc);
		if ( i == p-1 ) continue;
		MPI_Sendrecv(b, 1, btp, front, 1, bt, 1, bttp, next, 1, colcom, &st);
		l = (l+1) % p;
	}
	
    return;
}
