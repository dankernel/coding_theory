#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 128
#define ARRAY_SIZE 128

#define MAX_LOOP 0xFFFF
#define MAX_BUFF 0x00FF

int read_number(FILE *fp, int *buff1, int *buff2)
{
  int i = 0, ret = 0;

  if (fp == NULL)
    return -1;

  i = 0;
  while (!feof(fp)) {
 
    // Read one line
    ret = fscanf(fp, "%d %d", &buff1[i], &buff2[i]);
    fgetc(fp);
    
    i++;
  }

  return i;
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

int deviation(int *arr, const double avr, int size)
{
  if (arr == NULL)
    return -1;

  int i = 0;

  if (arr == NULL)
    return 0;

  while (i < size) {
    arr[i] -= avr;
    i++;
  }

  return 0;
}

int deviation_x(int *arr1, int *arr2, int size)
{
  if (arr1 == NULL || arr2 == NULL)
    return -1;

  int i = 0;

  while (i < size) {
    arr1[i] *= arr2[i];
    i++;
  }

  return 0;
}

int deviation_sum(int *arr1, int size)
{
  if (arr1 == NULL)
    return -1;

  int i = 1;

  while (i < size) {
    arr1[0] += arr1[i];
    i++;
  }

  return 0;
}
int main(int argc, const char *argv[])
{
  FILE *fp = NULL;
  int size = 0;

  int buff1[BUFF_SIZE] = {'\0', };
  int buff2[BUFF_SIZE] = {'\0', };
 
  double ave[2] = {0.0f, 0.0f};
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

  memset(buff1, '\0', BUFF_SIZE);
  memset(buff2, '\0', BUFF_SIZE);

  size = read_number(fp, buff1, buff2);
  size--;

  // 평균
  ave[0] = average(buff1);
  ave[1] = average(buff2);
 
  // 편차 => buffx
  deviation(buff1, ave[0], size);
  deviation(buff2, ave[1], size);

  // 편차곱 => buff1
  deviation_x(buff1, buff2, size);

  // 편차합
  deviation_sum(buff1, size);

  printf("공분산 : %lf \n", (double)(buff1[0] / (size - 1)));

  return 0;
}

