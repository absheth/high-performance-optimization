CC = gcc
CCFLAGS = -mcpu=ultrasparc3 -mtune=ultrasparc3 -fomit-frame-pointer -std=c89 -O3
MHZ = 1503    # replace this with the Mhz of your machine!
ASM = gcc -c
PRG=1

objs = pktime.o GetMflop.o GetCycleCount.o
xpktime : $(objs)
	$(CC) $(CCFLAGS) -o $@ $(objs)
pktime.o : pktime.c
	$(CC) $(CCFLAGS) -DSparcMhz=$(MHZ) -o $@ -c pktime.c
GetMflop.o : GetMflop.c
	$(CC) $(CCFLAGS) -o $@ -c GetMflop.c
GetCycleCount.o : GetCycleCount.S
	$(ASM) -DUSEWALL=1 -DSparcMhz=$(MHZ) GetCycleCount.S

GetMflop.s : GetMflop.c
	$(CC) $(CCFLAGS) -o $@ -S GetMflop.c

clean :
	rm -f $(objs) xpktime GetMflop.s
