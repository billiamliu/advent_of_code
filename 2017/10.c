#include <stdio.h>

#define IN_SIZE 16
#define DENSE_SIZE 16
#define LENG 256

int cipher[LENG];
int dense[DENSE_SIZE];
int input[] = { 130,126,1,11,140,2,255,207,18,254,246,164,29,104,0,224 };
char in[] = "130,126,1,11,140,2,255,207,18,254,246,164,29,104,0,224";

void reverse(int *array, int size, int index, int amount)
{
  int stack[amount];
  int i, j;
  for (i = 0; i < amount; i++) {
    stack[i] = array[(index + i) % size];
  }
  for (j = 0; j < amount; j++) {
    array[(index + j) % size] = stack[--i];
  }
}

void initSeq(int *arr, int size) {
  while (size--) {
    arr[size] = size;
  }
}

void small()
{
  int pos = 0;
  for (int i = 0; i < IN_SIZE; i++) {
    reverse(cipher, LENG, pos, input[i]);
    pos += input[i] + i;
  }

  printf("%d\n", cipher[0] * cipher[1]);
}

int strleng(char *str)
{
  int i = 0;
  while (str[i++])
    ;
  return i - 1;
}

void large(char *input, int leng, int *store, int size, int rounds) {
  int pos = 0;
  int skip = 0;

  int suffix[] = { 17, 31, 73, 47, 23 };
  int sLeng = 5;

  while (rounds--) {
    for (int i = 0; i < leng; i++, skip++) {
      reverse(store, size, pos, (int) in[i]);
      pos += (int) in[i] + skip;
    }

    for (int i = 0; i < sLeng; i++, skip++) {
      reverse(store, size, pos, suffix[i]);
      pos += suffix[i] + skip;
    }
  }
}

void compress(int *src, int sLeng, int cycle, int *dest)
{
  int i = 0;
  int j = 0;
  int k = 1;
  int acc = 0;
  for (i = 0; i < sLeng; i++, k++) {
    if (k == cycle) {
      acc = acc ^ src[i];
      dest[j++] = acc;
      acc = 0;
      k = 0;
    } else {
      acc = acc ^ src[i];
    }
  }
}

void printHex()
{
  for (int i = 0; i < DENSE_SIZE; i++)
    printf("%2x", dense[i]);
  printf("\n");
}

void testSuite(void)
{
  printf("\n\n\tBEGIN TEST SUITE\n\n");

  int src[] = {
    65 , 27 , 9 , 1 , 4 , 3 , 40 , 50 , 91 , 7 , 6 , 0 , 2 , 5 , 68 , 22 ,
    65 , 27 , 9 , 1 , 4 , 3 , 40 , 50 , 91 , 7 , 6 , 0 , 2 , 5 , 68 , 22 };
  int dest[2] = { 0 };
  printf("\ttest #compress\n");
  compress(src, 32, 16, dest);
  printf("\tdest 0 should equal 64: %d\n", dest[0]);
  printf("\tdest 1 should equal 64: %d\n", dest[1]);

  printf("\n\n\tEND TEST SUITE\n");
}

int main(void)
{
  /*
  testSuite();
  */

  initSeq(cipher, LENG);
  small();
  initSeq(cipher, LENG);
  large(in, strleng(in), cipher, LENG, 64);
  compress(cipher, LENG, 16, dense);
  printHex();

  return 0;
}
