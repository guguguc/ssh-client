#include "ssh.h"
#include "utils.h"

const std::string HOST = "172.30.84.59";
const std::string USER = "gugugu";
const std::string PASSWD = "0518";

int main() {
  try {
    libssh::SSHClient client(HOST, USER, PASSWD);
    if (!client.connect()) {
      throw std::runtime_error("Failed to connect!");
    }
    std::string out;
    if (!client.execute("ps aux", out)) {
      throw std::runtime_error("Failed to execute command");
    }
    std::cout << out << "\n";
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
  return 0;
}