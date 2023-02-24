#include "smartcalc.h"

#include <string.h>

int MainCalc(char *sstr, double *res, double x) {
  if (sstr != NULL) {
    size_t len = strlen(sstr);
    char *str = calloc(len + 1, sizeof(char));
    if (str != NULL) {
      strcpy(str, sstr);
      smart_stack *stack = NULL;
      if (!convert_to_polish(&stack, str)) {
        smart_stack *new_stack = NULL;
        reverse_stack(&stack, &new_stack);
        *res = calc(new_stack, x);
        free(stack);
      } else {
        return PARSE_ERROR;
      }
      free(str);
    }
  }
  return OK;
}

smart_stack *init(double n, int importance, value_type type) {
  smart_stack *stack_new = (smart_stack *)malloc(sizeof(smart_stack));
  stack_new->data = n;
  stack_new->type = type;
  stack_new->importance = importance;
  stack_new->next = NULL;
  return stack_new;
}

void push(smart_stack **stack, double value, int importance, value_type type) {
  smart_stack *stack_new = init(value, importance, type);
  stack_new->next = *stack;
  *(stack) = stack_new;
}

void pop(smart_stack **stack_top) {
  if (*stack_top != NULL) {
    smart_stack *temp = *stack_top;
    *stack_top = (*stack_top)->next;
    free(temp);
  }
}

int convert_to_polish(smart_stack **stack_top, char *str) {
  smart_stack *operators = NULL;
  char *first_digit, *last_digit;
  double number = 0;
  char prev = '(';
  int open_braces = 0, close_braces = 0;
  while (*str != '\0') {
    if (*str == 'x') {
      push(stack_top, 0, 0, X);
      ++str;
    } else if (*str >= '0' && *str <= '9') {
      first_digit = str;
      do {
        last_digit = str;
        ++str;
      } while ((*str >= '0' && *str <= '9') || *str == '.');
      if (*last_digit == '.') return PARSE_ERROR;
      number = strtod(first_digit, &last_digit);
      push(stack_top, number, 0, Num);
    } else if (*str == '(') {
      push(&operators, 0, 0, Open_brace);
      ++open_braces;
      ++str;
    } else if (*str == ')') {
      if (close_brace_case(stack_top, &operators) == PARSE_ERROR)
        return PARSE_ERROR;
      ++close_braces;
      ++str;
    } else if (strchr("+-*/^", *str)) {
      operators_case(stack_top, &operators, str, prev);
      ++str;
    } else {
      funcs_case(&operators, &str);
    }
    --str;
    prev = *str;
    ++str;
  }
  if (operators != NULL)
    if (null_ops_case(close_braces, open_braces, &operators, stack_top))
      return PARSE_ERROR;
  free(operators);
  return OK;
}

int null_ops_case(int close_braces, int open_braces, smart_stack **operators,
                  smart_stack **stack_top) {
  if (close_braces != open_braces || (*operators)->type == Close_brace ||
      (*operators)->type == Open_brace)
    return PARSE_ERROR;
  while (*operators != NULL) {
    push(stack_top, 0, (*operators)->importance, (*operators)->type);
    pop(operators);
  }
  return OK;
}

void funcs_case(smart_stack **operators, char **str) {
  if (!strncmp(*str, "sin", 3)) {
    push(operators, 0, 4, Sin);
    (*str) += 3;
  } else if (!strncmp(*str, "cos", 3)) {
    push(operators, 0, 4, Cos);
    (*str) += 3;
  } else if (!strncmp(*str, "log", 3)) {
    push(operators, 0, 4, Log);
    (*str) += 3;
  } else if (!strncmp(*str, "ln", 2)) {
    push(operators, 0, 4, Ln);
    (*str) += 2;
  } else if (!strncmp(*str, "sqrt", 4)) {
    push(operators, 0, 4, Sqrt);
    (*str) += 4;
  } else if (!strncmp(*str, "tan", 3)) {
    push(operators, 0, 4, Tan);
    (*str) += 3;
  } else if (!strncmp(*str, "atan", 4)) {
    push(operators, 0, 4, Atan);
    (*str) += 4;
  } else if (!strncmp(*str, "asin", 4)) {
    push(operators, 0, 4, Asin);
    (*str) += 4;
  } else if (!strncmp(*str, "acos", 4)) {
    push(operators, 0, 4, Acos);
    (*str) += 4;
  } else if (!strncmp(*str, "mod", 3)) {
    push(operators, 0, 2, Mod);
    (*str) += 3;
  }
}

void operators_case(smart_stack **stack_top, smart_stack **operators, char *str,
                    int prev) {
  if (*str == '-') {
    while ((*operators) != NULL && (*operators)->importance >= 1) {
      push(stack_top, 0, (*operators)->importance, (*operators)->type);
      pop(operators);
    }
    if (prev == '(')
      push(operators, 0, 1, Unary_minus);
    else
      push(operators, 0, 1, Minus);
  } else if (*str == '+') {
    while ((*operators) != NULL && (*operators)->importance >= 1) {
      push(stack_top, 0, (*operators)->importance, (*operators)->type);
      pop(operators);
    }
    if (prev == '(')
      push(operators, 0, 1, Unary_plus);
    else
      push(operators, 0, 1, Plus);
  } else if (*str == '*') {
    while ((*operators) != NULL && (*operators)->importance >= 2) {
      push(stack_top, 0, (*operators)->importance, (*operators)->type);
      pop(operators);
    }
    push(operators, 0, 2, Multi);
  } else if (*str == '/') {
    while ((*operators) != NULL && (*operators)->importance >= 2) {
      push(stack_top, 0, (*operators)->importance, (*operators)->type);
      pop(operators);
    }
    push(operators, 0, 2, Div);
  } else if (*str == '^') {
    while ((*operators) != NULL && (*operators)->importance >= 3) {
      push(stack_top, 0, (*operators)->importance, (*operators)->type);
      pop(operators);
    }
    push(operators, 0, 3, Pow);
  }
}

int close_brace_case(smart_stack **stack_top, smart_stack **operators) {
  while ((*operators)->type != Open_brace && *operators != NULL) {
    push(stack_top, (*operators)->data, (*operators)->importance,
         (*operators)->type);
    pop(operators);
  }
  if (*operators == NULL) return PARSE_ERROR;
  pop(operators);
  if (*operators != NULL) {
    if ((*operators)->type >= Cos && (*operators)->type <= Log) {
      push(stack_top, 0, 4, (*operators)->type);
      pop(operators);
    }
  }
  return OK;
}

void reverse_stack(smart_stack **stack, smart_stack **new_stack) {
  while (*stack != NULL) {
    push(new_stack, (*stack)->data, (*stack)->importance, (*stack)->type);
    pop(stack);
  }
}

double calc(smart_stack *stack, double x) {
  smart_stack *nums = NULL;
  double op1 = 0, op2 = 0;
  while (stack != NULL) {
    op1 = 0, op2 = 0;
    if (stack->type == Num) {
      push(&nums, stack->data, 0, Num);
      pop(&stack);
    } else if (stack->type == X) {
      push(&nums, x, 0, Num);
      pop(&stack);
    } else {
      if (stack->type >= Plus && stack->type <= Mod) {
        op2 = nums->data;
        pop(&nums);
        op1 = nums->data;
        pop(&nums);
        calc_operators(&nums, op1, op2, stack->type);
      } else {
        op1 = nums->data;
        pop(&nums);
        calc_funcs(&nums, op1, stack->type);
      }
      pop(&stack);
    }
  }
  if (nums != NULL) op1 = nums->data;
  free(nums);
  return op1;
}

void calc_operators(smart_stack **nums, double op1, double op2,
                    value_type type) {
  switch (type) {
    case Plus:
      push(nums, op1 + op2, 0, Num);
      break;
    case Minus:
      push(nums, op1 - op2, 0, Num);
      break;
    case Multi:
      push(nums, op1 * op2, 0, Num);
      break;
    case Div:
      push(nums, op1 / op2, 0, Num);
      break;
    case Pow:
      push(nums, pow(op1, op2), 0, Num);
      break;
    case Mod:
      push(nums, fmod(op1, op2), 0, Num);
      break;
    default:
      break;
  }
}

void calc_funcs(smart_stack **nums, double op1, value_type type) {
  switch (type) {
    case Sin:
      push(nums, sin(op1), 0, Num);
      break;
    case Cos:
      push(nums, cos(op1), 0, Num);
      break;
    case Tan:
      push(nums, tan(op1), 0, Num);
      break;
    case Asin:
      push(nums, asin(op1), 0, Num);
      break;
    case Acos:
      push(nums, acos(op1), 0, Num);
      break;
    case Sqrt:
      push(nums, sqrt(op1), 0, Num);
      break;
    case Ln:
      push(nums, log(op1), 0, Num);
      break;
    case Log:
      push(nums, log10(op1), 0, Num);
      break;
    case Atan:
      push(nums, atan(op1), 0, Num);
      break;
    case Unary_minus:
      push(nums, -op1, 0, Num);
      break;
    case Unary_plus:
      push(nums, fabs(op1), 0, Num);
      break;
    default:
      break;
  }
}
