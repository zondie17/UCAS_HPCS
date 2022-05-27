
#include "myhead.h"
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