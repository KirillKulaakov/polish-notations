#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define SIZE 100
#define MINUS '-'
#define PLUS '+'
#define MUL '*'
#define DIV '/'
#define SIN 's'
#define COS 'c'
#define TG 't'
#define CTG 'g'
#define SQRT 'q'
#define LN 'l'
#define SPACE ' '
#define FLAG 7777

typedef struct node {
    char operation;
    struct node* next;
} Node;

typedef struct stack {
    double number;
    struct stack* next;
} Stack;


void push(Node **top, char operation);
void delete_key(Node **top, char operation);
void print(Node *top);
void clear_stack(Node** top);


void push_stack_number(Stack **top, double number);
void delete_key_stack_number(Stack **top, double number);
void print_stack(Stack *top);
void clear_stack_number(Stack** top);

char *init_arr();
char *read_arr();
int validate_operation(char *arr, char *new_arr);
int sum_char(char* arr);
int is_operation(char ch);
char* polish_convert(char *arr, int len);
int priority_operation(char ch);
void add_uminus_number(char *arr, char *output_str, int i, int *count_str);
void add_number(char *arr, char *output_str, int i, int *count_str);
// void check_priority_operation(int priority_stack_operation, int priority, char* output_str, int *count_str, Node* top, Node* current, int* count_stack);
// void add_to_output_str(char* output_str, int* count_str, Node* top, Node* current, int* count_stack);

double ariphmetics(char* arr, double x, int len_arr);
double operations_number(double number1, double number2, char operation);
double operations_functions(double number, char operation);
