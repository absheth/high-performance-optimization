long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, register double *dum) {
    int nsize = 100; 
    const int lflops = 2*nsize;  /* flops performed in your loop */
    long long t0, t1; 
    int nrep, i;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    double *X, *Y;
    register int alpha = 0.5;
    if (nrep<1) nrep=1;

    /*
       TODO
       1) Check loop skewing, loop unrolling
       2) Workout the math.
       3) Read about all the assembly instructions

        NOTE: 14 stage pipeline
     */

    /* Allocate memory and populate the vectors*/
    X = (double *) malloc(nsize * sizeof(double));
    Y = (double *) malloc(nsize * sizeof(double));


    for (i = 0; i < nsize; ++i) { /* Think why 16*/
        X[i] = 1.0*i;
        Y[i] = 2.0*i;
    }

    t0 = GetCycleCount();
    for (i=nrep; i; i--) {
        /*Optimizations*/
        register int j; // DECIDE

        /* Calculate N14 */

        double x0, x1, x2, x3, x4, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13;
        x0  = alpha * *X;
        x1  = alpha * X[1];
        x2  = alpha * X[2];
        x3  = alpha * X[3];
        x4  = alpha * X[4];
        x5  = alpha * X[5];
        x6  = alpha * X[6];
        x7  = alpha * X[7];
        x8  = alpha * X[8];
        x9  = alpha * X[9];
        x10 = alpha * X[10];
        x11 = alpha * X[11];
        x12 = alpha * X[12];
        x13 = alpha * X[12];

        do {
            *Y += x0;
            x0 = alpha * *X;

            Y[1] += x1;
            x1 += alpha * X[1];

            Y[2] += x2;
            x1 += alpha * X[1];
            Y[3] += x3;
            x1 += alpha * X[1];
            Y[4] += x4;
            x1 += alpha * X[1];
            Y[5] += x5;
            x1 += alpha * X[1];
            Y[6] += x6;
            x1 += alpha * X[1];
            Y[7] += x7;
            x1 += alpha * X[1];
            Y[8] += x8;
            x1 += alpha * X[1];
            Y[9] += x9;
            x1 += alpha * X[1];
            Y[10] += x10;
            x1 += alpha * X[1];
            Y[11] += x11;
            x1 += alpha * X[1];
            Y[12] += x12;
            x1 += alpha * X[1];
            Y[13] += x13;
            x1 += alpha * X[1];


            *Y = alpha * *X;
            Y[3] += alpha * X[3];
            Y[4] += alpha * X[4];
            Y[5] += alpha * X[5];
            Y[6] += alpha * X[6];
            Y[7] += alpha * X[7];
            Y[8] += alpha * X[8];
            Y[9] += alpha * X[9];
            Y[10] += alpha * X[10];
            Y[11] += alpha * X[11];
            Y[12] += alpha * X[12];
            Y[13] += alpha * X[13];

            X += 14;
            Y += 14
        } while (X != stX);

    }
    t1 = GetCycleCount();



    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
