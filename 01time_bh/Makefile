CC = gcc
CCFLAGS = -O3 -fomit-frame-pointer
TIMEDEF =

OBJ = dottime.o ddot.o
xdottime: $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $(OBJ)
dottime.o : dottime.c
	$(CC) $(CCFLAGS) $(TIMEDEF) -c dottime.c
ddot.o : ddot.c
	$(CC) $(CCFLAGS) -c ddot.c
clean :
	rm -f $(OBJ)
kill : 
	rm -f xdottime $(OBJ)
