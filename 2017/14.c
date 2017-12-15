#include <stdio.h>
#include <string.h>

#define HEIGHT 128
#define DENSE_LENG 16
#define CIPHER_LENG 256

int cipher[CIPHER_LENG];
int dense[DENSE_LENG];
short matrix[128][128];
short visited[128][128];
const char digits[] = "0123456789abcdef";
const char lookup[16][5] = {
  "0000", "0001", "0010", "0011",
  "0100", "0101", "0110", "0111",
  "1000", "1001", "1010", "1011",
  "1100", "1101", "1110", "1111"
};

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

void scramble(char *seed, int *store, int size)
{
  int pos = 0;
  int skip = 0;
  int rounds = 64;

  int suffix[] = { 17, 31, 73, 47, 23 };
  int sLeng = 5;

  int i;
  char c;

  while (rounds--) {
    i = 0;
    while ((c = seed[i++])) {
      reverse(store, size, pos, (int) c);
      pos += (int) c + skip++;
    }
    for (i = 0; i < sLeng; i++, skip++) {
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

char *denseToHash(int *src, int leng, char *output)
{
  char temp[DENSE_LENG * 2 + 1];
  int i;
  for (i = 0; i < leng; i++)
    sprintf(&temp[i * 2], "%02x", src[i]);
  temp[DENSE_LENG * 2] = '\0';

  i = 0;
  while ((output[i] = temp[i]))
    i++;

  return output;
}

void int2str(int n, char *store) {
  sprintf(store, "%d", n);
}

char *createStrInput(char *store, char *prefix, int k)
{
  int i = 0;
  int j = 0;
  char c;
  char temp[4];
  int2str(k, temp);

  while ((c = prefix[i]))
    store[i++] = c;
  store[i++] = '-';
  while ((c = temp[j++]))
    store[i++] = c;
  store[i] = '\0';

  return store;
}

/* accesses globals, main() for hashing */
char * hash(char *seed, char *output)
{
  initSeq(cipher, CIPHER_LENG);
  scramble(seed, cipher, CIPHER_LENG);
  compress(cipher, CIPHER_LENG, DENSE_LENG, dense);
  denseToHash(dense, DENSE_LENG, output);
  return output;
}

char * hexToBin(char *hexes, char *bins)
{
  char *c;
  int i = 0;
  bins[0] = '\0';
  while ((c = &hexes[i++]) && *c != '\0') {
    c = strchr(digits, *c);
    strcat(bins, lookup[c - digits]);
  }

  return bins;
}

int countBins(char *bins)
{
  int count = 0;
  int i = 0;
  while (bins[i])
    if (bins[i++] == '1')
      count++;

  return count;
}

void testSuite(void)
{
  printf("\n\t\tBEGIN TESTS\n\n");

  printf("\ntest #denseToHash\n");
  int dense[DENSE_LENG];
  char store[DENSE_LENG * 2 + 1];
  for (int i = 0; i < DENSE_LENG; i++)
    dense[i] = i * DENSE_LENG;
  printf("should equal:\n00102030405060708090a0b0c0d0e0f0\n");
  denseToHash(dense, DENSE_LENG, store);
  printf("%s\n", store);

  printf("\ntest #createStrInput\n");
  char input[] = "abcdefgh";
  char temp[13]; /* [a-Z]{8}-\d{1,3}\0 */
  printf("should equal:\nabcdefgh-123\n");
  printf("%s\n", createStrInput(temp, input, 123));

  printf("\ntest #scramble\n");
  char day10[] = "130,126,1,11,140,2,255,207,18,254,246,164,29,104,0,224"; /* 54 */
  initSeq(cipher, CIPHER_LENG);
  scramble(day10, cipher, CIPHER_LENG);
  printf("should equal:\n95, 116, 78\n");
  printf("%d, %d, %d\n", cipher[0], cipher[1], cipher[2]);

  printf("\ntest #hashing\n");
  char output[33];
  hash(day10, output);
  printf("should equal:\ne1462100a34221a7f0906da15c1c979a\n");
  printf("%s\n", output);

  printf("\ntest #hexToBin\n");
  char hex[] = "0f31";
  char bin[17];
  hexToBin(hex, bin);
  printf("should equal:\n0000111100110001\n%s\n", bin);

  printf("\ntest #countBin\n");
  char bins[] = "001011110101";
  printf("should equal:\n7\n%d\n", countBins(bins));

  printf("\n\t\tEND TESTS\n\n");
}

void small(void)
{
  char input[] = "xlqgujun";
  char seed[13];
  char hashout[33];
  char bin[129];
  int count = 0;
  int i;
  for (i = 0; i < 128; i++) {
    createStrInput(seed, input, i);
    hash(seed, hashout);
    hexToBin(hashout, bin);
    count += countBins(bin);
  }
  printf("%d\n", count);
}

void initGrid(void)
{
  for (int i = 0; i < 128; i++)
    for (int j = 0; j < 128; j++)
      visited[i][j] = matrix[i][j] = 0;
}

void dfs(short grid[128][128], int width, int height, int x, int y)
{
  if (x >= 0 && x < width)
    if (y >= 0 && y < height)
      if (visited[x][y] == 0) {
        visited[x][y] = 1;
        if (grid[x][y]) {
          dfs(grid, width, height, x    , y + 1);
          dfs(grid, width, height, x    , y - 1);
          dfs(grid, width, height, x + 1, y    );
          dfs(grid, width, height, x - 1, y    );
        }
      }
}

void large(void)
{
  initGrid();

  char input[] = "xlqgujun";
  char seed[13];
  char hashout[33];
  char bin[129];
  int count = 0;
  int i, j;
  for (i = 0; i < 128; i++) {
    createStrInput(seed, input, i);
    hash(seed, hashout);
    hexToBin(hashout, bin);
    count += countBins(bin);
    for (j = 0; j < 128; j++)
      matrix[i][j] = bin[j] == '1' ? 1 : 0;
  }
  int islands = 0;
  for (i = 0; i < 128; i++)
    for (j = 0; j < 128; j++)
      if (visited[i][j] == 0 && matrix[i][j]) {
        dfs(matrix, 128, 128, i, j);
        islands++;
      }

  printf("%d\n", count);
  printf("%d\n", islands);
}

int main(void)
{
  /*
  testSuite();
  small();
  */
  large();
  return 0;
}
