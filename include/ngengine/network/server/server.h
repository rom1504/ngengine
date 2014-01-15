#ifndef ENGINE_UTILS_NETWORK_SERVER_SERVER_H
#define ENGINE_UTILS_NETWORK_SERVER_SERVER_H

#include <ngengine/network/server/client.h>

#include <netinet/in.h>
#include <sys/socket.h>

namespace nge {
namespace network {
namespace server {

  class Server {

    public:

      Server(unsigned short port);
      ~Server();

      void listen(unsigned int nb_connections);

      Client *accept(); // appel bloquant


    private:

      unsigned short _port;

      int _socket;
      struct sockaddr_in _sockaddr;
  };

}
}
}

#endif
