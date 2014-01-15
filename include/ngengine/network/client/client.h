#ifndef ENGINE_UTILS_NETWORK_CLIENT_CLIENT_H
#define ENGINE_UTILS_NETWORK_CLIENT_CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ngengine/network/client_interface.h>

namespace nge {
namespace network {
namespace client {

  class Client : public ClientInterface {

    public:

      Client(const char *server_name, unsigned short port);
      ~Client();
      
      bool connect();

      virtual int32_t write(const void *p, unsigned int maxsize);
      virtual int32_t read(void *p, unsigned int maxsize);

    private:

      char *_server_name;
      unsigned short _port;

      int _socket;
      struct sockaddr_in _server_sockaddr;
      struct hostent *_serverHostEnt;
  };

}
}
}

#endif
