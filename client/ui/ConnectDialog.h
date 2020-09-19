#pragma once

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

namespace client::ui {
class ConnectDialog : public QDialog {
    Q_OBJECT
  public:
    ConnectDialog();
    ~ConnectDialog() override;

  public slots:
    void connect();
    void cancel();

  private:
    std::unique_ptr<Ui::ConnectDialog> ui_;

    void displayError(const QString& reason);
};
}