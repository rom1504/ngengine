#include <ngengine/network/server/server.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace nge::network;
using namespace nge::network::server;


Server::Server(unsigned short port)
{
  _port = port;
  memset(&_sockaddr, 0, sizeof(_sockaddr));
 
  _sockaddr.sin_port = htons(port);
  _sockaddr.sin_family = AF_INET;
  _sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);  

  if ((_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("Impossible d'ouvrir la socket\n");
    exit(0);
  }

  /* bind serveur - socket */
  if(bind(_socket,(struct sockaddr *)&_sockaddr,sizeof(_sockaddr)) != 0) {
    printf("Impossible de binder la socket. Relancez le serveur dans 30 secondes.\n");
    exit(-1);
  }
  else;
}

Server::~Server()
{
  ::close(_socket);
}

void Server::listen(unsigned int nb_connections)
{
  ::listen(_socket, nb_connections);
}

Client *Server::accept()
{
  unsigned int size = sizeof(_sockaddr);
  struct sockaddr client_sockaddr;

  int client_socket = ::accept(_socket,
                             (struct sockaddr *)&client_sockaddr,
                             &size);

  Client *client = nullptr;

  if(client_socket > 0) {
    client = new Client(client_socket);
  }
  else;

  return client;
}

