#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 128
#define ARRAY_SIZE 128

int valid_char(const char *str)
{
  int len = 0, i = 0;
  int gap = 0;

  if (str == NULL)
    return -1;

  len = strlen(str);
  
  while (i < len) {
    if (str[i] == ' ' || str[i] == '\t')
      gap++;
    i++;
  }

  return gap;
}

int is_token(const char *str, const char *tok)
{
  int ret = 0;
  const char *start = NULL, *end = NULL;
  int str_len = 0, tok_len = 0, i = 0, j = 0;
  char tmp[BUFF_SIZE] = {'\0', };

  if (str == NULL || tok == NULL)
    return -1;

  str_len = strlen(str);
  tok_len = strlen(tok);

  start = str;
  for (i = 0; i < str_len; i++) {
    for (j = 0; j < tok_len; j++) {

      if (tok[j] == str[i]) {

        end = str + i;

        strncpy(tmp, start, end - start);
        tmp[end - start] = '\0';
        /* printf("\"%s\" \n", tmp); */
        /* printf("\'%c\'\n", tok[j]); */

        printf("\"%s\" \'%c\' ", tmp, tok[j]);

        start = str + i + 1;

      }
    }
  }

  return ret;
}

int *read_line(FILE *fp)
{
  int i = 0, count = 0, ret = 0;
  char buff[BUFF_SIZE] = {'\0', };
  char *tok = NULL;

  char token[] = "\t ()<>[]{},.!@#$%^&*_+-=;\n";

  if (fp == NULL)
    return NULL;

  while (!feof(fp)) {
    // Initialization
    memset(buff, '\0', BUFF_SIZE);
 
    // Read one line
    ret = fscanf(fp, "%[^\n]", buff);
    fgetc(fp);

    if (valid_char(buff) != strlen(buff))
      is_token(buff, token);
    else
      printf("XXXXXXXXXXXXXXXXXXXX\n");

    count++;
  }

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

  arr = read_line(fp);

  return 0;
}

