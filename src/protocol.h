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

typedef enum {
  NOT_IMPLEMENTED = -1,
  GET = 1,
} method_t;

typedef struct response_t {
  unsigned status;
  char description[50];
  char protocol_version[8];
} response_t;

typedef struct request_t {
  method_t method;
  char path[1024];
  char protocol_version[8];
} request_t;

request_t *parse(FILE *input);

#endif
