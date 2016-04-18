#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 128
#define ARRAY_SIZE 128

int tokenizer(const char *str, int len)
{
  int i = 0, count = 0;

  if (str == NULL || len <= 0)
    return -1;
}

double variance(const int *arr, const int size, const double average)
{
  double ret = 0.0f, sum = 0.0f;
  int i = 0;

  if (arr == NULL)
    return 0;

  while (i < size) {
    sum += (arr[i] - average) * (arr[i] - average);
    i++;
  }

  ret = sum / (size - 1);
  ret = sqrt(ret);
  return ret;
}

double average(const int *arr, const int size)
{
  double ret = 0.0f, sum = 0.0f;
  int i = 0;

  if (arr == NULL)
    return 0;

  while (i < size) {
    sum += arr[i++];
  }

  ret = sum / size;
  return ret;

};

int analytics(FILE *fp)
{
  int i = 0, count = 0, ret = 0;
  char buff[BUFF_SIZE] = {'\0', };

  int numbers[ARRAY_SIZE] = {'\0', };

  if (fp == NULL)
    return -1;

  while (!feof(fp)) {
    // Initialization
    memset(buff, '\0', BUFF_SIZE);
 
    // Read one line
    ret = fscanf(fp, "%[^\n]", buff);
    fgetc(fp);

    if (strlen(buff) < 1)
      break;

    // Atoi
    numbers[count] = atoi(buff);

    count++;
  }

  // XXX : TODO
  double av = 0.0f, va = 0.0f;
  av = average(numbers, count);
  va = variance(numbers, count, av);

  printf("average %lf\n", av);
  printf("average %lf\n", va);

  return count;
}

int main(int argc, const char *argv[])
{
  FILE *fp = NULL;
  int ret = 0;

  /* Argc Exception */
  if (argc < 2) {
    printf("[Fail] Argc < 2.. \n");
    return 0;
  }

  // Open target file
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("[Fail] Open error! \n");
    return 0;
  }

  ret = analytics(fp);
  
  return 0;
}

