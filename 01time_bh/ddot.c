/*
 * Performs double precision dot product on N-length vectors X & Y.
 * RETURNS: ddot = X[i]*Y[i], i=0,N.
 */
double ddot(int N, double *X, double *Y)
{
    int i;
    double dot=0.0;
    for (i=0; i < N; i++)
       dot += X[i] * Y[i];
    return(dot);
}
