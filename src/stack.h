#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef enum value_type {
  Num,
  X,
  Plus,
  Minus,
  Multi,
  Div,
  Open_brace,
  Close_brace,
  Pow,
  Mod,
  Unary_plus,
  Unary_minus,
  Cos,
  Sin,
  Tan,
  Acos,
  Asin,
  Atan,
  Sqrt,
  Ln,
  Log
} value_type;

enum code { OK, PARSE_ERROR };

typedef struct stack {
  double data;
  value_type type;
  int importance;
  struct stack *next;
} smart_stack;

smart_stack *init(double n, int importance, value_type type);
void push(smart_stack **stack, double value, int importance, value_type type);
void pop(smart_stack **last);
int convert_to_polish(smart_stack **stack_top, char *str);
void reverse_stack(smart_stack **stack, smart_stack **new_stack);
double calc(smart_stack *stack);
void MainCalc(char*str, double*res, double x);

void output_list(smart_stack *stack_top);
