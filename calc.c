/******************************************************************************
 * @file    simplecalc.c
 * @brief   Simple calculator program
 * @version 1.0
 * @date    June 2024
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

/* Function Prototypes */
void print_usage(void);
int32_t rotate_left(int32_t value, int32_t count);
int32_t rotate_right(int32_t value, int32_t count);
int32_t perform_addition(int32_t operand1, int32_t operand2);
int32_t perform_subtraction(int32_t operand1, int32_t operand2);
int32_t perform_multiplication(int32_t operand1, int32_t operand2);
double perform_division(int32_t operand1, int32_t operand2);
int32_t perform_modulo(int32_t operand1, int32_t operand2);
int32_t perform_left_shift(int32_t operand1, int32_t operand2);
int32_t perform_right_shift(int32_t operand1, int32_t operand2);
int32_t perform_and(int32_t operand1, int32_t operand2);
int32_t perform_or(int32_t operand1, int32_t operand2);
int32_t perform_xor(int32_t operand1, int32_t operand2);
int32_t perform_rotate_left(int32_t operand1, int32_t operand2);
int32_t perform_rotate_right(int32_t operand1, int32_t operand2);
int32_t perform_calculation(int32_t operand1, const char *operator, int32_t operand2);
int validate_operands(int32_t operand1, int32_t operand2, const char *operator);
void handle_error(const char *message);

/******************************************************************************
 * @brief    Print the usage of the program
 ******************************************************************************/
void print_usage(void)
{
    printf("Usage: ./simplecalc operand1 operator operand2\n");
    printf("Supported Operators:\n");
    printf("(+) addition\n");
    printf("(-) subtraction\n");
    printf("(*) multiplication\n");
    printf("(/) divide\n");
    printf("(%%) modulo\n");
    printf("(<<) left shift\n");
    printf("(>>) right shift\n");
    printf("(&) and\n");
    printf("(|) or\n");
    printf("(^) xor\n");
    printf("(<<<) rotate left\n");
    printf("(>>>) rotate right\n");
}

/******************************************************************************
 * @brief    Rotate bits to the left
 * @param    value   The value to be rotated
 * @param    count   The number of positions to rotate
 * @return   Rotated value
 ******************************************************************************/
int32_t rotate_left(int32_t value, int32_t count)
{
    int mask = (sizeof(value) * 8) - 1;
    count &= mask;
    return (value << count) | (value >> (-count & mask));
}

/******************************************************************************
 * @brief    Rotate bits to the right
 * @param    value   The value to be rotated
 * @param    count   The number of positions to rotate
 * @return   Rotated value
 ******************************************************************************/
int32_t rotate_right(int32_t value, int32_t count)
{
    int mask = (sizeof(value) * 8) - 1;
    count &= mask;
    return (value >> count) | (value << (-count & mask));
}

/******************************************************************************
 * @brief    Perform addition
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of addition
 ******************************************************************************/
int32_t perform_addition(int32_t operand1, int32_t operand2)
{
    return operand1 + operand2;
}

/******************************************************************************
 * @brief    Perform subtraction
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of subtraction
 ******************************************************************************/
int32_t perform_subtraction(int32_t operand1, int32_t operand2)
{
    return operand1 - operand2;
}

/******************************************************************************
 * @brief    Perform multiplication
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of multiplication
 ******************************************************************************/
int32_t perform_multiplication(int32_t operand1, int32_t operand2)
{
    return operand1 * operand2;
}

/******************************************************************************
 * @brief    Perform division
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of division
 ******************************************************************************/
double perform_division(int32_t operand1, int32_t operand2)
{
    if (operand2 == 0)
    {
        handle_error("Error! Division by zero.\n");
        exit(EXIT_FAILURE);
    }
    return (double)operand1 / operand2;
}

/******************************************************************************
 * @brief    Perform modulo operation
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of modulo operation
 ******************************************************************************/
int32_t perform_modulo(int32_t operand1, int32_t operand2)
{
    if (operand2 == 0)
    {
        handle_error("Error! Division by zero.\n");
        exit(EXIT_FAILURE);
    }
    return operand1 % operand2;
}

/******************************************************************************
 * @brief    Perform left shift
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of left shift
 ******************************************************************************/
int32_t perform_left_shift(int32_t operand1, int32_t operand2)
{
    return operand1 << operand2;
}

/******************************************************************************
 * @brief    Perform right shift
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of right shift
 ******************************************************************************/
int32_t perform_right_shift(int32_t operand1, int32_t operand2)
{
    return operand1 >> operand2;
}

/******************************************************************************
 * @brief    Perform bitwise AND
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of AND operation
 ******************************************************************************/
int32_t perform_and(int32_t operand1, int32_t operand2)
{
    return operand1 & operand2;
}

/******************************************************************************
 * @brief    Perform bitwise OR
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of OR operation
 ******************************************************************************/
int32_t perform_or(int32_t operand1, int32_t operand2)
{
    return operand1 | operand2;
}

/******************************************************************************
 * @brief    Perform bitwise XOR
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of XOR operation
 ******************************************************************************/
int32_t perform_xor(int32_t operand1, int32_t operand2)
{
    return operand1 ^ operand2;
}

/******************************************************************************
 * @brief    Perform rotate left
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of rotate left
 ******************************************************************************/
int32_t perform_rotate_left(int32_t operand1, int32_t operand2)
{
    return rotate_left(operand1, operand2);
}

/******************************************************************************
 * @brief    Perform rotate right
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of rotate right
 ******************************************************************************/
int32_t perform_rotate_right(int32_t operand1, int32_t operand2)
{
    return rotate_right(operand1, operand2);
}

/******************************************************************************
 * @brief    Perform calculation based on operator
 * @param    operand1    First operand
 * @param    operator    Operator as string
 * @param    operand2    Second operand
 * @return   Result of calculation
 ******************************************************************************/
int32_t perform_calculation(int32_t operand1, const char *operator, int32_t operand2)
{
    if (strcmp(operator, "+") == 0)
    {
        return perform_addition(operand1, operand2);
    }
    else if (strcmp(operator, "-") == 0)
    {
        return perform_subtraction(operand1, operand2);
    }
    else if (strcmp(operator, "*") == 0)
    {
        return perform_multiplication(operand1, operand2);
    }
    else if (strcmp(operator, "/") == 0)
    {
        return (int32_t)perform_division(operand1, operand2);
    }
    else if (strcmp(operator, "%") == 0)
    {
        return perform_modulo(operand1, operand2);
    }
    else if (strcmp(operator, "<<") == 0)
    {
        return perform_left_shift(operand1, operand2);
    }
    else if (strcmp(operator, ">>") == 0)
    {
        return perform_right_shift(operand1, operand2);
    }
    else if (strcmp(operator, "&") == 0)
    {
        return perform_and(operand1, operand2);
    }
    else if (strcmp(operator, "|") == 0)
    {
        return perform_or(operand1, operand2);
    }
    else if (strcmp(operator, "^") == 0)
    {
        return perform_xor(operand1, operand2);
    }
    else if (strcmp(operator, "<<<") == 0)
    {
        return perform_rotate_left(operand1, operand2);
    }
    else if (strcmp(operator, ">>>") == 0)
    {
        return perform_rotate_right(operand1, operand2);
    }
    else
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
}

/******************************************************************************
 * @brief    Validate operands for bitwise operations
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @param    operator    Operator as string
 * @return   1 if valid, 0 if invalid
 ******************************************************************************/
int validate_operands(int32_t operand1, int32_t operand2, const char *operator)
{
    if ((strcmp(operator, "<<") == 0 || strcmp(operator, ">>") == 0 ||
         strcmp(operator, "&") == 0 || strcmp(operator, "|") == 0 ||
         strcmp(operator, "^") == 0 || strcmp(operator, "<<<") == 0 ||
         strcmp(operator, ">>>") == 0) &&
        (operand1 < 0 || operand2 < 0))
    {
        handle_error("Negative numbers not accepted for bit related equations.\n");
        return 0;
    }
    return 1;
}

/******************************************************************************
 * @brief    Handle error by printing a message
 * @param    message    Error message to print
 ******************************************************************************/
void handle_error(const char *message)
{
    fprintf(stderr, "%s", message);
}

/******************************************************************************
 * @brief    Main function
 * @param    argc    Argument count
 * @param    argv    Argument vector
 * @return   Exit status
 ******************************************************************************/
int main(int argc, char *argv[])
{
    int32_t result;

    if (argc != 4)
    {
        print_usage();
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr;
    int32_t operand1 = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0')
    {
        handle_error("Invalid operand1\n");
        return EXIT_FAILURE;
    }

    const char *operator = argv[2];

    errno = 0;
    int32_t operand2 = strtol(argv[3], &endptr, 10);
    if (errno != 0 || *endptr != '\0')
    {
        handle_error("Invalid operand2\n");
        return EXIT_FAILURE;
    }

    if (!validate_operands(operand1, operand2, operator))
    {
        return EXIT_FAILURE;
    }

    result = perform_calculation(operand1, operator, operand2);

    printf("%d %s %d = %d\n", operand1, operator, operand2, result);

    return EXIT_SUCCESS;
}
