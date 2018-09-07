/*
 * ISE 599 Assignment 2: Akash Sheth || due 09/06/18.
 * This simple timer will perform at least mflop MFLOPS in order to get
 * timings above clock resolution, and can be compiled to use wall or cpu
 * time.
 *
 * Observations:
 * 1) Correct time is cycle accurate timer and GetCycleCount is an undefined symbol
 * 
 * 2) Yes. When the timer is run without cache flushing, the rough cache edges are visible
      Yes. When the cache fushing is enabled, the curve matches the typical curve as given
      in handout.
      Config used: ./xdottime -N 100 100000 100 -m 1000 -S 1
 * 3) Yes. Peforming multiple samples of smaller problem produces steady results at lower 
      mflop settings
      Config used: ./xdottime -N 100 100000 100 -m 10 -S 1 
 * 4) Interpreting one repitition as nrep to be calculated as 1, I got following results 
      when run 15 times. 

      Config used: ./xdottime -N 1000 1000 1000 -m 10  
       
      -S 1  --> N=    1000, time=1.218600e-06, MFLOPS=1641.23 
      -S 2  --> N=    1000, time=1.160505e-06, MFLOPS=1723.39 
      -S 3  --> N=    1000, time=1.155314e-06, MFLOPS=1731.13 
      -S 4  --> N=    1000, time=1.151505e-06, MFLOPS=1736.86 
      -S 5  --> N=    1000, time=1.152306e-06, MFLOPS=1735.65
      -S 6  --> N=    1000, time=1.153247e-06, MFLOPS=1734.23 
      -S 7  --> N=    1000, time=1.161787e-06, MFLOPS=1721.49 
      -S 8  --> N=    1000, time=1.165279e-06, MFLOPS=1716.33
      -S 9  --> N=    1000, time=1.164489e-06, MFLOPS=1717.49
      -S 10 --> N=    1000, time=1.155418e-06, MFLOPS=1730.98 
      -S 11 --> N=    1000, time=1.151767e-06, MFLOPS=1736.46 
      -S 12 --> N=    1000, time=1.152919e-06, MFLOPS=1734.73 
      -S 13 --> N=    1000, time=1.152183e-06, MFLOPS=1735.84 
      -S 14 --> N=    1000, time=1.154311e-06, MFLOPS=1732.64 
      -S 15 --> N=    1000, time=1.155212e-06, MFLOPS=1731.28 
      
      Results are quite steady.
      
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h> /* rand() prototyped here */
#include <sys/time.h>
#ifndef SUN_HR
#include <sys/resource.h>
#endif

/*
 * RETURNS: elapsed time (in microseconds) since arbitrary starting point, using a
 * variety of system clocks, as selected by macros
 */
long long my_time() {
    /*
     * Wall timers
     */
#ifdef USEWALL /* standard unix walltime - gettimeofday */

#ifdef PentiumMhz

    // fprintf(stdout, "USEWALL and Pentium \n");
    long long GetCycleCount(void);
    return(GetCycleCount());
#else
    
    // fprintf(stdout, "USEWALL \n");
    struct timeval w_time;
    gettimeofday(&w_time, NULL);
    return(w_time.tv_sec*1000000 + w_time.tv_usec);
#endif

#else /* standard unix cputime - getrusage */

    // fprintf(stdout, "CPU\n");
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return(usage.ru_utime.tv_sec*1000000 + usage.ru_utime.tv_usec);

#endif
}

/*
 * RETURNS: random double precision number in range [-0.5, 0.5]
 */
double my_drand() {
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

#if defined(USEWALL) && defined (PentiumMhz)
    // Clicks are clocks cycles 
    return((clicks/PentiumMhz)*1.0e-6);
#endif
    return(clicks*1.0e-6);
}

// A comparator function used by qsort
// Ref : https://www.geeksforgeeks.org/c-qsort-vs-c-sort/
int compare (const void * a, const void * b)
{
    if (*(double*)a > *(double*)b) return 1;
    else if (*(double*)a < *(double*)b) return -1;
    else return 0;
}
double GetGoodTime( int Nt, double *time) {
    
    int i;
    // fprintf(stdout, "\n");
    // fprintf(stdout, "Before sorting: ");
    // for (i = 0; i < Nt; i++) {
    //     fprintf(stdout, "%e, ", time[i]);
    // }
    // fprintf(stdout, "\n");

    qsort(time, Nt, sizeof(double), compare);

    // fprintf(stdout, "After sorting: ");
    // for (i = 0; i < Nt; i++) {
    //     fprintf(stdout, "%e, ", time[i]);
    // }
    // fprintf(stdout, "\n");

    //
#if defined (USEWALL) /* standard unix walltime - gettimeofday */
    // fprintf(stdout, "Returning lowest time: -->  %e \n ", time[0]);
    return time[0];
#endif
    int return_index = Nt/2;

    if (return_index == 0) {
        return_index = 1;
    }

    if (Nt&1) {
        if (Nt == 1) {
            // fprintf(stdout, "Median | Return index: %d \n", return_index-1);
            return time[return_index-1];
        }
        // fprintf(stdout, "Median | Return index: %d \n", return_index);
        return time[return_index];

    } else {

        // fprintf(stdout, "Median | Return average: %d and %d \n", return_index-1, return_index );
        return ((time[return_index-1] +  time[return_index])*0.5);
    }
}

/*
 * Times as many N-length dot product calls as necessary to produce
 * mflop MFLOPS (mflop is inflated to avoid clock resolution errors).
 * RETURNS: elapsed time (in seconds) for average call to ddot().
 */
double DoTime(int n, double mflop, int cache_size) {
    double ddot(int N, double *X, double *Y);
    double dot = 0.0, *X, *Y, *alloc_start, *iter_x, *iter_y;
    long long t0, t1;
    int i, nrep;

    nrep = (mflop*1000000.0 + 2*n-1) / (2.0*n);
    if (nrep < 1) {
        nrep = 1;
    }

    if(cache_size != 0) {
        //Cache flushing
        int cache_flush_size = cache_size * (1024/sizeof(double));
        int set_size = n+n; // Total number of operands in a set
        int no_of_sets = (cache_flush_size + set_size-1)/set_size; // Get the ceiling
        if (no_of_sets < 1) {
            no_of_sets = 1;
        }
        int total_elements = no_of_sets * set_size;
        // fprintf(stdout, "cache_flush_size: %d \n", cache_flush_size);
        // fprintf(stdout, "n: %d \n", n);
        // fprintf(stdout, "set_size: %d \n", set_size);
        // fprintf(stdout, "no_of_sets: %d \n", no_of_sets);
        // fprintf(stdout, "total_elements: %d \n", total_elements);
        // fprintf(stdout, "\n");

        // Allocate memory and populate the vectors
        alloc_start = (double *) malloc(sizeof(double) * total_elements);

        // split the vectors
        X = alloc_start + total_elements - set_size;
        Y = X + n;

        for (iter_x=alloc_start, i=total_elements-1 ; i >= 0; i--) {
            iter_x[i] = my_drand();
        }


        iter_x=X; iter_y=Y;
        int move_around = 0;

        t0 = my_time(); // start timer
        for (i = 0; i < nrep; i++) {

            dot += ddot(n, iter_x, iter_y);
            dot = -dot;
            if (++move_around != no_of_sets) {
                iter_x -= set_size; // change the pointing
                iter_y -= set_size; // change the pointing

            } else {
                iter_x=X;
                iter_y=Y;
                move_around=0;
            }
        }
        t1 = my_time(); // stop timer

        // Release the memory
        // free(X);
        free(alloc_start);
    } else {

        // Allocate memory and populate the vectors
        X = (double *) malloc(n * sizeof(double));
        Y = (double *) malloc(n * sizeof(double));
        for (i = 0; i < n; ++i) {
            X[i] = my_drand();
            Y[i] = my_drand();
        }

        t0 = my_time(); // start timer
        for (i = 0; i < nrep; i++) {
            dot += ddot(n, X, Y);
            dot = -dot;
        }
        t1 = my_time(); // stop timer

        // Release the memory
        free(X);
        free(Y);
    }
    // return (t1 / (nrep * 1.0)); // returns average time
    return (ClickToSec(t1-t0)/(1.0*nrep));
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
                if (*nsample == 0) {
                    *nsample = 1;
                }
                break;
            default:
                fprintf(stderr, "\nUNKNOWN FLAG (ARG %d) : '%s'!\n", i, args[i]);
                PrintUsage(args[0]);
        }
    }
}

// Main method
int main(int nargs, char **args) {
    int N0, NN, Ninc, i, j, mflop, cache_size, nsample;
    /*
     * Get timing range, and print header
     */
    GetFlags(nargs, args, &N0, &NN, &Ninc, &mflop, &cache_size, &nsample);
    fprintf(stdout,
            "\nTIMING VECTOR PRODUCTS IN RANGE [%d,%d:%d]; FORCED MFLOP=%d; CACHE SIZE: %d; NSAMPLE: %d;\n",
            N0, NN, Ninc, mflop, cache_size, nsample);

    double tim, mf;

    for (i = N0; i <= NN; i += Ninc)
    {
        double *time_array;

        // Allocate memory for n samples.
        time_array = (double *) malloc(nsample * sizeof(double));

        for (j = 0; j < nsample; j++) {
            time_array[j] = DoTime(i, mflop, cache_size);
        }

        tim = GetGoodTime(nsample, time_array);
        mf = (2.0*i) / (tim*1000000.0);
        fprintf(stdout, "   N=%8d, time=%e, MFLOPS=%.2f\n", i, tim, mf);
       
        //Release the memory
        free(time_array);
    }
    fprintf(stdout, "DONE\n");
    return(0);
}
