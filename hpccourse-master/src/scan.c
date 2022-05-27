#include "myhead.h"
//使用通信子划分的方法实现进程iam的scan
void snglscan(MPI_Comm comm,int np, int iam,int root, float a,float *b){

    MPI_Comm newcomm;
    int color, key;
    if(iam <= root)
        color = 0;
    else
    {
        color = MPI_UNDEFINED;
    }
    key = iam;
    MPI_Comm_split(comm,color,key,&newcomm);
    //MPI_COMM_NULL
    if(iam <= root){
        MPI_Reduce(&a,b,1,MPI_FLOAT,MPI_SUM,root,newcomm);
    }

}