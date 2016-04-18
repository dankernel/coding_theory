#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 128

/*
 * return rtrim sting address
 * @ret : return trim_buff
 * @s : target string
 */
char *rtrim(char *ret, const char *s)
{
  int p = 0, q = 0;

  if (ret == NULL || s == NULL)
    return NULL;

  // Copy to trim buff
  while (s[q] != '\0') {
    if (!isspace(s[q]))
      ret[p++] = s[q];
    q++;
  }

  // End
  ret[p] = '\n';
  ret[p + 1] = ret[BUFF_SIZE] = '\0';
  return ret;
}

int check_loc(const char *str, int len)
{
  int i = 0, count = 0;

  if (str == NULL || len <= 0)
    return -1;

  while (i < len) {
    if ((str[i] == ';' || str[i] == '}') && str[i + 1] == '\n')
      return i;
    i++;
  }
  return -1;
}

int loc_counter(FILE *fp)
{
  int i = 0, count = 0, ret = 0;
  char buff[BUFF_SIZE] = {'\0', };
  char trim_buff[BUFF_SIZE] = {'\0', };

  if (fp == NULL)
    return -1;

  while (!feof(fp)) {
    // Initialization
    memset(buff, '\0', BUFF_SIZE);
    memset(trim_buff, '\0', BUFF_SIZE);
 
    // Read one line
    ret = fscanf(fp, "%[^\n]", buff);
    fgetc(fp);

    // Trim
    rtrim(trim_buff, buff) == NULL;
    printf("= %s", trim_buff);

    // Check LOC
    if (0 <= (ret = check_loc(trim_buff, BUFF_SIZE)))
      count++;
  }
 
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

  ret = loc_counter(fp);
  printf("Count : %d \n", ret);
  
  return 0;
}

