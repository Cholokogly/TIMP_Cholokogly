#include <stdio.h>

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

    int counter = 0;

    int x;
    int i;

    for (i = 0; i < n; ++i) {
        args = scanf("%d", &x);

        if (args != 1) {
            return 1;
        }

        if (x > 0) {
            ++counter;
        }
    }

    printf("%d", counter);

    return 0;
}