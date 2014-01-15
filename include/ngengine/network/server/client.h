#ifndef ENGINE_UTILS_NETWORK_SERVER_CLIENT_H
#define ENGINE_UTILS_NETWORK_SERVER_CLIENT_H

#include <netinet/in.h>
#include <sys/socket.h>
#include <ngengine/network/client_interface.h>

#include <cstdint>
#include <string>

namespace nge {
namespace network {
namespace server {

  class Client : public ClientInterface {

    public:

      Client(int socket);
      ~Client();

      virtual int32_t write(const void *p, unsigned int maxsize);
      virtual int32_t read(void *p, unsigned int maxsize);

    private:

      int _socket;
  };

}
}
}

#endif
