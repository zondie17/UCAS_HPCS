#/bin/bash

numprocs=$1

if [ -z "$1" ];then
    numprocs=4
fi

mpirun --oversubscribe -np ${numprocs}  ./bin/main