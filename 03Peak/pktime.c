#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

long long GetCycleCount();
double GetMflop(int mflop, double *dum);

#ifndef SparcMhz
#error "need to define your clock rate as SparcMhz!"
#endif
double ClickToSec(long long clicks)
{
    static const double mul = 1.0 / (SparcMhz*1000000.0);
    return(clicks*mul);
}


void PrintUsage(char *exe)
{
    fprintf(stderr, "USAGE: %s [-m <mflop>]\n");
    exit(1);
}

int GetFlags(int nargs, char **args) /* RETURNS: # of mflops to perform */
{
    int mflop=800, i;
    for (i=1; i < nargs; i++)
    {
        if (args[i][0] != '-' || i == nargs-1)
            PrintUsage(args[0]);
        switch(args[i][1])
        {
            case 'm':
                mflop = atoi(args[++i]);
                break;
            default:
                fprintf(stderr, "\nUNKNOWN FLAG : '%s'!\n", args[i]);
                PrintUsage(args[0]);
        }
    }
    return(mflop);
}

int main(int nargs, char **args)
{
    int mflop, i;
    double dum[16];
    double mf, pcPeak;

    mflop = GetFlags(nargs, args);
    for (i=0; i < 16; i++)
        dum[i] = 0.0;
#if 0
    if (nargs > 1)
        mflop = atoi(args[1]);
#endif

    mf = GetMflop(mflop, dum);

    pcPeak = 100.0*(mf / (SparcMhz*2.0));
    printf("Peak mflop = %.2f (%.2f percent of peak)\n", mf, pcPeak);
}
