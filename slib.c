#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>

#include <signal.h>
#include <strings.h>

#define DIE(msg) perror(msg); exit(1);

int broadcast_setup (char *);
int open_listening_port(void);
int has_hole (void);

int broadcast_setup (char * name) {

  int smoothied;
  struct hostent * router;
  struct sockaddr_in router_addr;

  if ((router = gethostbyname(name)) == NULL) {
    DIE ("gethostbyname");
  }

  bzero((char *) &router_addr, sizeof(router_addr));
  router_addr.sin_family = AF_INET;

  bcopy((char *) router->h_addr,
    (char *) &router_addr.sin_addr.s_addr,
    router->h_length);

  router_addr.sin_port = htons(42170);
  if ((smoothied = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    DIE("socket");
  }
  if (connect (smoothied, (struct sockaddr *)
        &router_addr, sizeof(router_addr)) == -1) {
    DIE("connect");
  }

  return smoothied;

}

int open_listening_port() {
  struct sockaddr_in server_addr;
  int socket_pid;

  if ((socket_pid =
    socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      DIE("socket");
  }

  bzero((char *) &server_addr, sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(42170);

  if ((bind(socket_pid,
    (struct sockaddr *) &server_addr,
    sizeof(server_addr) == -1))) {
      DIE ("bind");
  }

  if ((listen(socket_pid, 40) == -1)) {
    DIE("listen");
  }

  return socket_pid;
}

int has_hole () {
  FILE *fp = fopen ("hole", "r");
  if (fp == NULL) {
      mkdir ("hole", S_IRWXU);
      return 0;
  }
  else
    return 1;
};
