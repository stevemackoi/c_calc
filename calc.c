/******************************************************************************
 * @file    simplecalc.c
 * @brief   Simple calculator program
 * @version 1.4
 * @date    July 2024
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

// Function Prototypes
void print_usage(void);
uint32_t rotate_left(uint32_t value, uint32_t count);
uint32_t rotate_right(uint32_t value, uint32_t count);
int32_t perform_addition(int32_t operand1, int32_t operand2);
int32_t perform_subtraction(int32_t operand1, int32_t operand2);
int32_t perform_multiplication(int32_t operand1, int32_t operand2);
double perform_division(int32_t operand1, int32_t operand2);
int32_t perform_modulo(int32_t operand1, int32_t operand2);
uint32_t perform_left_shift(uint32_t operand1, uint32_t operand2);
uint32_t perform_right_shift(uint32_t operand1, uint32_t operand2);
uint32_t perform_and(uint32_t operand1, uint32_t operand2);
uint32_t perform_or(uint32_t operand1, uint32_t operand2);
uint32_t perform_xor(uint32_t operand1, uint32_t operand2);
void perform_calculation(uint32_t operand1, const char *operator, uint32_t operand2);
int validate_operands(int32_t operand1, int32_t operand2, const char *operator);
void handle_error(const char *message);

/******************************************************************************
 * @brief    Print the usage of the program
 ******************************************************************************/
void print_usage(void)
{
    printf("Usage: ./simplecalc operand1 operator operand2\n");
    printf("Supported Operators:\n");
    printf(" (+)  addition\n");
    printf(" (-)  subtraction\n");
    printf(" (*)  multiplication\n");
    printf(" (/)  divide\n");
    printf(" (%%)  modulo\n");
    printf(" (<<) left shift\n");
    printf(" (>>) right shift\n");
    printf(" (&)  bitwise AND\n");
    printf(" (|)  bitwise OR\n");
    printf(" (^)  bitwise XOR\n");
    printf(" (<<<) rotate left\n");
    printf(" (>>>) rotate right\n");
}

/******************************************************************************
 * @brief    Rotate bits to the left
 * @param    value   The value to be rotated
 * @param    count   The number of positions to rotate
 * @return   Rotated value
 ******************************************************************************/
uint32_t rotate_left(uint32_t value, uint32_t count)
{
    count = count % 32; // Ensure the count is within the 0-31 range
    return (value << count) | (value >> (32 - count));
}

/******************************************************************************
 * @brief    Rotate bits to the right
 * @param    value   The value to be rotated
 * @param    count   The number of positions to rotate
 * @return   Rotated value
 ******************************************************************************/
uint32_t rotate_right(uint32_t value, uint32_t count)
{
    count = count % 32; // Ensure the count is within the 0-31 range
    return (value >> count) | (value << (32 - count));
}

/******************************************************************************
 * @brief    Perform addition
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of addition
 ******************************************************************************/
int32_t perform_addition(int32_t operand1, int32_t operand2)
{
    int64_t result = (int64_t)operand1 + operand2;
    if (result > INT32_MAX || result < INT32_MIN) {
        handle_error("Error! Addition result out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return (int32_t)result;
}

/******************************************************************************
 * @brief    Perform subtraction
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of subtraction
 ******************************************************************************/
int32_t perform_subtraction(int32_t operand1, int32_t operand2)
{
    int64_t result = (int64_t)operand1 - operand2;
    if (result > INT32_MAX || result < INT32_MIN) {
        handle_error("Error! Subtraction result out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return (int32_t)result;
}

/******************************************************************************
 * @brief    Perform multiplication
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of multiplication
 ******************************************************************************/
int32_t perform_multiplication(int32_t operand1, int32_t operand2)
{
    int64_t result = (int64_t)operand1 * operand2;
    if (result > INT32_MAX || result < INT32_MIN) {
        handle_error("Error! Multiplication result out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return (int32_t)result;
}

/******************************************************************************
 * @brief    Perform division
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of division
 ******************************************************************************/
double perform_division(int32_t operand1, int32_t operand2)
{
    if (operand2 == 0) {
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
    if (operand2 == 0) {
        handle_error("Error! Modulo by zero.\n");
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
uint32_t perform_left_shift(uint32_t operand1, uint32_t operand2)
{
    return operand1 << operand2;
}

/******************************************************************************
 * @brief    Perform right shift
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of right shift
 ******************************************************************************/
uint32_t perform_right_shift(uint32_t operand1, uint32_t operand2)
{
    return operand1 >> operand2;
}

/******************************************************************************
 * @brief    Perform bitwise AND
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of AND operation
 ******************************************************************************/
uint32_t perform_and(uint32_t operand1, uint32_t operand2)
{
    return operand1 & operand2;
}

/******************************************************************************
 * @brief    Perform bitwise OR
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of OR operation
 ******************************************************************************/
uint32_t perform_or(uint32_t operand1, uint32_t operand2)
{
    return operand1 | operand2;
}

/******************************************************************************
 * @brief    Perform bitwise XOR
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @return   Result of XOR operation
 ******************************************************************************/
uint32_t perform_xor(uint32_t operand1, uint32_t operand2)
{
    return operand1 ^ operand2;
}

/******************************************************************************
 * @brief    Perform calculation based on operator
 * @param    operand1    First operand
 * @param    operator    Operator as string
 * @param    operand2    Second operand
 ******************************************************************************/
void perform_calculation(uint32_t operand1, const char *operator, uint32_t operand2)
{
    int32_t result;
    uint32_t result_uint;

    // Ensure the operator is long enough to check the extended operators
    if (strlen(operator) == 3) {
        if (strncmp(operator, "<<<", 3) == 0) {
            result_uint = rotate_left(operand1, operand2);
            printf("Result: %u\n", result_uint);
            return;
        } else if (strncmp(operator, ">>>", 3) == 0) {
            result_uint = rotate_right(operand1, operand2);
            printf("Result: %u\n", result_uint);
            return;
        }
    }

    // Use a switch statement to handle different operations
    switch (operator[0])
    {
        case '+':
            result = perform_addition((int32_t)operand1, (int32_t)operand2);
            printf("Result: %d\n", result);
            break;

        case '-':
            result = perform_subtraction((int32_t)operand1, (int32_t)operand2);
            printf("Result: %d\n", result);
            break;

        case '*':
            result = perform_multiplication((int32_t)operand1, (int32_t)operand2);
            printf("Result: %d\n", result);
            break;

        case '/':
            printf("Result: %.2f\n", perform_division((int32_t)operand1, (int32_t)operand2));
            break;

        case '%':
            result = perform_modulo((int32_t)operand1, (int32_t)operand2);
            printf("Result: %d\n", result);
            break;

        case '<':
            if (operator[1] == '<') {
                result_uint = perform_left_shift(operand1, operand2);
                printf("Result: %u\n", result_uint);
            } else {
                handle_error("Error! Unsupported operator.\n");
                exit(EXIT_FAILURE);
            }
            break;

        case '>':
            if (operator[1] == '>') {
                if (operator[2] == '>') {
                    result_uint = rotate_right(operand1, operand2);
                    printf("Result: %u\n", result_uint);
                } else {
                    result_uint = perform_right_shift(operand1, operand2);
                    printf("Result: %u\n", result_uint);
                }
            } else {
                handle_error("Error! Unsupported operator.\n");
                exit(EXIT_FAILURE);
            }
            break;

        case '&':
            result_uint = perform_and(operand1, operand2);
            printf("Result: %u\n", result_uint);
            break;

        case '|':
            result_uint = perform_or(operand1, operand2);
            printf("Result: %u\n", result_uint);
            break;

        case '^':
            result_uint = perform_xor(operand1, operand2);
            printf("Result: %u\n", result_uint);
            break;

        default:
            handle_error("Error! Unsupported operator.\n");
            exit(EXIT_FAILURE);
    }
}

/******************************************************************************
 * @brief    Validate operands for division and modulo operations
 * @param    operand1    First operand
 * @param    operand2    Second operand
 * @param    operator    Operator as string
 * @return   1 if valid, 0 otherwise
 ******************************************************************************/
int validate_operands(int32_t operand1, int32_t operand2, const char *operator)
{
    if (strncmp(operator, "/", 1) == 0 || strncmp(operator, "%", 1) == 0)
    {
        if (operand2 == 0)
        {
            handle_error("Error! Division or modulo by zero.\n");
            return 0;
        }
    }
    return 1;
}

/******************************************************************************
 * @brief    Handle errors
 * @param    message Error message
 ******************************************************************************/
void handle_error(const char *message)
{
    fprintf(stderr, "%s", message);
}

/******************************************************************************
 * @brief    Main function
 ******************************************************************************/
int main(int argc, char *argv[])
{
    if (argc != 4) {
        print_usage();
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;

    // Convert operand1
    uint32_t operand1 = strtoul(argv[1], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE) {
        handle_error("Error! Invalid operand1.\n");
        return EXIT_FAILURE;
    }

    // Convert operand2
    uint32_t operand2 = strtoul(argv[3], &endptr, 10);
    if (*endptr != '\0' || errno == ERANGE) {
        handle_error("Error! Invalid operand2.\n");
        return EXIT_FAILURE;
    }

    // Validate operands
    const char *operator = argv[2];
    if (!validate_operands((int32_t)operand1, (int32_t)operand2, operator)) {
        return EXIT_FAILURE;
    }

    // Perform calculation
    perform_calculation(operand1, operator, operand2);

    return EXIT_SUCCESS;
}
