#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum value_type {
  Num,
  X,
  Open_brace,
  Close_brace,
  Plus,
  Minus,
  Multi,
  Div,
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
double calc(smart_stack *stack, double x);
int MainCalc(char *str, double *res, double x);
void calc_funcs(smart_stack **nums, double op1, value_type type);
void calc_operators(smart_stack **nums, double op1, double op2,
                    value_type type);
int close_brace_case(smart_stack **stack_top, smart_stack **operators);
void operators_case(smart_stack **stack_top, smart_stack **operators, char *str,
                    int prev);
void funcs_case(smart_stack **operators, char **str);
int null_ops_case(int close_braces, int open_braces, smart_stack **operators,
                  smart_stack **stack_top);
