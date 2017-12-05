#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "05.txt"

#define MAXV 2048
int sm[MAXV];
int lg[MAXV];

int small(int size)
{
  int i = 0;
  int count = 0;

  while (i < size) {
    count++;
    i += sm[i]++;
  }

  return count;
}

int big(int size)
{
  int n;
  int i, count;
  i = count = 0;

  while (i < size) {
    count++;
    n = lg[i];
    lg[i] += n >= 3 ? -1 : 1;
    i += n;
  }

  return count;
}

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;

  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(1);
  }

  int i = 0;
  while (getline(&line, &len, fp) != -1) {
    line[strcspn(line, "\n")] = 0;
    lg[i] = sm[i] = atoi(line);
    i++;
  }

  printf("small: %d\n", small(i));
  printf("big: %d\n", big(i));

  return 0;
}
