#include "ConnectDialog.h"

#include "model/User.h"
#include "networking/ConnectionManager.h"
#include "networking/Connection.h"
#include "networking/Chat.h"
#include "ui_ConnectDialog.h"

#include <QErrorMessage>

namespace client::ui {
ConnectDialog::ConnectDialog(networking::ConnectionManager &connectionManager)
    : connectionManager_(connectionManager) {
    ui_ = std::make_unique<Ui::ConnectDialog>();
    ui_->setupUi(this);
}

ConnectDialog::~ConnectDialog() = default;

void ConnectDialog::connect() {
    try {
        auto server = ui_->serverInput->text().toStdString();
        auto port   = static_cast<unsigned short>(ui_->portInput->value());

        std::shared_ptr<networking::Connection> connection = connectionManager_.connect(server, port);

        auto username = ui_->usernameInput->text();
        auto chat = networking::Chat::init(connection, username.toStdString());
        emit chatConnected(std::move(chat), username);
        accept();

    } catch(const std::exception &ex) {
        displayError(ex.what());
    }
}

void ConnectDialog::cancel() {
    reject();
}

void ConnectDialog::displayError(const QString &reason) {
    auto *msg = new QErrorMessage(this);
    msg->showMessage("Error: " + reason);
}
}  // namespace client::ui