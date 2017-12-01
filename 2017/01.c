#include <stdio.h>

#define MAXV 10000

void small(void)
{
  int sum = 0;
  char prev = '\0', c;
  char initial;

  initial = c = getchar();

  while (c != EOF && c != '\n') {
    if (c == prev)
      sum = sum + (c - '0');
    prev = c;
    c = getchar();
  }

  if (prev == initial)
    sum = sum + (prev - '0');

  printf("sum is: %d\n", sum);
}

void large(void)
{
  char str[MAXV], c;
  int i = 0, mid;
  int sum = 0;

  while ((c = getchar()) != EOF && c != '\n')
    str[i++] = c;

  mid = i >> 1;

  for (i = 0; i < mid; i++)
    if (str[i] == str[i + mid])
      sum = sum + (str[i] - '0');

  printf("sum is: %d\n", sum << 1);
}

int main(void)
{
  large();
}
