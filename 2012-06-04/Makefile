#
# Makefile for sorting algorithms
#

#DEFS	= -g
DEFS	= 

#CC	= gcc 
CC	= cc

sort: sort.o sort_util.o str_sel.o heap.o str_ins.o bubble.o shell.o quick.o quick_strins.o
	$(CC) $(DEFS) -o sort sort.o sort_util.o str_sel.o heap.o \
                         str_ins.o bubble.o shell.o quick.o quick_strins.o

sort.o: sort.c sort_util.h
	$(CC) $(DEFS) -c sort.c

sort_util.o: sort_util.c sort.h
	$(CC) $(DEFS) -c sort_util.c

str_sel.o: str_sel.c sort.h sort_util.h
	$(CC) $(DEFS) -c str_sel.c

heap.o: heap.c sort.h sort_util.h
	$(CC) $(DEFS) -c heap.c

str_ins.o: str_ins.c sort.h sort_util.h
	$(CC) $(DEFS) -c str_ins.c

bubble.o: bubble.c sort.h sort_util.h
	$(CC) $(DEFS) -c bubble.c

quick.o: quick.c sort.h sort_util.h
	$(CC) $(DEFS) -c quick.c

shell.o: shell.c sort.h sort_util.h
	$(CC) $(DEFS) -c shell.c

quick_strins.o: quick_strins.c sort.h sort_util.h
	${CC} ${DEFS} -c quick_strins.c

clean:
	rm -f *~ *.o

allclean:
	rm -f *~ *.o sort
