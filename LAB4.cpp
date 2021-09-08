#include<stdio.h>
#include<math.h>
int main()
{
    float a,b,c,Area,sum;
    scanf("%f %f %f",&a,&b,&c);

    if(a+b>c&&a+c>b&&b+c>a)
    {
        sum=(a+b+c)/float(2);
        Area= sqrt(sum*(sum-a)*(sum-b)*(sum-c));
    }
    else
    {
        Area=0;
    }
    printf("%.2f",Area);
} 
