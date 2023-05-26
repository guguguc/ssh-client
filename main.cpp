#include "ssh.h"
#include "utils.h"

int main()
{
  libssh::SSHClient client("172.19.234.41", "gugugu", "0518");
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
  std::cout << "size: " << out.size() << "\n";
  std::cout << Utils::String2Hex(out) << "\n";
  return 0;
}