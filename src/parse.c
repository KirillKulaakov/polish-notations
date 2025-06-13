#include "parse.h"

#include <unistd.h>

void push(Node** top, char operation) {
    Node* ptr = malloc(sizeof(Node));
    if (ptr != NULL) {
        ptr->operation = operation;
        if (top == NULL) {
            ptr->next = NULL;
            *top = ptr;
        } else {
            ptr->next = *top;
            *top = ptr;
        }
    }
}

void delete_key(Node** top, char operation) {
    Node* ptr = *top;
    Node* prev = NULL;
    int flag = 0;

    while (ptr != NULL && !flag) {
        if (ptr->operation == operation) {
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

void clear_stack(Node** top) {
    Node* current = *top;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    *top = NULL;
}

void print(Node* top) {
    Node* ptr = top;
    while (ptr) {
        printf("%c", ptr->operation);
        ptr = ptr->next;
    }
}

char* init_arr(int size, int N) {
    char* arr = malloc(N * size);
    return arr;
}

char* read_arr() {
    char* arr = init_arr(sizeof(char), SIZE);
    if (arr == NULL) return NULL;
    int size = SIZE, symbol = getchar(), index = 0;
    while (symbol != 10) {
        arr[index] = (char)symbol;
        index++;
        if (index == size) {
            size *= 2;
            arr = realloc(arr, size * sizeof(char));
            if (arr == NULL) return NULL;
        }
        symbol = getchar();
    }
    arr[index] = '\0';
    char* new_arr = malloc(size * 2 * sizeof(char));
    if (validate_operation(arr, new_arr) == -1) {
        return NULL;
    }
    return new_arr;
}

int validate_operation(char* arr, char* new_arr) {
    int type = 1, count = 0, i = 0, flag = 0, count_x = 0;
    if (sum_char(arr) == 0) flag = -1;
    while (arr[i] != '\0' && !flag) {
        if (is_operation(arr[i])) {
            if (type && arr[i] == MINUS) {
                new_arr[count++] = '0';
                new_arr[count++] = MINUS;
                i += 1;
            } else {
                new_arr[count++] = arr[i];
                i += 1;
            }
            type = 1;
        } else if ((arr[i] == 'x') || (arr[i] >= '0' && arr[i] <= '9')) {
            type = 0;
            new_arr[count++] = arr[i];
            i++;
        } else if (arr[i] == '(' || arr[i] == ')') {
            if (arr[i] == '(') {
                type = 1;
                count_x++;
            } else {
                type = 0;
                count_x--;
            }
            new_arr[count++] = arr[i++];
        } else if (arr[i + 1] != '\0' && arr[i + 2] != '\0' &&
                   ((arr[i] == 's' && arr[i + 1] == 'i' && arr[i + 2] == 'n') ||
                    (arr[i] == 'c' && arr[i + 1] == 'o' && arr[i + 2] == 's') ||
                    (arr[i] == 't' && arr[i + 1] == 'a' && arr[i + 2] == 'n') ||
                    (arr[i] == 'c' && arr[i + 1] == 't' && arr[i + 2] == 'g'))) {
            if (arr[i] == 's')
                new_arr[count++] = SIN;
            else if (arr[i] == 'c' && arr[i + 1] == 'o')
                new_arr[count++] = COS;
            else if (arr[i] == 't')
                new_arr[count++] = TG;
            else if (arr[i] == 'c')
                new_arr[count++] = CTG;
            type = 1;
            i += 3;
        } else if (arr[i + 1] != '\0' && arr[i + 2] != '\0' && arr[i + 3] != '\0' && arr[i] == 's' &&
                   arr[i + 1] == 'q' && arr[i + 2] == 'r' && arr[i + 3] == 't') {
            new_arr[count++] = SQRT;
            type = 1;
            i += 4;
        } else if (arr[i + 1] != '\0' && arr[i] == 'l' && arr[i + 1] == 'n') {
            new_arr[count++] = LN;
            type = 1;
            i += 2;
        } else if (arr[i] == SPACE) {
            new_arr[count++] = SPACE;
            i++;
        } else {
            i++;
            flag = -1;
        }
    }
    new_arr[count] = '\0';
    if (count_x != 0) flag = -1;
    return flag;
}

int sum_char(char* arr) {
    char* ptr = arr;
    int sum = 0;
    while (*ptr != '\0') {
        if (*ptr != '\n' && *ptr != ' ') sum ++;
        ptr++;
    }
    return sum > 0;
}

int is_operation(char ch) { return ch == PLUS || ch == MINUS || ch == MUL || ch == DIV; }

char* polish_convert(char* arr, int len) {
    Node* top = NULL;
    char* output_str = init_arr(sizeof(char), len * 3);
    int count_str = 0, count_stack = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == 'x' || (arr[i] >= '0' && arr[i] <= '9')) {
            add_number(arr, output_str, i, &count_str);
        } else if (is_operation(arr[i]) || arr[i] == SIN || arr[i] == COS || arr[i] == TG || arr[i] == CTG ||
                   arr[i] == LN || arr[i] == SQRT) {
            int priority = priority_operation(arr[i]);
            output_str[count_str++] = SPACE;
            if (count_stack > 0) {
                Node* current = top;
                while (current->next != NULL && current->operation != '(' &&
                       priority <= priority_operation(current->operation)) {
                    Node* next = current->next;
                    output_str[(count_str)++] = current->operation;
                    delete_key(&top, current->operation);
                    (count_stack)--;
                    current = next;
                }
                if (current->next == NULL && current->operation != '(' &&
                    priority <= priority_operation(current->operation)) {
                    output_str[(count_str)++] = current->operation;
                    delete_key(&top, current->operation);
                    (count_stack)--;
                }
            }
            push(&top, arr[i]);
            count_stack++;
        } else if (arr[i] == '(') {
            push(&top, arr[i]);
            count_stack++;
        } else if (arr[i] == ')') {
            Node* current = top;
            while (current->operation != '(') {
                Node* next = current->next;
                output_str[(count_str)++] = current->operation;
                delete_key(&top, current->operation);
                (count_stack)--;
                current = next;
            }
            delete_key(&top, current->operation);
            count_stack--;
        }
    }
    while (top != NULL) {
        output_str[count_str++] = top->operation;
        delete_key(&top, top->operation);
    }
    output_str[count_str] = '\0';
    clear_stack(&top);
    return output_str;
}

void add_number(char* arr, char* output_str, int i, int* count_str) { output_str[(*count_str)++] = arr[i]; }

int priority_operation(char ch) {
    int priority = 0;
    if (ch == PLUS || ch == MINUS)
        priority = 1;
    else if (ch == MUL || ch == DIV)
        priority = 2;
    else if (ch == SIN || ch == COS || ch == TG || ch == CTG || ch == LN || ch == SQRT)
        priority = 3;
    return priority;
}
