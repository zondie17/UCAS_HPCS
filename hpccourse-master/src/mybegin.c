#include "myhead.h"
void mybegin(argc, argv, comm, np, iam)
MPI_Comm *comm;
int *argc, *np, *iam;
char ***argv;
{
	MPI_Init(argc, argv);
	MPI_Comm_dup(MPI_COMM_WORLD, comm);
	MPI_Comm_size(*comm, np); //进程数量？
	MPI_Comm_rank(*comm, iam);//进程号
	 
	return ;
}