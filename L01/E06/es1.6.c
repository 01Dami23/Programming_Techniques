#include <stdio.h>

int main()
{
    char operator;
    float op1, op2, result;
    int line_counter;

    FILE *fp_read, *fp_write;

    if ((fp_read = fopen("../Operations.txt", "r")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    if ((fp_write = fopen("../Results.txt", "w")) == NULL) {
        printf("Error opening file\n");
        return 2;
    }


    while (fscanf(fp_read, "%c %f %f\n", &operator, &op1, &op2) == 3) {

        ++line_counter;

        if (operator == '+') {
            result = op1 + op2;
            fprintf(fp_write,"%c %.2f\n", operator, result);
        }
        else if (operator == '-') {
            result = op1 - op2;
            fprintf(fp_write,"%c %.2f\n", operator, result);
        }
        else if (operator == '*') {
            result = op1 * op2;
            fprintf(fp_write,"%c %.2f\n", operator, result);
        }
        else if (operator == '/') {

            if (op2 == 0.0) {
                fprintf(fp_write, "Invalid division by zero in line %d\n", line_counter);
            } else {
                result = op1 / op2;
                fprintf(fp_write, "%c %.2f\n", operator, result);
            }
        }
    }

    fclose(fp_read);
    fclose(fp_write);

    return 0;
}

