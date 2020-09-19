#include "Client.h"

#include "ui/MainWindow.h"
#include "ui/ConnectDialog.h"

namespace client {
Client::Client(ui::ConnectDialog &connectDialog, ui::MainWindow &mainWindow)
    : connectDialog_(connectDialog), mainWindow_(mainWindow) {
}

void Client::start() {
    mainWindow_.show();
    connectDialog_.show();
}
}  // namespace client
