#include "ssh.h"
#include "utils.h"

int main()
{
  std::string host("172.30.84.59");
  std::string user("gugugu");
  std::string passwd("0518");
  libssh::SSHClient client(host, user, passwd);
  if (!client.connect())
  {
    std::cerr << "failed to connect!\n";
    return 1;
  }
  std::string out;
  bool ret = client.execute("ps aux", out);
  if (!ret)
  {
    std::cerr << "failed to execute cmd\n";
    return 1;
  }
  std::cout << out << "\n";
  // std::cout << "size: " << out.size() << "\n";
  // std::cout << Utils::String2Hex(out) << "\n";
  return 0;
}