double dodiv(double *x)
{
   double sum=0.0;
   int i;
   for (i=1; i < 10; i++)
      sum+= x[i];
   return(sum);
}
