# build helloworld executable when user executes "make"
my_simple: main.o
	$(CC) $(LDFLAGS) main.o -o main
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o my_simple
