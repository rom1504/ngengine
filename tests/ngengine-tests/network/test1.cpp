#include <ngengine-tests/test.h>
#include <stdio.h>
#include <ngengine/network/network.h>
#include <pthread.h>
#include <unistd.h>

namespace tests {
namespace network {

void *thread_server(void *data)
{
  bool *server_ok = (bool *) data;

  nge::network::server::Server server(5666);
  nge::network::server::Client *c;

  server.listen(1);

  *server_ok = true;

  c = server.accept();

  char t = 42;

  c->write(&t, 1);
  c->read(&t, 1);

  if(t != 73) {
    printf("server: wrong value received : %d\n", (int) t);
    exit(1);
  }
  else;

  delete c;

  return NULL;
}

void *thread_client(void *data)
{
  bool *server_ok = (bool *) data;

  while(!(*server_ok)) {
    usleep(30 * 1000);
  }

  nge::network::client::Client *c = new nge::network::client::Client("127.0.0.1", 5666);

  if(!c->connect()) {
    printf("Unable to connect to port 5666\n");
    exit(1);
  }
  else;

  char t;
  
  c->read(&t, 1);

  if(t != 42) {
    printf("client: wrong value received: %d\n", (int) t);
    exit(1);
  }
  else;

  t = 73;
  c->write(&t, 1);

  delete c;
  
  return NULL;
}

void test1()
{
  pthread_t tc, ts; // thread client/server 
  bool server_ok = 0;

  pthread_create(&ts, NULL, thread_server, &server_ok);
  pthread_create(&tc, NULL, thread_client, &server_ok);

  pthread_join(ts, NULL);
  pthread_join(tc, NULL);

  printf("success\n");
}

}
}
