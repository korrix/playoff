#include "Client.h"

#include "ui/ConnectDialog.h"
#include "ui/MainWindow.h"

namespace client {
Client::Client(ui::ConnectDialog &connectDialog, ui::MainWindow &mainWindow)
    : connectDialog_(connectDialog)
    , mainWindow_(mainWindow) {

    QObject::connect(&connectDialog_, &ui::ConnectDialog::chatConnected, &mainWindow_, &ui::MainWindow::chatConnected);
}

void Client::start() {
    mainWindow_.show();
    connectDialog_.show();
}
}  // namespace client
