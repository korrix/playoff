#pragma once

#include <QDialog>

namespace networking {
class ConnectionManager;
class Chat;
}

namespace Ui {
class ConnectDialog;
}

namespace client::ui {
class ConnectDialog : public QDialog {
    Q_OBJECT
  public:
    ConnectDialog(networking::ConnectionManager& connectionManager);
    ~ConnectDialog() override;

  public slots:
    void connect();
    void cancel();

  signals:
    void chatConnected(std::shared_ptr<networking::Chat>);

  private:
    networking::ConnectionManager& connectionManager_;
    std::unique_ptr<Ui::ConnectDialog> ui_;

    void displayError(const QString& reason);
};
}