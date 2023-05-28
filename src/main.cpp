#include "ssh.h"
#include "utils.h"
#include <iostream>
#include <string>

int main()
{
  std::string host, user, passwd;

  std::cout << "Enter HOST: ";
  std::cin >> host;
  std::cout << "Enter USER: ";
  std::cin >> user;
  std::cout << "Enter PASSWD: ";
  std::cin >> passwd;

  libssh::SSHClient client(host, user, passwd);
  if (!client.connect())
  {
    std::cerr << "Failed to connect!\n";
    return 1;
  }

  std::cout << "Enter command (or 'exit' to quit): ";
  while (true)
  {
    std::string command;
    std::cout << "client: ";
    std::getline(std::cin, command);
    if (command == "exit")
    {
      break;
    }

    std::string out;
    if (!client.execute(command, out))
    {
      std::cerr << "Failed to execute command\n";
    }
    else
    {
      std::cout << "server:\n" << out;
    }
  }

  return 0;
}
