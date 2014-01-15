#include <ngengine/network/server/client.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace nge::network;
using namespace nge::network::server;

Client::Client(int socket)
{
  _socket = socket;
}

Client::~Client()
{
  
}

int32_t Client::write(const void *p, unsigned int maxsize)
{
  return ::write(_socket, p, maxsize);
}

int32_t Client::read(void *p, unsigned int maxsize)
{
  return ::read(_socket, p, maxsize);
}

