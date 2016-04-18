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

/*
 * Tokenizing origin data
 * @str : origin string
 * @tok : tokens
 * @result : result
 */
int tokenization(const char *str, const char *tok, char *result[])
{
  int ret = 0,  str_len = 0, tok_len = 0, i = 0, j = 0, cp_index = 0;
  const char *start = NULL, *end = NULL;

  if (str == NULL || tok == NULL || result == NULL)
    return -1;

  str_len = strlen(str);
  tok_len = strlen(tok);

  // Remove whitespace
  i = 0;
  while (str[i] == ' ' || str[i] == '\t') {
    i++;
  }

  // tokenizing
  start = str + i;
  for (; i < str_len; i++) {
    for (j = 0; j < tok_len; j++) {

      // Lookup token
      if (tok[j] == str[i]) {

        // End
        end = &str[i];

        if (end == start) {
          strncpy(result[cp_index], end, 1);
          strcat(result[cp_index++], "\0");
        } else { 
          strncpy(result[cp_index], start, end - start);
          strcat(result[cp_index++], "\0");

          strncpy(result[cp_index], end, 1);
          strcat(result[cp_index++], "\0");
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

int is_keyword(const char *str, char *keyword[])
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
    printf("%s", line[i++]);

  printf("\n");

  return 0;
}

/*
 * Copy onliy valid string
 */
int cp_valid(char *valid[], char *str[])
{
  int i = 0, j = 0;

  if (valid == NULL || str == NULL)
    return -1;

  // Copy valid keyword to tmp[][]
  i = 0, j = 0;
  while (str[i][0] != '\0' && i < ARRAY_SIZE) {
    if (str[i][0] != ' ' && str[i][0] != '\t') {
      strcpy(valid[j++], str[i]);
    }
    i++;
  }

  return 0;
}

/*
 * Print variable and function string
 * @valid : valid string
 * @keyword : data typa
 * @str : origin string
 */
int print_variable(char *valid[], char *keyword[], char *str[], int depth)
{
  // Function
  if (is_keyword(valid[0], keyword) && valid[2][0] == '(') {
    printf("function : %s : ", valid[0]);
    print_line(str);
  }

  // Variable
  if (is_keyword(valid[0], keyword) && (valid[2][0] == '=' || valid[2][0] == ';')) {

    if (depth == 0) 
      printf("local variable : %s : ", valid[0]);
    else if (0 < depth) 
      printf("global variable : %s : ", valid[0]);

    print_line(str);
  }

  return 0;
}

int check_depth(char *str[])
{
  int ret = 0, i = 0;

  if (str == NULL)
    return -1;

  // Count depth
  i = 0;
  while (str[i][0] != '\0' && i < ARRAY_SIZE) {
    if (str[i][0] == '{')
      ret++;
    if (str[i][0] == '}')
      ret--;

    i++;
  }

  return ret;
}

int read_line(FILE *fp)
{
  // Exception
  if (fp == NULL)
    return -1;

  int i = 0, depth = 0;

  char buff[BUFF_SIZE] = {'\0', };
  char *result[ARRAY_SIZE] = {'\0', };
  char *valid[ARRAY_SIZE] = {'\0', };

  char *keyword[ARRAY_SIZE] = {"int", "char", "long", "double", "\0"};
  char token[] = "\t ()<>[]{},.!@#$%^&*+-=;\'\"\n";

  // Allocation array
  i = 0;
  while (i < ARRAY_SIZE) {
    result[i] = malloc(sizeof(char *) * ARRAY_SIZE);
    valid[i] = malloc(sizeof(char *) * ARRAY_SIZE);
    i++;
  }

  // Read file
  while (!feof(fp)) {

    // Initialization
    i = 0;
    memset(buff, '\0', BUFF_SIZE);
    while (i < ARRAY_SIZE) {
      memset(result[i], '\0', ARRAY_SIZE);
      memset(valid[i], '\0', ARRAY_SIZE);
      i++;
    }
 
    // Read one line to buff
    fscanf(fp, "%[^\n]", buff);
    fgetc(fp);

    // Tokenization one line
    if (valid_char(buff) != strlen(buff))
      tokenization(buff, token, result);

    // Copy only valid string
    cp_valid(valid, result);

    // Check depth
    depth += check_depth(valid);

    // Print variable string
    print_variable(valid, keyword, result, depth);

  }

  // Free
  i = 0;
  while (i < ARRAY_SIZE) {
    free(result[i]);
    free(valid[i]);
    i++;
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

