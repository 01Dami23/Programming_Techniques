#include <stdio.h>

int main()
{
    int num1, num2, max, min, remainder;

    printf("Enter two (non-zero) positive integer numbers:\n");
    scanf("%d%d", &num1, &num2);

    if (num1 <= 0 || num2 <= 0) {
        printf("Error: invalid numbers");
        return 1;
    }

    if (num1 >= num2) {
        max = num1;
        min = num2;
    } else {
        max = num2;
        min = num1;
    }

    do {
        remainder = max % min;
        max = min;
        min = remainder;
    } while (remainder != 0);

    printf("MCD = %d", max);

    return 0;
}