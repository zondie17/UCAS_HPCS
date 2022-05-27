#include <stdio.h>
#include "mpi.h"

//第二问是可以的，用MPI_Type_indexed就行
void make_newtype(int m, int n, int lda,MPI_Datatype * newtype){

    MPI_Datatype vec_type;
    const int count = m;
    const int length = m;
    const int stride = lda;

    MPI_Type_vector(count, length, stride, MPI_INT, &vec_type);
    MPI_Type_create_resized(vec_type,0,sizeof(int )*( m * lda + n),newtype);
}
//修改源矩阵的参数m,n和子矩阵的sub_m,sub_n
int main(int args, char ** argv){

    MPI_Init(&args,&argv);
    MPI_Datatype submat;

    const int m = 4, n = 4;
    const int lda = n;
    int sub_m = 2;
    int sub_n = 2;
    int a[4][4] ;
    int recv[4][4];

//分块矩阵 大矩阵4 * 4,小矩阵2 * 2
    make_newtype(sub_m,sub_n,lda,&submat);
    MPI_Type_commit(&submat);
    int rank , numprocs;
    MPI_Comm comm;

    MPI_Comm_dup(MPI_COMM_WORLD,&comm);
    MPI_Comm_size(comm,&numprocs); 
    MPI_Comm_rank(comm,&rank);
    MPI_Status st;
    for(int i = 0 ; i < m ; i ++){
        for(int j = 0 ; j < n ; j++){
            a[i][j] = i + j + rank;
            recv[i][j] = 0;
        }
    }
    //发送对角块(0,0) 和 (1,1)
    if(rank == 0){
        MPI_Send(&a[0][0], 2, submat,1,1,comm);
    }
    else if(rank == 1){
        MPI_Recv(recv,2,submat,0,1,comm,&st);
        for(int i = 0 ; i < m; i++){
            for(int j = 0 ; j < n ; j++){
                printf("%d ",recv[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}