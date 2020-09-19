#pragma once
#include <QObject>

namespace client {
namespace ui {
class ConnectDialog;
class MainWindow;
}

class Client {
  public:
    Client(ui::ConnectDialog &connectDialog, ui::MainWindow &mainWindow);

    void start();

  private:
    ui::ConnectDialog &connectDialog_;
    ui::MainWindow &mainWindow_;
};
}  // namespace client