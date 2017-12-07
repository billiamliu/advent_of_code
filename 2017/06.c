/*
 * INCOMPLETE
 */
#include<stdio.h>
#include<stdlib.h>

#define MAXV 110000 /* 100 000 */
#define WIDTH 16

struct data {
  int hash;
  int value[WIDTH];
  int time;
  struct data *next;
};

int hash(int * array, int size)
{
  /* based on http://www.cse.yorku.ca/~oz/hash.html */
  long hash = 127;

  while (size--)
    hash = (hash << 3) + array[size] + size;

  return hash % 100000;
}

int max(int * array, int size)
{
  int index = 0;
  for (int i = 0; i < size;  i++)
    if (array[i] > array[index])
      index = i;

  return index;
}

void redistribute(int * array, int size, int source) {
  int n = array[source];
  array[source++] = 0;

  while (n--) {
    if (source == size)
      source = 0;
    array[source++]++;
  }
}

void initializeMemory(struct data *memory, int size)
{
  struct data *p;
  for (int i = 0; i < size; i++) {
    p = malloc(sizeof(struct data));
    p->next = NULL;
    p->hash = i;
    p->time = 0;
    memory[i] = *p;
  }
}

void copy(int *store, int *input, int size)
{
  while (size--)
    store[size] = input[size];
}

int arrayEq(int size, int *a, int *b)
{
  int flag = 1;
  while (size--)
    if (a[size] != b[size])
      flag = 0;

  return flag;
}

struct data *
record(struct data *p, int hash, int *input, int size, int count) {
  struct data *tp;
  if (p == NULL) {
    p = malloc(sizeof(struct data));
    p->hash = hash;
    p->time = count;
    copy(p->value, input, size);
    p->next = NULL;
    return p;
  } else {
    tp = p;
    while (p->next != NULL)
      p = p->next;
    p->next = record(p->next, hash, input, size, count);

    return tp;
  }
}

int exist(struct data *slot, int *input, int size) {
  if (slot == NULL)
    return 0;

  if (arrayEq(size, slot->value, input))
    return 1;
  else
    return exist(slot->next, input, size);
}

void show(int *input, int size)
{
  for (int i = 0; i < size; i++)
    printf("%2d ", input[i]);
  printf("\n");
}

int main(void)
{
  int input[] = { 0, 5, 10, 0, 11, 14, 13, 4, 11, 8, 8, 7, 1, 4, 12, 11 };
  int count = 0;
  int nextIndex;
  int key;
  struct data *memory[MAXV];
  for (int i = 0; i < WIDTH; i++)
    memory[i] = NULL;

  key = hash(input, WIDTH);
  while (exist(memory[key], input, WIDTH) == 0) {
    memory[key] = record(memory[key], key, input, WIDTH, count);
    nextIndex = max(input, WIDTH);
    redistribute(input, WIDTH, nextIndex);
    key = hash(input, WIDTH);
    count++;
  }

  printf("count %d\n", count);
  return 0;
}
