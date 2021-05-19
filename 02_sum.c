#include <stdio.h>

int main() {
    double first = 0.0;
    double second = 0.0;

    int args = scanf("%lf %lf", &first, &second);

    if (args != 2) {
        return 0;
    }

    double result = first + second;
    printf("%lf" , result);

    return 0;
}
