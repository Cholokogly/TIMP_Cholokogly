#include <stdio.h>
#include <math.h>

int main() {
    double x = 0.0;
    double y = 0.0;

    int args = scanf("%lf %lf", &x, &y);

    if (args != 2) {
        return 0;
    }

    double result = pow(x, y);
    printf("%lf" , result);

    return 0;
}
