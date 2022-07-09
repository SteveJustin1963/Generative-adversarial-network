#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 1000000

int main()
{
    int x, y, z, i;
    float alpha = 0.01;
    
    printf("Enter the value of z: ");
    scanf("%d", &z);
    
    x = y = 1;
    
    for(i=0; i<MAX_ITER; i++)
    {
        x = x - alpha*(2*x + 5*y - z);
        y = y - alpha*(4*x + 3*y - z);
    }
    
    printf("The value of x and y are %d and %d respectively.", x, y);
    
    return 0;
}
