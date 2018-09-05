/*
 * ISE 599 Asg 1: Akash Sheth || due 09/04/18.
 * This simple timer will perform at least mflop MFLOPS in order to get
 * timings above clock resolution, and can be compiled to use wall or cpu
 * time.
 *
 * Observations:
 * 1) There is difference in the timing when `sleep` is used. Wall time takes
 *    sleep time into account whereas cpu time does not.
 * 2) As we are calculating nreps using mflops, timing is similar to different mflops.
 * 3) When the compiler optimization level is changed from `O3` to `O0`,
 *    it takes more time to compute and in turn the number of mflops are less and vice-versa.
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> /* rand() prototyped here */
#include <sys/time.h>
#ifndef SUN_HR
#include <sys/resource.h>
#endif


/*
 * RETURNS: elapsed time (in seconds) since arbitrary starting point, using a
 * variety of system clocks, as selected by macros
 */
long long my_time()
{
    /*
     * Wall timers
     */
#ifdef USEWALL /* standard unix walltime - gettimeofday */

    struct timeval w_time;
    gettimeofday(&w_time, NULL);
#ifdef PentiumMhz
    // fprintf(stdout, "PentiumMHZ - Set \n");
    long long GetCycleCount(void);
    long long value = GetCycleCount();

    // fprintf(stdout, "Value: %lld \n", value);

    return(value);
#else
    // fprintf(stdout, "PentiumMHZ - Not set \n");
    // return(w_time.tv_sec + w_time.tv_usec*1.0e-6);
    long long lret;
    lret = w_time.tv_sec;
    lret *= 1000000;
    lret += w_time.tv_usec;
    return(lret);
#endif

#else /* standard unix cputime - getrusage */

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    // return(usage.ru_utime.tv_sec + usage.ru_utime.tv_usec*1.0e-6);
    return(usage.ru_utime.tv_sec*1000000 + usage.ru_utime.tv_usec);

#endif
}

/*
 * RETURNS: random double precision number in range [-0.5, 0.5]
 */
double my_drand()

{
    long ll;
    double dr;
    ll = random();                            /* get random integer */
    dr = (1.0 * ll) / (1.0 * RAND_MAX) - 0.5; /* make it real [-0.5,0.5] */
    return (dr);
}

/*
 * Return seconds
 */
double ClickToSec(long long clicks) {
    
    fprintf(stdout, "Clicks: %lld \n", clicks);
    return(clicks*1.0e-6);
}

/*
 * Times as many N-length dot product calls as necessary to produce
 * mflop MFLOPS (mflop is inflated to avoid clock resolution errors).
 * RETURNS: elapsed time (in seconds) for average call to ddot().
 */
double DoTime(int n, double mflop)

{
    double ddot(int N, double *X, double *Y);
    double dot = 0.0, *X, *Y;
    long long t0, t1;
    int i, nrep;

    nrep = (mflop * 1000000.0 + 2*n-1) / (1.0 * 2*n);
    fprintf(stdout, "For nrep: %d \n", nrep);
    if (nrep < 1) {
        nrep = 1;
    }

    // Allocate memory and populate the vectors
    X = (double *) malloc(n * sizeof(double));
    Y = (double *) malloc(n * sizeof(double));
    for (i = 0; i < n; ++i) {
        X[i] = my_drand();
        Y[i] = my_drand();
    }

    t0 = my_time();
    
    fprintf(stdout, "Time t0 : %lld \n", t0);
    for (i = 0; i < nrep; i++) {
        dot = ddot(n, X, Y);
        dot = -dot;
    }
    // sleep(1); // Trial
    t1 = my_time();
    fprintf(stdout, "Time t1 : %lld \n", t1);
    fprintf(stdout, "Time difference: %lld \n", t1-t0);
    fprintf(stdout, "Time to be returned: %lf \n", (t1-t0)*1.0e-6);
    // Release the memory
    free(X);
    free(Y);
    // return (t1 / (nrep * 1.0)); // returns average time
    return (ClickToSec(t1-t0)); // returns average time
}

/*
 * Print usage info and quit with error
 */
void PrintUsage(char *name) {
    fprintf(stderr, "USAGE: %s [-n <N>] [-N <N0> <NN> <Ninc>] [-m <mflop>] [-C <kbytes>] [-S <nsample>] \n", name);
    exit(-1);
}

/*
 * Get flags from user and/or set defaults
 */
void GetFlags(int nargs, char **args, int *N0, int *NN, int *Ninc, int *mflop, int *cache_size, int *nsample) {
    
    fprintf(stdout, "nargs: %d \n", nargs);
    int i;
    /*
     * Set defaults
     */
    *N0 = 200;
    *NN = 2000;
    *Ninc = 200;
    *mflop = 200;
    *cache_size = 32000; // In Kbs
    *nsample = 1;
    /*
     * See what user wants
     */
    for (i=1; i < nargs; i++)
    {
        if (args[i][0] != '-' || i == nargs-1)
            PrintUsage(args[0]);
        fprintf(stdout, "i: %d \n", i);
        switch(args[i][1])
        {
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
                if (i+3 >= nargs)
                    PrintUsage(args[0]);
                *N0 = atoi(args[i+1]);
                *NN = atoi(args[i+2]);
                *Ninc = atoi(args[i+3]);
                i += 3;
                break;
            case 'C':
                if (++i == nargs)
                    PrintUsage(args[0]);
                *cache_size = atoi(args[i]);
                break;
            case 'S':
                if (++i == nargs)
                    PrintUsage(args[0]);
                *nsample= atoi(args[i]); 
                break;
            default:
                fprintf(stderr, "\nUNKNOWN FLAG (ARG %d) : '%s'!\n", i, args[i]);
                PrintUsage(args[0]);
        }
    }
}


// Main method
int main(int nargs, char **args) {
    int N0, NN, Ninc, i, mflop, cache_size, nsample;
    double tim, mf;

    /*
     * Get timing range, and print header
     */
    GetFlags(nargs, args, &N0, &NN, &Ninc, &mflop, &cache_size, &nsample);
    fprintf(stdout,
            "\nTIMING VECTOR PRODUCTS IN RANGE [%d,%d:%d]; FORCED MFLOP=%d; CACHE SIZE: %d; NSAMPLE: %d\n;",
            N0, NN, Ninc, mflop, cache_size, nsample);
    exit(0);    
    /*
     * Loop over all cases to be timed
     */
    for (i=N0; i <= NN; i += Ninc)
    {
        tim = DoTime(i, mflop);
        
        fprintf(stdout, "Time returned: %lf \n", tim);
        mf = (2.0*i) / (tim*1000000.0);
        fprintf(stdout, "   N=%8d, time=%e, MFLOPS=%.2f\n", i, tim, mf);
        fprintf(stdout, "---------------------------------------\n");
        fprintf(stdout, "\n");

    }
    fprintf(stdout, "DONE\n");
    return(0);
}
