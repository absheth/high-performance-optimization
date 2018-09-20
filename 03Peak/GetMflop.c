long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, double *dum) {
    const int nsize = 1400; 
    const int lflops = 2*nsize;  /* flops performed in your loop */
    long long t0, t1; 
    int nrep;
    register int i;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    double X[nsize], Y[nsize];
    double *Xj, *Yj; 
    const int alpha = 0.5;
    if (nrep<1) nrep=1;

    /*
       TODO
       2) Workout the math.
        NOTE: 14 stage pipeline
     */

    /* Allocate memory and populate the vectors*/
    /*X = (double *) malloc(nsize * sizeof(double));
    Y = (double *) malloc(nsize * sizeof(double));*/

    /*for (i = 0; i < nsize; ++i) {
        X[i] = 1.0*i;
        Y[i] = 2.0*i;
    }*/
    double x0 =1.0, x1=2.0, x2=3.2, x3=0.02, x4=1.7, x5=0.97, x6=2.3, x7=1.07, x8=1.3, x9=2.4, x10=1.1, x11=1.2, x12=0.4, x13=1.3;
    double y0, y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13;
    int j = 0;
    t0 = GetCycleCount();

    for (i=nrep; i; i--) {
         
        
        x0  *= 0.2122;
        x1  *= 0.493;
        x2  *= 32.11;
        x3  *= 0.22; 
        x4  *= 0.333; 
        x5  *= 0.323; 
        x6  *= 0.998989; 
        x7  *= 0.0302302; 
        x8  *= 656.3232; 
        x9  *= 34.43; 
        x10 *= 0.34645; 
        x11 *= 0.9922999; 
        x12 *= 1.0000943; 
        x13 *= 12.29302; 
        
        do {
            y0 += x0; 
            x0 = 0.3232*0.5523;
            
            y1 += x1;
            x1 = 0.2*2.55;
            
            y2 += x2;
            x2 = 0.213*0.5455;
            
            y3 += x3;
            x3 = 2.3*0.34355;
            
            y4 += x4;
            x4 = 0.343*0.43455;
            
            y5 += x5;
            x5 = 0.36565*0.4355;
            
            y6 += x6;
            x6 = 0.43433*0.5235;
            
            y6 += x6;
            x6 = 0.543*0.5455;
            
            y7 += x7;
            x7 = 0.453*0.5655;
            
            y8 += x8;
            x8 = 0.3333*0.55643;
            
            y9 += x9;
            x0 = 0.3333*0.5665;
            
            y10 += x10; 
            x0 = 0.3233*0.65655;
            
            y11 += x11;
            x11 = 0.37756*0.565;
            
            y12 += x12;
            x12 = 0.322323*0.56565;
            
            y13 += x13;
            x13 = 0.343434*0.511115;
            j += 14;
        } while (j!=nsize); 
        
        y0 += x0;
        y1 += x1;
        y2 += x2;
        y3 += x3;
        y4 += x4;
        y5 += x5;
        y6 += x6;
        y7 += x7;
        y8 += x8;
        y9 += x9;
        y10 += x10;
        y11 += x11;
        y12 += x12;
        y13 += x13;
        /* 
        Xj = X;
        Yj = Y;
         
        double *stX = Xj + nsize;
        register double x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13;
        x0  = alpha * *X;
        x1  = alpha * Xj[1];
        x2  = alpha * Xj[2];
        x3  = alpha * Xj[3];
        x4  = alpha * Xj[4];
        x5  = alpha * Xj[5];
        x6  = alpha * Xj[6];
        x7  = alpha * Xj[7];
        x8  = alpha * Xj[8];
        x9  = alpha * Xj[9];
        x10 = alpha * Xj[10];
        x11 = alpha * Xj[11];
        x12 = alpha * Xj[12];
        x13 = alpha * Xj[13];
        Xj += 14;

        do {
            *Yj += x0;
            x0 = alpha * *Xj;
            Yj[1] += x1;
            x1 = alpha * Xj[1];
            Yj[2] += x2;
            x2 = alpha * Xj[2];
            Yj[3] += x3;
            x3 = alpha * Xj[3];
            Yj[4] += x4;
            x4 = alpha * Xj[4];
            Yj[5] += x5;
            x5 = alpha * Xj[5];
            Yj[6] += x6;
            x6 = alpha * Xj[6];
            Yj[7] += x7;
            x7 = alpha * Xj[7];
            Yj[8] += x8;
            x8 = alpha * Xj[8];
            Yj[9] += x9;
            x9 = alpha * Xj[9];
            Yj[10] += x10;
            x10 = alpha * Xj[10];
            Yj[11] += x11;
            x11 = alpha * Xj[11];
            Yj[12] += x12;
            x12 = alpha * Xj[12];
            Yj[13] += x13;
            x3 = alpha * Xj[13];
            Xj += 14;
            Yj += 14;
        } while (Xj != stX);
        
        *Yj += x0;
        Yj[1] += x1;
        Yj[2] += x2;
        Yj[3] += x3;
        Yj[4] += x4;
        Yj[5] += x5;
        Yj[6] += x6;
        Yj[7] += x7;
        Yj[8] += x8;
        Yj[9] += x9;
        Yj[10] += x10;
        Yj[11] += x11;
        Yj[12] += x12;
        Yj[13] += x13;
        */ 
        /*do{
        
        } while (); */
    }
    t1 = GetCycleCount();

    printf("t0: %lld\n", t0);
    printf("t1: %lld\n", t1);

    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
