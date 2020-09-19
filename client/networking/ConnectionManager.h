#pragma once

#include <memory>
#include <string>

namespace networking {
class Connection;

class ConnectionManager {
  public:
    ConnectionManager();
    ~ConnectionManager();

    [[nodiscard]] std::shared_ptr<Connection> connect(const std::string &server, unsigned short port);

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
}  // namespace networking