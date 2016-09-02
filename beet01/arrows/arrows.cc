#include <bits/stdc++.h>

#define r(x) (x / 180.0 * acos(-1))

int main()
{
    double n, k;
    scanf("%lf %lf", &n, &k);
    printf("%.8f\n", n*sin(r(180/n))*cos(r(180*k/n))/cos(r(180*(k-1)/n)));
    return 0;
}
