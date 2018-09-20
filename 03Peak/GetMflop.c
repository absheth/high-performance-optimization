long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, double *dum) {
    const int nsize = 80; 
    const int lflops = 2*nsize + (8*2);  /* flops performed in your loop */
    long long t0, t1;
    int nrep;
    register int i;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    /* double X[nsize], Y[nsize]; */
    double *Xj, *Yj;
    if (nrep<1) nrep=1;
    register double res = 0.0;

    register double x0, x1, x2, x3, x4, x5, x6, x7;
    register double y0, y1, y2, y3, y4, y5, y6, y7;
    register double s1=0.0, s2=0.0, s3=0.0, s4=0.0;
    register double r1=0.0, r2=0.0;
    register int j=0;
    register int f=0; 
    int c=nsize-8;
    printf("c: %d\n", c); 
    t0 = GetCycleCount();
    for (i=nrep; i; i--) {

        j = 0;
        f = 0; 
        x0  = 1.32*1.12;
        x1  = 0.34*0.93;
        x2  = 3.53*1.13;
        x3  = 4.38*0.22;
        x4  = 5.24*2.39;
        x5  = 0.01*9.56;
        x6  = 4.8*0.34;
        x7  = 0.18*0.22;
        j+=8;
        f++;
        do {
            y0 += x0; x0 = 0.32*0.55;
            y1 += x1; x1 = 0.22*1.55;
            y2 += x2; x2 = 1.21*2.54;
            y3 += x3; x3 = 2.63*3.37;
            y4 += x4; x4 = 1.43*2.36;
            y5 += x5; x5 = 0.19*0.67;
            y6 += x6; x6 = 7.52*4.8;
            y7 += x7; x7 = 1.92*2.98;
            
            j += 8;
            f++;
            /* printf("x0: %e, f: %d, y0: %e\n", x0,  f, y0);
            printf("x1: %e, f: %d, y1: %e\n", x1,  f, y1);
            printf("x2: %e, f: %d, y2: %e\n", x2,  f, y2);
            printf("x3: %e, f: %d, y3: %e\n", x3,  f, y3);
            printf("x4: %e, f: %d, y4: %e\n", x4,  f, y4);
            printf("x5: %e, f: %d, y5: %e\n", x5,  f, y5);
            printf("x6: %e, f: %d, y6: %e\n", x6,  f, y6);
            printf("x7: %e, f: %d, y7: %e\n", x7,  f, y7);
            */
            /* printf("\n");
            if (f == 4) {
                exit(1);    
            }*/


        } while (j!=c);
        
        
        y0 += x0;
        y1 += x1;
        y2 += x2;
        y3 += x3;
        y4 += x4;
        y5 += x5;
        y6 += x6;
        y7 += x7;
        
        j += 8; 
        f++;
        /*printf("x0: %e, f: %d, y0: %e\n", x0,  f, y0);
        printf("x1: %e, f: %d, y1: %e\n", x1,  f, y1);
        printf("x2: %e, f: %d, y2: %e\n", x2,  f, y2);
        printf("x3: %e, f: %d, y3: %e\n", x3,  f, y3);
        printf("x4: %e, f: %d, y4: %e\n", x4,  f, y4);
        printf("x5: %e, f: %d, y5: %e\n", x5,  f, y5);
        printf("x6: %e, f: %d, y6: %e\n", x6,  f, y6);
        printf("x7: %e, f: %d, y7: %e\n", x7,  f, y7);
        printf("\n");
        */
        s1 = y0 + y1;
        s2 = y2 + y3;
        s3 = y4 + y5;
        s4 = y6 + y7;
        
        y0  *= 0.0; 
        y1  *= 0.0; 
        y2  *= 0.0; 
        y3  *= 0.0; 
        y4  *= 0.0; 
        y5  *= 0.0; 
        y6  *= 0.0; 
        y7  *= 0.0; 
        
        r1 = s1 + s2;
        r2 = s3 + s4;
        
        r1 += r2;
        
        res += r1;
        
        /* printf("res: %e\n", res); 
        if (i == nrep-100) {
            exit(1);    
        }*/

        
    }
    
    printf("f: %d\n", f);

    printf("res: %e\n", res); 
    t1 = GetCycleCount();
    printf("t1: %lld\n", t1);

    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
