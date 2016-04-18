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

int is_token(const char c, const char *tok)
{
  int i = 0;

  if (tok == NULL)
    return -1;

  while (tok[i]) {
    if (tok[i++] == c)
      return 1;
  }

  return 0;
}

int tokenization(const char *str, const char *tok, char *result[])
{
  int ret = 0;
  const char *start = NULL, *end = NULL;
  int str_len = 0, tok_len = 0, i = 0, j = 0;
  int cp_index = 0;

  if (str == NULL || tok == NULL || result == NULL)
    return -1;

  str_len = strlen(str);
  tok_len = strlen(tok);

  i = 0;
  while (str[i] == ' ' || str[i] == '\t') {
    i++;
  }

  start = str;
  for (; i < str_len; i++) {
    for (j = 0; j < tok_len; j++) {

      // Lookup token
      if (tok[j] == str[i]) {

        // End
        end = &str[i];

        if (end == start) {
          strncpy(result[cp_index], end, 1);
          strcat(result[cp_index], "\0");
          printf("0= %s\n", result[cp_index++]);
        } else { 

          // Copy string
          strncpy(result[cp_index], start, end - start);
          strcat(result[cp_index], "\0");
          printf("1= %s\n", result[cp_index++]);

          strncpy(result[cp_index], end, 1);
          strcat(result[cp_index], "\0");
          printf("2= %s\n", result[cp_index++]);
        }

        // Next
        start = end + 1;
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
    if (result[i][0] != ' ')
      printf("[%d]%s\n", i, result[i]);

    i++;
  }

  return 0;
}

int is_keyword(const char *str, const char *keyword[])
{
  int i = 0;
  if (str == NULL || keyword == NULL)
    return -1;

  i = 0;
  while (keyword[i][0] != '\0' && i < ARRAY_SIZE) {
    if (!strcmp(keyword[i], str))
      return 1;

    i++;
  }

  return 0;
}

int print_line(char *line[])
{
  int i = 0;
  while (line[i][0] != '\0' && i < ARRAY_SIZE)
    printf("%s ", line[i++]);

  printf("\n");

  return 0;
}

int cp_valid(char *result[], const char *keyword[])
{
  int i = 0, j = 0;
  char *valid[ARRAY_SIZE] = {'\0', };

  if (result == NULL)
    return -1;

  // Allocation valid array
  i = 0;
  while (i < ARRAY_SIZE) {
    valid[i] = malloc(sizeof(char *) * ARRAY_SIZE);
    memset(valid[i++], '\0', ARRAY_SIZE);
  }

  // Copy valid keyword to tmp[][]
  i = 0, j = 0;
  printf("\n");
  while (result[i][0] != '\0' && i < ARRAY_SIZE) {
    if (result[i][0] != ' ') {
      strcpy(valid[j++], result[i]);
    }
    i++;
  }

  // Function
  if (is_keyword(valid[0], keyword) && valid[2][0] == '(') {
    printf("function\n");
    print_line(result);
  }

  if (is_keyword(valid[0], keyword) && valid[2][0] == '=') {
    printf("variable\n");
    print_line(result);
  }
  /*
  j = 0;
  while (tmp[j][0] != '\0' && i < ARRAY_SIZE) {
    printf("%s\n", tmp[j]);
    if (is_keyword(tmp[j], keyword))
      printf("keyword!!!\n");
    j++;
  }
  */

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

  char token[] = "\t ()<>[]{},.!@#$%^&*_+-=;\'\"\n";
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

    // Tokenization one line
    if (valid_char(buff) != strlen(buff))
      tokenization(buff, token, result);

    char *keyword[ARRAY_SIZE] = {"int", "char", "long", "double", "\0"};

    // TODO ...
    print_line(result);
    /* cp_valid(result, keyword); */
  }

  i = 0;
  while (i < ARRAY_SIZE)
    free(result[i++]);


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

