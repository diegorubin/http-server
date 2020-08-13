/**
 * Example of request
 * METHOD path PROTOCOL_VERSION
 * HEADERS
 */
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {
  NOT_IMPLEMENTED = -1,
  GET = 200,
} method_t;

typedef struct response_t {
  unsigned status;
  char reason[50];
  char protocol_version[8];
  char *body;
} response_t;

typedef struct request_t {
  method_t method;
  char path[1024];
  char protocol_version[8];
} request_t;

request_t *parse(FILE *input);

void read_reason(unsigned status, char *dest);
void respond(int clientfd, response_t *response);
void send_response(int clientfd, response_t *response);

#endif
