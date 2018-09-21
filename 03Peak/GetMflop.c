/*
   Peak mflop = 2751.28 (91.53 percent of peak)
 */

long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, double *dum) {
    const int nsize = 80;
    const int lflops = 2*nsize+(8+8); /* flops performed in your loop ==> 176 (Calculcation mentioned below) */
    long long t0, t1;
    int nrep;
    int i;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    if (nrep<1) nrep=1;
    register double res = 0.0;
    register double x0, x1, x2, x3, x4, x5, x6, x7;
    register double y0, y1, y2, y3, y4, y5, y6, y7;
    register double s1=0.0, s2=0.0, s3=0.0, s4=0.0;
    register double r1=0.0, r2=0.0;
    int j=0;
    /* register int f=0;*/  /* Just for verifying iterations */
    int c=nsize-8;
    t0 = GetCycleCount();
    for (i=nrep; i; i--) {

        j=0;
        /* f=0; */ 

        /* 8 flop */
        x0=1.3*1.1;
        x1=0.3*0.9;
        x2=3.5*1.1;
        x3=4.3*0.2;
        x4=5.2*2.3;
        x5=0.0*9.5;
        x6=4.8*0.3;
        x7=0.1*0.2;

        /* f++; */

        /*
           This loop executes 9 times.
           9*16 = 144 flop */
        do {
            y0+=x0; x0=0.3*0.5;
            y1+=x1; x1=0.2*1.5;
            y2+=x2; x2=1.2*2.5;
            y3+=x3; x3=2.6*3.3;
            y4+=x4; x4=1.4*2.3;
            y5+=x5; x5=0.1*0.6;
            y6+=x6; x6=7.5*4.8;
            y7+=x7; x7=1.9*2.9;

            j+=8;
            /* f++; */

        } while (j!=c);

        /* 8 flop  */
        y0+=x0;
        y1+=x1;
        y2+=x2;
        y3+=x3;
        y4+=x4;
        y5+=x5;
        y6+=x6;
        y7+=x7;

        /*Increment j to verify flops */
        j+=8;
        /* f++; */

        /* 16 flop  */
        s1=y0+y1;
        y0*=0.0;
        y1*=0.0;
        
        s2=y2+y3;
        y2*=0.0;
        y3*=0.0;
        
        s3=y4+y5;
        y4*=0.0;
        y5*=0.0;
        
        s4=y6+y7;
        y6*=0.0;
        y7*=0.0;

        r1=s1+s2;
        r2=s3+s4;
        r2+=r1;

        res+=r2;

    }

    /* printf("f: %d\n", f);
       printf("j: %d\n", j); */
    printf("res: %e\n", res);
    t1 = GetCycleCount();

    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
