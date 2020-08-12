#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "worker.h"

const int SERVER_PORT = 8080;
const int BACKGROUND_CONNECTIONS = 10;
const int NUMBER_OF_WORKERS = 4;

int main() {

  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  int reuseopt = 1;

  if (socketfd < 0) {
    fprintf(stderr, "Could not open socket!\n");
    return 1;
  }

  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &reuseopt, sizeof(int));

  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(SERVER_PORT);

  int bindret =
      bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  if (bindret < 0) {
    fprintf(stderr, "Could not bind to address!\n");
    return 2;
  }

  listen(socketfd, BACKGROUND_CONNECTIONS);
  printf("Server started at port %d.\n", SERVER_PORT);

  init_workers(NUMBER_OF_WORKERS);

  for (;;) {
    struct sockaddr_in client_address;
    unsigned int clientlen = sizeof(client_address);

    int clientfd =
        accept(socketfd, (struct sockaddr *)&client_address, &clientlen);

    printf("connection into pid %d\n", getpid());

    ssize_t result;
    char buffer[1024];
    char input[2048];

    bzero(input, 2048);
    bzero(buffer, 1024);
    while ((result = read(clientfd, buffer, 1024)) > 0) {
      printf("< %s", buffer);
      if (buffer[0] == '\r') {
        break;
      }
      strcat(input, buffer);
      bzero(buffer, 1024);
    }

    FILE *request_raw = fmemopen(input, strlen(input), "r");
    request_t *request = parse(request_raw);
    fclose(request_raw);

    char response[2048];
    bzero(response, 2048);
    sprintf(response, "%d %s %s\n", request->method, request->path,
            request->protocol_version);

    printf("> %s", response);

    free(request);
    write(clientfd, response, strlen(response));
    close(clientfd);
  }

  close(socketfd);

  return 0;
}
