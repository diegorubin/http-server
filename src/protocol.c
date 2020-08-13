#include "protocol.h"

int read_method(FILE *input) {
  int lexeme_position = 0;
  char method_str[10];
  char c;

  while (!isspace(c = getc(input))) {
    method_str[lexeme_position++] = c;
  }
  method_str[lexeme_position] = '\0';
  ungetc(c, input);

  if (strcmp("GET", method_str) == 0)
    return GET;

  return NOT_IMPLEMENTED;
}

void read_path(FILE *input, char *dest) {
  int lexeme_position = 0;
  char lexeme[1024];
  char c;

  while (!isspace(c = getc(input))) {
    lexeme[lexeme_position++] = c;
  }
  lexeme[lexeme_position] = '\0';
  strcpy(dest, lexeme);
}

void read_version(FILE *input, char *dest) {
  int lexeme_position = 0;
  char lexeme[50];
  char c;
  while (!isspace(c = getc(input))) {
    lexeme[lexeme_position++] = c;
  }
  lexeme[lexeme_position] = '\0';
  strcpy(dest, lexeme);
}

void skip_whitespace(FILE *input) {
  char c;
  while ((isspace(c = getc(input))))
    ;
  ungetc(c, input);
}

request_t *parse(FILE *input) {
  request_t *request = (request_t *)malloc(sizeof(request_t));

  request->method = read_method(input);
  skip_whitespace(input);
  read_path(input, request->path);
  skip_whitespace(input);
  read_version(input, request->protocol_version);

  return request;
}
