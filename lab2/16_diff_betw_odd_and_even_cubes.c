#include <stdio.h>
#include <math.h>

int main()
{
    int n;

    int args = scanf("%d", &n);

    if (args != 1) {
        return 1;
    }

    if (n < 1) {
        return 1;
    }

    double sum = 0;
    double first;
    double second;

    int x;
    int i;

    for (i = 0; i < n; ++i) {
        args = scanf("%d", &x);

        if (args != 1) {
            return 1;
        }

        first = pow((double)-1, (double)(i + 2));
        second = pow((double)x, (double)3);

        sum += (first * second);
    }

    printf("%lf", sum);

    return 0;
}