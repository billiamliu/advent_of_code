#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT "19.txt"
#define MAXD 200
char grid[MAXD][MAXD] = { 0 };

void showGrid()
{
  for (int i = 0; i < MAXD; i++) {
    for (int j = 0; j < MAXD; j++)
      printf("%c", grid[i][j]);
    printf("\n");
  }
}

int findStart()
{
  int i = 0;
  while (grid[0][i++] != '|')
    ;
  return i - 1;
}

int isLine(int i, int j)
{
  return grid[i][j] != ' ' && grid[i][j] != '\0';;
}

int isNotLine(int i, int j)
{
  return grid[i][j] == ' ' || grid[i][j] == '\0';
}

int changeDirection(int i, int j, int *x, int *y)
{
  if (*x == 0) {
    /* only y moves */
    if (isLine(i + *y, j))
      return 0;
    if (isLine(i, j + 1) && isNotLine(i, j - 1)) {
      *y = 0;
      *x = 1;
      return 0;
    } else if (isLine(i, j - 1) && isNotLine(i, j + 1)) {
      *y = 0;
      *x = -1;
      return 0;
    }
    return -1; /* end of line */
  } else {
    /* only x moves */
    if (isLine(i, j + *x))
      return 0;
    if (isLine(i + 1, j) && isNotLine(i - 1, j)) {
      *y = 1;
      *x = 0;
      return 0;
    } else if (isLine(i - 1, j) && isNotLine(i + 1, j)) {
      *y = -1;
      *x = 0;
      return 0;
    }
    return -1; /* end of line */
  }
}

void small()
{
  char letters[26];
  int n = 0;
  int i = 0, j = findStart();
  int y = 1, x = 0; /* direction */
  int steps = 0, end = 0;
  while (end != -1) {
    if (grid[i][j] == '+')
      end = changeDirection(i, j, &x, &y);
    if (grid[i][j] - 'A' >= 0 && grid[i][j] - 'A' <= 26) {
      letters[n++] = grid[i][j];
      end = changeDirection(i, j, &x, &y);
    }
    i += y;
    j += x;
    steps++;
  }
  letters[n] = '\0';
  printf("%s\n", letters);
  printf("%d\n", steps);
}

int main(void)
{
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  int i, j;
  char c;

  fp = fopen(INPUT, "r");
  if (fp == NULL) {
    perror(INPUT);
    exit(1);
  }

  i = 0;
  while (getline(&line, &len, fp) != -1) {
    line[strcspn(line, "\n")] = 0;
    j = 0;
    while ((c = line[j]))
      grid[i][j++] = c;
    i++;
  }

  small();
  return 0;
}
