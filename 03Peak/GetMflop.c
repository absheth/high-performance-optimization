long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, double *dum) {
    const int lflops = 1000000;  /* flops performed in your loop */
    long long t0, t1; 
    int nrep, i;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    
    printf("\nnrep = %d \n", nrep);

    if (nrep<1) nrep=1;

    t0 = GetCycleCount();
    for (i=nrep; i>0; i--)
    {   
    }
    t1 = GetCycleCount();






    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
