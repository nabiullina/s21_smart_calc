#include "stack.h"

int main() {
  char *str = "atan(2*x)";
  smart_stack *stack = NULL;
  if (!convert_to_polish(&stack, str)) {
    smart_stack *new_stack = NULL;
    reverse_stack(&stack, &new_stack);
    double res = calc(new_stack, 0.0019);
    printf("%lf\n", res);
  }
  return 0;
}