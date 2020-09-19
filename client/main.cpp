#include "Client.h"
#include "networking/ConnectionManager.h"
#include "ui/ConnectDialog.h"
#include "ui/MainWindow.h"

#include <QApplication>
#include <boost/di.hpp>
#include <spdlog/spdlog.h>

namespace di = boost::di;

int main(int argc, char **argv) {
    spdlog::set_level(spdlog::level::trace);
    QApplication app(argc, argv);

    auto injector = di::make_injector();
    auto client   = injector.create<client::Client>();
    client.start();

    return app.exec();
}