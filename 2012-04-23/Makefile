CC = clang

q1: intlist.o q1.o
	@echo "$? are modified."
	$(CC) -o $@ intlist.o q1.o

q2_list: intlist.o intqueue_list.o q2.o
	@echo "$? are modified."
	$(CC) -o $@ intlist.o intqueue_list.o q2.o

q2_array: intqueue_array.o q2.o
	@echo "$? are modified."
	$(CC) -o $@ intqueue_array.o q2.o

.c.o:
	$(CC) -c $<

clean:
	$(RM) *.o

