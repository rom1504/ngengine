#ifndef ENGINE_UTILS_NETWORK_CLIENTINTERFACE_H
#define ENGINE_UTILS_NETWORK_CLIENTINTERFACE_H

#include <cstdint>

namespace nge {
namespace network {

  class ClientInterface {

    public:

      virtual ~ClientInterface();

      virtual int32_t write(const void *p, unsigned int maxsize) = 0;
      virtual int32_t read(void *p, unsigned int maxsize) = 0;
  };

}
}

#endif

