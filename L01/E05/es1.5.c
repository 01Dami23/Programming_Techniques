#include <stdio.h>

int main()
{
    char operator;
    float op1, op2, result;

    printf("Enter the operator ('+', '-', '*' or '/'):\n");
    operator = getchar();

    if (operator != '+' && operator != '-' && operator != '*' && operator != '/') {
        printf("Invalid operator inserted\n");
        return 1;
    }

    printf("Enter the 2 operands separated by one space (e.g. 21.0 2.0):\n");
    scanf("%f%f", &op1, &op2);


    if (operator == '+') {
        result = op1 + op2;
        printf("%c %.2f\n", operator, result);
    }
    else if (operator == '-') {
        result = op1 - op2;
        printf("%c %.2f\n", operator, result);
    }
    else if (operator == '*') {
        result = op1 * op2;
        printf("%c %.2f\n", operator, result);
    }
    else if (operator == '/') {

        if (op2 == 0.0) {
            printf("Invalid division by zero\n");
            return 2;
        }
        else {
            result = op1 / op2;
            printf("%c %.2f\n", operator, result);
        }

    }
    return 0;
}