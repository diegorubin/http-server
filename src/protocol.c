#include "protocol.h"

char *reasons[] = {
    "OK",
    "NOT FOUND",
};

unsigned statuses[] = {
    200,
    404,
};

#define separator "\n"

/**
 * Response = Status-Line
 *            *(( general-header
 *             | response-header
 *             | entity-header ) CRLF)
 *            CRLF
 *            [ message-body ]
 * Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
 */
void send_response(int clientfd, response_t *response) {

  char status_line[256];
  bzero(status_line, 256);
  sprintf(status_line, "%s %u %s\n", response->protocol_version,
          response->status, response->reason);
  write(clientfd, status_line, strlen(status_line));

  if (response->body != NULL) {
    char content_length[20];
    sprintf(content_length, "Content-Length: %lu\n", strlen(response->body));
    write(clientfd, content_length, strlen(content_length));
  }

  write(clientfd, separator, strlen(separator));

  if (response->body != NULL) {
    write(clientfd, response->body, strlen(response->body));
  }
}

void read_reason(unsigned status, char *dest) {
  for (unsigned i = 0; i < (sizeof(statuses) / sizeof(unsigned)); i++) {
    if (statuses[i] == status) {
      strcpy(dest, reasons[i]);
    }
  }
}

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
