#Mikefile

OPT = -O2
LIBPATH =../lib
MYLIB = mympi
LIBMYMPI = libmympi.a
# LIBOBJS = ../obj/mybegin.o ../obj/myend.o ../obj/ring.o ../obj/datatype.o ../obj/mpistruct.o ../obj/rcmatmul.o ../obj/mesh.o ../obj/scan.o ../obj/main.o
LIBOBJS = mybegin.o myend.o ring.o datatype.o mpistruct.o rcmatmul.o mesh.o scan.o main.o cannon.o

CC = mpicc
CFLAG = -I../include
%.o: %.c
	$(CC) -c $(OPT)  $(CFLAG) -o $@ $<

#ultimate target
main:main.o mylib
	$(CC) $(OPT) $(CFLAG) -o $@ $< -L$(LIBPATH) -l$(MYLIB) -lm 
	@mv main ../bin
	# @mv *.o ../obj

#make a library
mylib: $(LIBOBJS)
		ar rcs $(LIBMYMPI) $(LIBOBJS)
		mv $(LIBMYMPI) ../lib
 
exam:exam1.c exam2.c
	$(CC) -o exam1 $(CFLAG) exam1.c
	$(CC) -o exam2 $(CFLAG) exam2.c
	@mv exam1 ../bin
	@mv exam2 ../bin

.PHONY = clean
clean:
		rm -f $(LIBOBJS)  ../lib/* ../obj/* ../bin/*
 