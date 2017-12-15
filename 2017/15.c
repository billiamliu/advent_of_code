#include <stdio.h>

int small(long a, long b, int a_fact, int b_fact, int boss, int rounds)
{
  int count = 0;
  while (rounds--) {
    a = (a * a_fact) % boss;
    b = (b * b_fact) % boss;
    if ((a & 0xFFFF) == (b & 0xFFFF))
      count++;
  }

  return count;
}

int large(long a, long b, int a_fact, int b_fact, int boss, int rounds)
{
  int count = 0;
  while (rounds--) {
    while ((a = (a * a_fact) % boss) % 4 != 0)
      ;
    while ((b = (b * b_fact) % boss) % 8 != 0)
      ;
    if ((a & 0xFFFF) == (b & 0xFFFF))
      count++;
  }
  return count;
}

int main(void)
{
  printf("%d\n", small(116, 299, 16807, 48271, 2147483647, 40000000));
  printf("%d\n", large(116, 299, 16807, 48271, 2147483647, 5000000));
  return 0;
}
