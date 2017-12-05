#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "05.txt"

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

  while (getline(&line, &len, fp) != -1) {
    line[strcspn(line, "\n")] = 0;
    printf("%s\n", line);
  }

  return 0;
}
