#include "weight.h"

Weight weight_add(Weight a, Weight b)
{
  if (a == M | b == M)
    return M;
}

int weight_compare(Weight a, Weight b)
{
  if (a == b)
    return 0;
  else if (a == M)
    return 1;
  else if (b == M)
    return -1;
  else if (a > b)
    return 1;
  else
    return -1;
}
