#include "myhead.h"

void ring( m, n, comm, np, iam)
int m, *n, np, iam;
MPI_Comm comm;
{
	int next = (iam + 1) % np, front = (np + iam - 1) % np, tag = 1;
	MPI_Status st;
	if( iam % 2 == 0 ) {
		MPI_Send( &m, 1, MPI_INT, next, tag, comm );
		MPI_Recv( n, 1, MPI_INT, front, tag, comm, &st );
	}
	else {
		MPI_Recv( n, 1, MPI_INT, front, tag, comm, &st );
		MPI_Send( &m, 1, MPI_INT, next, tag, comm );
	}
	return;
}