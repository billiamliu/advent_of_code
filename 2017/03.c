#include <stdlib.h>
#include <stdio.h>

#define MAXD 10000

struct point {
  int x;
  int y;
};

int **
initMatrix(int **matrix, int size)
{
  int i, j;
  matrix = (int **) malloc(size * sizeof(int *));
  for (i = 0; i < size; i++)
    matrix[i] = (int *) malloc(size * sizeof(int));

  for (i = 0; i < size; i++)
    for (j = 0; j < size; j++)
      matrix[i][j] = 0;

  return matrix;
}

int valueOf(int **matrix, struct point *pt)
{
  int sum = 0;
  sum += matrix[pt->x - 1][pt->y - 1];
  sum += matrix[pt->x    ][pt->y - 1];
  sum += matrix[pt->x + 1][pt->y - 1];
  sum += matrix[pt->x - 1][pt->y    ];
  sum += matrix[pt->x    ][pt->y    ];
  sum += matrix[pt->x + 1][pt->y    ];
  sum += matrix[pt->x - 1][pt->y + 1];
  sum += matrix[pt->x    ][pt->y + 1];
  sum += matrix[pt->x + 1][pt->y + 1];

  return sum;
}

void turn(int *x, int *y)
{
  int tmp;
  tmp = *x;
  *x = *y * -1;
  *y = tmp;
}

void step(int **matrix, int val, struct point *pt)
{
  static int turnCount = 1, i = 1, j = 1; /* direction magnitute */
  static int x = 1, y = 0; /* direction multipliers */

  matrix[pt->x][pt->y] = val;

  if (j == 0) {
    turn(&x, &y);
    i = j = ++turnCount;
  }

  if (i == 0)
    turn(&x, &y);

  if (i-- > 0) {
    pt->x += x;
  }
  else if (j-- > 0) {
    pt->y += y;
  }
}

int main(void) {
  int target = 277678; 

  int middle = MAXD / 2;
  int **memory;
  memory = initMatrix(memory, MAXD);

  struct point *pt = (struct point *) malloc(sizeof(struct point));
  pt->x = pt->y = middle;

  int total = 1;

  do {
    step(memory, total, pt);
  } while ((total = valueOf(memory, pt)) <= target);

  printf("ans: %d\n", total);
};
