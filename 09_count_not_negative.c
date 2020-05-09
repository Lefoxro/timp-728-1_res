#include <stdio.h>
#include <math.h>

int main ()
{
int n, x, k, i;
k = 0;
(void) scanf ("%d\n", &n);
for (i = 1; i<= n; i++)
{
    (void) scanf ("\n");
    (void) scanf ("%d", &x);
    if (x >= 0)
    {k = k+1; }
}
printf ("%d\n", k);
return 0;
}
