#include <stdio.h>
#include <math.h>

int main ()
{
int n, x, k, i;
k = 1;
(void) scanf ("%d\n", &n);
for (i = 1; i<= n; i++)
{
    (void) scanf ("\n");
    (void) scanf ("%d", &x);
    k = k * x;
}
printf ("%d\n", k);
return 0;
}
