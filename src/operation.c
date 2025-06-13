#include "parse.h"

void push_stack_number(Stack **top, double number) {
    Stack *ptr = malloc(sizeof(Stack));
    if (ptr != NULL) {
        ptr->number = number;
        if (top == NULL) {
            ptr->next = NULL;
            *top = ptr;
        } else {
            ptr->next = *top;
            *top = ptr;
        }
    }
}

void print_stack(Stack *top) {
    Stack *ptr = top;
    while (ptr) {
        printf("%lf", ptr->number);
        ptr = ptr->next;
    }
}

void delete_key_stack_number(Stack **top, double number) {
    Stack *ptr = *top;
    Stack *prev = NULL;
    int flag = 0;

    while (ptr != NULL && !flag) {
        if (ptr->number == number) {
            if (ptr == *top) {
                *top = ptr->next;
                free(ptr);
                ptr = *top;
                flag = 1;
            } else {
                prev->next = ptr->next;
                free(ptr);
                ptr = prev->next;
                flag = 1;
            }
        } else {
            prev = ptr;
            ptr = ptr->next;
        }
    }
}

void clear_stack_number(Stack **top) {
    Stack *current = *top;
    Stack *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *top = NULL;
}

double ariphmetics(char *arr, double x, int len_arr) {
    Stack *top = NULL;
    int i = 0, flag = 0;
    double sum = 0.0;
    while (i < len_arr && !flag) {
        // printf("\nefe i = %d\n", i);
        // print_stack(top);
        if (((arr[i] >= '0' && arr[i] <= '9') || arr[i] == 'x') && !flag) {
            while ((arr[i] >= '0' && arr[i] <= '9') || (arr[i] == 'x')) {
                if (arr[i] == 'x')
                    sum = sum * 10.0 + x;
                else
                    sum = sum * 10.0 + (int)arr[i] - 48;
                i++;
            }
            push_stack_number(&top, sum);
            sum = 0.0;
            // print_stack(top);
        } else if (is_operation(arr[i]) && !flag) {
            Stack *current = top;
            Stack *current_next = current->next;
            double result = operations_number(current->number, current_next->number, arr[i]);
            if (result == FLAG) flag = FLAG;
            delete_key_stack_number(&top, current->number);
            delete_key_stack_number(&top, current_next->number);
            push_stack_number(&top, result);
            i++;
            // print_stack(top);
        } else if (arr[i] == SIN || arr[i] == COS || arr[i] == TG || arr[i] == CTG || arr[i] == LN ||
                   arr[i] == SQRT) {
            Stack *current = top;
            double result = operations_functions(current->number, arr[i]);
            if (result == FLAG) flag = FLAG;
            delete_key_stack_number(&top, current->number);
            push_stack_number(&top, result);
            i++;
        } else if (arr[i] == SPACE)
            i++;
    }
    double all_result = top->number;
    if (flag == FLAG) all_result = FLAG;
    clear_stack_number(&top);
    return all_result;
}

double operations_number(double number1, double number2, char operation) {
    double result;
    if (operation == PLUS)
        result = number2 + number1;
    else if (operation == MINUS)
        result = number2 - number1;
    else if (operation == MUL)
        result = number2 * number1;
    else if (operation == DIV) {
        if (number1 == 0)
            return FLAG;
        else
            result = number2 / number1;
    }
    return result;
}

double operations_functions(double number, char operation) {
    double result;
    if (operation == COS)
        result = cos(number);
    else if (operation == SIN)
        result = sin(number);
    else if (operation == TG) {
        if (number / M_PI == 1.0 || number / M_PI == 2.0 || number / M_PI == 3.0 || number / M_PI == 4.0 ||
            number == 0.0)
            result = FLAG;
        else
            result = tan(number);
    } else if (operation == CTG) {
        if (number / M_PI == 1.0 || number / M_PI == 2.0 || number / M_PI == 3.0 || number / M_PI == 4.0 ||
            number == 0.0)
            result = FLAG;
        else
            result = 1.0 / tan(number);

    } else if (operation == SQRT) {
        if (number < 0.0)
            result = FLAG;
        else
            result = sqrt(number);
    } else if (operation == LN) {
        if (number <= 0.0)
            result = FLAG;
        else
            result = log(number);
    }
    return result;
}