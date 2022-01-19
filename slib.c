#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>

#include <signal.h>
#include <strings.h>

#define MAX 4096
#define DIE(msg) perror(msg); exit(1);

// declaration block //
// declaration block //

int broadcast_setup (char *);
int open_listening_port(void);
void accept_connection (int, char *);
void port_forward (int, char *);
int has_hole (void);
int open_public_socket (char *);
void com (int, int);

// declaration block //
// declaration block //

void com (int to, int from) {

  char buf[MAX];
  int r, i, j;

  r = read(to, buf, MAX);
  while (r > 0) {
    i = 0;
    while (i < r) {
      if ((j = write (from, buf+i, r-i)) == -1) {
        DIE ("write");
      }
      i+=j;
    }
    r = read(to, buf, 4096);
  }
  if (r == -1) {
    DIE("read");
  }

  shutdown (to, SHUT_RD);
  shutdown (from, SHUT_WR);

  close(to);
  close(from);

  exit(0);
}

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

void port_forward (int client_sock, char * name) {

  int pub_sock;
  pid_t priv_pid;

  pub_sock = open_public_socket (name);
  if ((priv_pid = fork () == -1)) {
    DIE("fork.");
  }
  if (priv_pid == 0)  {
  // com (pub_sock, client_sock);
  }
  else  {
  // com (client_sock, pub_sock);
  }



}

int open_public_socket (char * name) {

  int pub_sock;
  struct hostent *pub;
  struct sockaddr_in pub_addr;

  if ((pub = gethostbyname(name)) == NULL) {
    DIE("gethostbyname");
  }

  bzero ((char *) &pub_addr, sizeof(pub_addr));
  pub_addr.sin_family = AF_INET;

  bcopy ((char *)pub->h_addr,
    (char *) &pub_addr.sin_addr.s_addr,
    pub->h_length);

  pub_addr.sin_port = htons(42170);
  if ((pub_sock = socket(AF_INET,
      SOCK_STREAM, 0) == -1)) {
    DIE("socket");
  }

  if (connect(pub_sock, 
    (struct sockaddr *) &pub_addr,
    sizeof(pub_addr)) == -1) {
      DIE("connect.");
  }

  return pub_sock;
}

void accept_connection (int spid, char * name) {

  int local_sock;
  pid_t pid;

  if ((local_sock =
      accept(spid, NULL, NULL))) {
    DIE("accept");
  }

  if ((pid = fork()) == -1) {
    DIE("fork.");
  }

  if (pid == 0) {
    //forward_traffic ();
  }

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
