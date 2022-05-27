#include <stdio.h>
#include "mpi.h"
//第二问看不懂
void mesh( iam,  np, comm, p, q, myrow, mycol, \
           rowcom, colcom )
int iam, np, p, q, *myrow, *mycol; MPI_Comm comm, *rowcom, *colcom;
{
    int color, key;
    if( np < p*q ) return;
    if( iam < p*q ) color = iam / q;
    else color = MPI_UNDEFINED;
    key = iam;
    MPI_Comm_split( comm, color, key, rowcom );
    
    /*column communicator*/
    if( iam < p*q ) color = iam % q;
    else color = MPI_UNDEFINED;
    key = iam;
    MPI_Comm_split( comm, color, key, colcom );
    if( iam <p*q ) {
        MPI_Comm_rank( *colcom, myrow );
        MPI_Comm_rank( *rowcom, mycol );
    } 
    return;
            
}

int main(int args, char ** argv){
    MPI_Init(&args,&argv);

    const int m = 100;
    const int n = 100;
    
    const int p = 5;
    const int q = 5;

    int myrank , numprocs;
    MPI_Comm global_comm,row_comm,col_comm;
    MPI_Comm_dup(MPI_COMM_WORLD,&global_comm);

    MPI_Comm_rank(global_comm,&myrank);
    MPI_Comm_size(global_comm,&numprocs);

    int row,col;

    mesh(myrank,numprocs,global_comm,p,q,&row,&col,&row_comm,&col_comm);

    float a;
    if(row == 0 && col == 0){
        a = 100.1;
    }
    else a = -1;
    if(row == 0 && col == 0)
        MPI_Bcast(&a,1,MPI_FLOAT,0,row_comm);
    MPI_Barrier(row_comm);
    MPI_Bcast(&a,1,MPI_FLOAT,col,col_comm);

    MPI_Finalize();
    return 0;
}