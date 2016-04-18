#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFF_SIZE 128
#define ARRAY_SIZE 32

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

int is_token(const char *str, const char *tok, char *result[])
{
  int ret = 0;
  const char *start = NULL, *end = NULL;
  int str_len = 0, tok_len = 0, i = 0, j = 0;
  int cp_index = 0;

  if (str == NULL || tok == NULL || result == NULL)
    return -1;

  str_len = strlen(str);
  tok_len = strlen(tok);

  start = str;
  for (i = 0; i < str_len; i++) {
    for (j = 0; j < tok_len; j++) {

      // Lookup token
      if (tok[j] == str[i]) {

        // End
        end = str + i;

        // Copy string
        if (end - start < 2) {
          strncpy(result[cp_index], &tok[j], 1);
          strcat(result[cp_index++], "\0");
        } else {
          strncpy(result[cp_index], start, end - start);
          strcat(result[cp_index++], "\0");

          strncpy(result[cp_index], &tok[j], 1);
          strcat(result[cp_index++], "\0");
        }

        // Next
        start = str + i + 1;
      }
    }
  }

  return ret;
}

int print_valid(char *result[])
{
  int i = 0;
  if (result == NULL)
    return -1;

  // Print All
  i = 0;
  printf("\n");
  while (result[i][0] != '\0' && i < ARRAY_SIZE) {
    printf("[%d]%s\n", i, result[i]);
    i++;
  }

  return 0;
}

int print_keyword(char *arr[], char *keyword[])
{
  int i = 0, j = 0;
  if (arr == NULL || keyword == NULL)
    return -1;

  // Print All
  i = 0, j = 0;
  printf("\n");
  while (arr[i][0] != '\0' && i < ARRAY_SIZE) {
    j = 0;
    
    printf("= \"%10s\" \n", arr[i]);
    while (keyword[j][0] != '\0' && j < ARRAY_SIZE) {

      if (arr[i][0] != ' ' && !strcmp(arr[i], keyword[j])) {
        printf("> %10s\n", "keyword");
        break;
      } else {
        /* printf("_ [%d]%s\n", i, arr[i]); */
      }

      j++;
    }

    i++;
  }
  return 0;
}

int read_line(FILE *fp)
{
  int i = 0;
  char buff[BUFF_SIZE] = {'\0', };

  char token[] = "\t ()<>[]{},.!@#$%^&*_+-=;\n";
  char *result[ARRAY_SIZE] = {'\0', };

  // Exception
  if (fp == NULL)
    return -1;

  // Allocation array
  i = 0;
  while (i < ARRAY_SIZE)
    result[i++] = malloc(sizeof(char *) * ARRAY_SIZE);

  while (!feof(fp)) {
    // Initialization
    memset(buff, '\0', BUFF_SIZE);

    // Initialization result array
    i = 0;
    while (i < ARRAY_SIZE)
      memset(result[i++], '\0', BUFF_SIZE);
 
    // Read one line
    fscanf(fp, "%[^\n]", buff);
    fgetc(fp);

    // Token
    if (valid_char(buff) != strlen(buff))
      is_token(buff, token, result);

    char *keyword[ARRAY_SIZE] = {"int", "char", "long", "double", "\0"};

    print_keyword(result, keyword);

    // Print All
    /* print_valid(result); */
  }

  return 0;
}

int main(int argc, const char *argv[])
{
  FILE *fp = NULL;

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

  read_line(fp);

  return 0;
}

