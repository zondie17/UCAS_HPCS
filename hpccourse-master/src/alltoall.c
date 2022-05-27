#include "mpi.h"
#include "stdio.h"

int My_Alltoall(void *sendBuffer, int sendcount, MPI_Datatype sendtype,
                void *receiveBuffer, int recvcount, MPI_Datatype recvtype, MPI_Comm comm, int rank, int size)
{
    int i, j;
    MPI_Status status;

    for (i = 0; i < size; i++)
    {
        if (rank == i)
        {
            MPI_Sendrecv(sendBuffer + (sendcount * i) * sizeof(sendtype), sendcount, sendtype, i, 99, 
            receiveBuffer + (recvcount * i) * sizeof(recvtype), recvcount, recvtype, i, 99, comm, &status);
        }
    }

    for (i = 0; i < size; i++)
    {
        if (rank != i)
        {
            MPI_Send(sendBuffer + (sendcount * i) * sizeof(sendtype), sendcount, sendtype, i, i, comm);
        }
    }

    for (i = 0; i < size; i++)
    {
        if (rank != i)
        {
            MPI_Recv(receiveBuffer + (recvcount * i) * sizeof(recvtype), recvcount, recvtype, i, rank, comm, &status);
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    int i, myrank, size;
    int *send_buffer;
    int *recv_buffer;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    size = size * 2;

    send_buffer = (int *)calloc(size, sizeof(int));
    recv_buffer = (int *)calloc(size, sizeof(int));

    for (i = 0; i < size; i++)
        send_buffer[i] = i + myrank * size;

    My_Alltoall(send_buffer, 2, MPI_INT,
                recv_buffer, 2, MPI_INT, MPI_COMM_WORLD, myrank, size / 2);

    for (i = 0; i < size; i++)
    {
        printf("myrank=%d,sendbuf[%d]=%d\n", myrank, i, send_buffer[i]);
    }

    for (i = 0; i < size; i++)
        printf("myrank = %d, recv_buffer[%d] = %d\n", myrank, i, recv_buffer[i]);

    free(recv_buffer);
    free(send_buffer);
    MPI_Finalize();
    return 0;
}