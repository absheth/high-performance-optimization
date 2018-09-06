CC = gcc
CCFLAGS = -O3 -fomit-frame-pointer
TIMEDEF = -DUSEWALL
MHZ = -DPentiumMhz=3492.128
OBJ = dottime.o ddot.o GetCycleCount.o
xdottime: $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $(OBJ)
dottime.o : dottime.c
	$(CC) $(CCFLAGS) $(TIMEDEF) $(MHZ) -c dottime.c
ddot.o : ddot.c
	$(CC) $(CCFLAGS) -c ddot.c
GetCycleCount.o : GetCycleCount.S
	$(CC) $(CCFLAGS) $(TIMEDEF) -c GetCycleCount.S
clean :
	rm -f $(OBJ) xdottime
kill :
	rm -f xdottime $(OBJ)
