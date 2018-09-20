long long GetCycleCount(void);
double ClickToSec(long long clicks);

double GetMflop(int mflop, double *dum) {
    const int nsize = 168;
    const int lflops = 2*nsize;  /* flops performed in your loop */
    long long t0, t1;
    int nrep;
    register int i;
    nrep = (mflop * 1000000 + lflops-1)/lflops;
    double X[nsize], Y[nsize];
    double *Xj, *Yj;
    const int alpha = 0.5;
    if (nrep<1) nrep=1;
    register double res = 0.0;

    register double x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13;
    register double y0, y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13;
    /* x0  = 1.0;
       x1  = 2.0;
       x2  = 3.2;
       x3  = 0.02;
       x4  = 1.7;
       x5  = 0.97;
       x6  = 2.3;
       x7  = 1.07;
       x8  = 1.3;
       x9  = 2.4;
       x10 = 1.1;
       x11 = 1.2;
       x12 = 0.4;
       x13 = 1.3; */

    res = 0.0;
    t0 = GetCycleCount();
    register double s1, s2, s3, s4, s5, s6, s7;
    register double r1, r2, r3, r4;

    for (i=nrep; i; i--) {

        register int j = 0;
        register int c = 0;
        x0  = 1.32*1.12;
        x1  = 0.34*0.93;
        x2  = 3.53*1.13;
        x3  = 4.3*0.22;
        x4  = 1.17*1.23;
        x5  = 0.03*0.323;
        x6  = 0.003*1.9;
        x7  = 3.2*0.032;
        x8  = 2.5*1.323;
        x9  = 1.121*3.43;
        x10 = 0.717*1.34645;
        x11 = 22.23*1.9299;
        x12 = 1.9*0.0943;
        x13 = 1.9*1.29302;

        do {
            y0 += x0;
            x0 = 0.32*0.55;

            y1 += x1;
            x1 = 0.2*1.55;

            y2 += x2;
            x2 = 1.21*2.54;

            y3 += x3;
            x3 = 2.3*3.3;

            y4 += x4;
            x4 = 0.13*0.43;

            y5 += x5;
            x5 = 0.365*0.455;

            y6 += x6;
            x6 = 0.53*0.555;

            y7 += x7;
            x7 = 0.453*0.56;

            y8 += x8;
            x8 = 1.33*1.64;

            y9 += x9;
            x9 = 0.312*0.65;

            y10 += x10;
            x10 = 2.233*1.2;

            y11 += x11;
            x11 = 0.376*0.65;

            y12 += x12;
            x12 = 2.323*2.565;

            y13 += x13;
            x13 = 0.33*0.115;
            j += 14;

            c++;
            /* printf("res: %e, c: %d, y0: %e\n", x0,  c, y0);
               printf("res: %e, c: %d, y1: %e\n", x1,  c, y1);
               printf("res: %e, c: %d, y2: %e\n", x2,  c, y2);
               printf("res: %e, c: %d, y3: %e\n", x3,  c, y3);
               printf("res: %e, c: %d, y4: %e\n", x4,  c, y4);
               printf("res: %e, c: %d, y5: %e\n", x5,  c, y5);
               printf("res: %e, c: %d, y6: %e\n", x6,  c, y6);
               printf("res: %e, c: %d, y7: %e\n", x7,  c, y7);
               printf("res: %e, c: %d, y8: %e\n", x8,  c, y8);
               printf("res: %e, c: %d, y9: %e\n", x9,  c, y9);
               printf("res: %e, c: %d, y10: %e\n", x10, c, y10);
               printf("res: %e, c: %d, y11: %e\n", x11, c, y11);
               printf("res: %e, c: %d, y12: %e\n", x12, c, y12);
               printf("res: %e, c: %d, y13: %e\n", x13, c, y13);
               printf("\n");*/
            /* if (c == 5) {
               exit(1);    
               } */
        } while (j!=(nsize-(14*2)));



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
        /* printf("x0: %e, c: %d, y0: %e\n", x0,  c, y0);
        printf("x1: %e, c: %d, y1: %e\n", x1,  c, y1);
        printf("x2: %e, c: %d, y2: %e\n", x2,  c, y2);
        printf("x3: %e, c: %d, y3: %e\n", x3,  c, y3);
        printf("x4: %e, c: %d, y4: %e\n", x4,  c, y4);
        printf("x5: %e, c: %d, y5: %e\n", x5,  c, y5);
        printf("x6: %e, c: %d, y6: %e\n", x6,  c, y6);
        printf("x7: %e, c: %d, y7: %e\n", x7,  c, y7);
        printf("x8: %e, c: %d, y8: %e\n", x8,  c, y8);
        printf("x9: %e, c: %d, y9: %e\n", x9,  c, y9);
        printf("x10: %e, c: %d, y10: %e\n", x10, c, y10);
        printf("x11: %e, c: %d, y11: %e\n", x11, c, y11);
        printf("x12: %e, c: %d, y12: %e\n", x12, c, y12);
        printf("x13: %e, c: %d, y13: %e\n", x13, c, y13);
        printf("\n");
        */
        
        s1 = y0 + y1;
        s2 = y2 + y3;
        s3 = y4 + y5;
        s4 = y6 + y7;
        s5 = y8 + y9;
        s6 = y10 + y11;
        s7 = y12 + y13;

        r1 = s1 + s6;
        r2 = s2 + s5;
        r3 = s3 + s4;
        
        r4 = r1 + r2;
        r1 = r3 + s7;
        
        r1 += r4;
        res += r1;
        /* res += s1+s2; */
        /* res += y0 + y1 + y2 + y3 + 
            y4 + y5 + y6 + y7 + 
            y8 + y9 + y10 + y11 + 
            y12+ y13; */
            
            
        y0  *= 0.0; 
        y1  *= 0.0; 
        y2  *= 0.0; 
        y3  *= 0.0; 
        y4  *= 0.0; 
        y5  *= 0.0; 
        y6  *= 0.0; 
        y7  *= 0.0; 
        y8  *= 0.0; 
        y9  *= 0.0; 
        y10 *= 0.0; 
        y11 *= 0.0; 
        y12 *= 0.0; 
        y13 *= 0.0; 
        /* printf("res: %e\n", res);
        if (i == nrep-100) {
            exit(1);    
        } */

        /*   
             res +=  y0;
             printf("res: %e\n", res);

             res +=  y1;
             printf("res: %e\n", res);

             res +=  y2;
             printf("res: %e\n", res);

             res +=  y3;
             printf("res: %e\n", res);

             res +=  y4;
             printf("res: %e\n", res);

             res +=  y5;
             printf("res: %e\n", res);

             res +=  y6;
             printf("res: %e\n", res);

             res +=  y7;
             printf("res: %e\n", res);

             res +=  y8;
             printf("res: %e\n", res);

             res +=  y9;
             printf("res: %e\n", res);

             res +=  y10;
             printf("res: %e\n", res);

             res +=  y11;
             printf("res: %e\n", res);

             res +=  y12;
             printf("res: %e\n", res);

             res +=  y13;
             printf("res: %e\n", res);
         */

    }

    printf("res: %e\n", res); 
    t1 = GetCycleCount();
    printf("t1: %lld\n", t1);

    return(nrep*1.0e-6*lflops/ClickToSec(t1-t0));
}
