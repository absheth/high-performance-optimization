/*
 * ISE 599 Asg 1: Akash B. Sheth || due 09/04/18.
 * This simple timer will perform at least mflop MFLOPS in order to get
 * timings above clock resolution, and can be compiled to use wall or cpu
 * time.
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> /* rand() prototyped here */
#include <sys/time.h>
#ifndef SUN_HR
#include <sys/resource.h>
#endif


// TODO
/*
 * RETURNS: elapsed time (in seconds) since arbitrary starting point, using a
 * variety of system clocks, as selected by macros
 */
double my_time()
{
    /*
     * Wall timers
     */
#ifdef USEWALL /* standard unix walltime - gettimeofday */

    struct timeval tv;
    fprintf(stdout, "# Using USEWALL\n");
    gettimeofday(&tv, NULL);
    return(tv.tv_sec +
            tv.tv_usec/1000000.0);

#else          /* standard unix cputime - getrusage */

    fprintf(stdout, "# Not using USEWALL\n");
    // struct timeval user_cpu, system_cpu;
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    // user_cpu = usage.ru_utime;
    // system_cpu = usage.ru_stime;
    return(usage.ru_utime.tv_sec + usage.ru_utime.tv_usec/1000000.0 + usage.ru_stime.tv_sec + usage.ru_stime.tv_usec/1000000.0);
    // return(user_cpu.tv_sec + user_cpu.tv_usec/1000000.0 + system_cpu.tv_sec + system_cpu.tv_usec/1000000.0);
#endif
}

double my_drand()
    /*
     * RETURNS: random double precision number in range [-0.5, 0.5]
     */
{
    long ll;
    double dr;
    ll = random();                            /* get random integer */
    dr = (1.0 * ll) / (1.0 * RAND_MAX) - 0.5; /* make it real [-0.5,0.5] */
    return (dr);
}


// TODO
/*
 * Times as many N-length dot product calls as necessary to produce
 * mflop MFLOPS (mflop is inflated to avoid clock resolution errors).
 * RETURNS: elapsed time (in seconds) for average call to ddot().
 */
double DoTime(int n, double mflop)

{
    fprintf(stdout, " -- in DoTime --\n");
    double ddot(int N, double *X, double *Y);
    double dot = 0.0, t0, t2, *X, *Y;
    int i, nrep;
    /*
     * Missing some code
     */
    nrep = (mflop * 1000000.0 + n-1) / (1.0 * n);
    if (nrep < 1) {
        nrep = 1;
    }
    fprintf(stdout, "nrep: %d\n", nrep);

    // Populate the vectors
    X = (double *) calloc(n, sizeof(double));
    Y = (double *) calloc(n, sizeof(double));
    for (i = 0; i < n; ++i) {
        X[i] = my_drand();
        Y[i] = my_drand();
    }

    // DEBUG
    //  fprintf(stdout, "X: [");
    //  for (i = 0; i < n; ++i) {
    //      fprintf(stdout, "%f, ", X[i]);
    //  }
    //  fprintf(stdout, "] \n");

    //  printf("Y: [");
    //  for (i = 0; i < n; ++i) {
    //      fprintf(stdout, "%f, ", Y[i]);
    //  }
    //  fprintf(stdout, "] \n");


    t0 = my_time();
    for (i = 0; i < nrep; i++) {
        dot = ddot(n, X, Y);
    }
    t2 = my_time() - t0;

    fprintf(stdout, "t0: %f\n", t0);
    fprintf(stdout, "t1: %f\n", t0+t2);
    fprintf(stdout, "t0 - t1 = %f\n", t2);

    // fprintf(stdout, "\n");

    // Release the memory
    free(X);
    free(Y);
    double avg = t2 / (nrep * 1.0);
    fprintf(stdout, "avg: %e\n", avg);
    return avg;
}

void PrintUsage(char *name)
    /*
     * Print usage info and quit with error
     */
{
    fprintf(stderr, "USAGE: %s [-n <N>] [-N <N0> <NN> <Ninc>] [-m <mflop>]\n", name);
    exit(-1);
}

void GetFlags(int nargs, char **args, int *N0, int *NN, int *Ninc, int *mflop)
    /*
     * Get flags from user and/or set defaults
     */
{
    // DEBUG
    fprintf(stdout, "--BEFORE--\n");
    fprintf(stdout, "Number of arguments: %d\n", nargs);
    fprintf(stdout, "Arguments %s\n", *args);
    fprintf(stdout, "N0: %d\n", *N0);
    fprintf(stdout, "NN: %d\n", *NN);
    fprintf(stdout, "Ninc: %d\n", *Ninc);
    fprintf(stdout, "MFLOPS: %d\n", *mflop);
    fprintf(stdout, "\n");

    int i;
    /*
     * Set defaults
     */
    *N0 = 200;
    *NN = 2000;
    *Ninc = 200;
    *mflop = 200;


    // *N0 = 2;
    // *NN = 5;
    // *Ninc = 1;
    // *mflop = 200;
    /*
     * See what user wants
     */
    for (i = 1; i < nargs; i++) {
        if (args[i][0] != '-' || i == nargs - 1)
            PrintUsage(args[0]);
        switch (args[i][1]) {
            case 'm':
                if (++i == nargs)
                    PrintUsage(args[0]);
                *mflop = atoi(args[i]);
                break;
            case 'n':
                if (++i == nargs)
                    PrintUsage(args[0]);
                *N0 = *NN = *Ninc = atoi(args[i]);
                break;
            case 'N':
                if (i + 3 >= nargs)
                    PrintUsage(args[0]);
                *N0 = atoi(args[i + 1]);
                *NN = atoi(args[i + 2]);
                *Ninc = atoi(args[i + 3]);
                i += 3;
                break;
            default:
                fprintf(stderr, "\nUNKNOWN FLAG (ARG %d) : '%s'!\n", i, args[i]);
                PrintUsage(args[0]);
        }
    }

    // DEBUG
    fprintf(stdout, "--AFTER--\n");
    fprintf(stdout, "Number of arguments: %d\n", nargs);
    fprintf(stdout, "Arguments %s\n", *args);
    fprintf(stdout, "N0: %d\n", *N0);
    fprintf(stdout, "NN: %d\n", *NN);
    fprintf(stdout, "Ninc: %d\n", *Ninc);
    fprintf(stdout, "MFLOPS: %d\n", *mflop);
    fprintf(stdout, "\n");

}


// Main method
int main(int nargs, char **args) {
    int N0, NN, Ninc, i, mflop;
    double tim, mf;
    /*
     * Get timing range, and print header
     */
    GetFlags(nargs, args, &N0, &NN, &Ninc, &mflop);
    fprintf(stdout, "\nTIMING VECTOR PRODUCTS IN RANGE [%d,%d:%d]; FORCED MFLOP=%d\n", N0, NN, Ninc,
            mflop);
    /*
     * Loop over all cases to be timed
     */
    for (i = N0; i <= NN; i += Ninc) {
        fprintf(stdout, "-----------\n");
        tim = DoTime(i, mflop);
        //  fprintf(stdout, "Time returned: %f\n", tim);
        mf = (2.0 * i) / (tim * 1000000.0);
        fprintf(stdout, "   N=%8d, time=%e, MFLOPS=%.2f\n", i, tim, mf);
        fprintf(stdout, "-----------\n");
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "DONE\n");
    return (0);
}
