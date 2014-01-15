#include <ngengine-tests/test.h>
#include <stdio.h>

namespace tests {
  namespace network {
    void test1();
  } 
}

void start_test(const char *name, void (*fn_test)(void))
{
  printf("Begining of the test '%s'\n", name);

  fn_test();

  printf("End of the test '%s'\n", name);

}

int main(int argc, char **argv)
{
  printf("=====================================\n");
  printf("  Nativ' Games Engine Unitary Tests  \n");
  printf("=====================================\n");

  start_test("network/test1", tests::network::test1);

  return 0;
}

