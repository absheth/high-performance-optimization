long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, double *dum) {
    const int lflops = 2*16;  /* flops performed in your loop */
    long long t0, t1; 
    int nrep, i, j;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    double *X, *Y;
    if (nrep<1) nrep=1;
    
    /*
    TODO
    1) Check loop skewing, loop unrolling
    2) Workout the math.
    3) Read about all the assembly instructions
    */
    
    /* Allocate memory and populate the vectors*/
    X = (double *) malloc(16 * sizeof(double));
    Y = (double *) malloc(16 * sizeof(double));
    for (i = 0; i < 16; ++i) {
        X[i] = 1.0*i;
        Y[i] = 2.0*i;
    }
    t0 = GetCycleCount();
    for (i=nrep; i; i--) {
        for (j = 0; j < 16; ++j) {
            dum[j] = X[j] + Y[j];
        }
    }
    t1 = GetCycleCount();



    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
