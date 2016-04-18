#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 128
#define ARRAY_SIZE 128

#define MAX_LOOP 0xFFFF
#define MAX_BUFF 0x00FF

int *read_number(FILE *fp)
{
  int i = 0, count = 0, ret = 0;
  int *numbers = NULL;
  char buff[BUFF_SIZE] = {'\0', };
  char *tok = NULL;

  if (fp == NULL)
    return NULL;

  numbers = malloc(sizeof(int*) * ARRAY_SIZE);

  while (!feof(fp)) {
    // Initialization
    memset(buff, '\0', BUFF_SIZE);
 
    // Read one line
    ret = fscanf(fp, "%[^\n]", buff);
    fgetc(fp);

    numbers[count] = atoi(buff);

    count++;
  }

  return numbers;
}

double average(const int *arr)
{
  if (arr == NULL)
    return -1;

  double ret = 0.0f, sum = 0.0f;
  int i = 0;
  int size = 0;

  if (arr == NULL)
    return 0;

  while (arr[size]) {
    sum += arr[i++];
    size++;
  }

  ret = sum / size;

  return ret;
}

double variance(const int *arr, const double average)
{
  double ret = 0.0f, sum = 0.0f;
  int i = 0;

  if (arr == NULL)
    return 0;

  while (arr[i]) {
    sum += (arr[i] - average) * (arr[i] - average);
    i++;
  }

  ret = sum / i;

  return ret;
}

int main(int argc, const char *argv[])
{
  FILE *fp = NULL;
  int *arr = 0;
  double ave = 0.0f;
  double var = 0.0f;

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

  arr = read_number(fp);

  ave = average(arr);
  var = variance(arr, ave);

  printf("ave : %lf \n", ave);
  printf("var : %lf \n", var);

  return 0;
}

