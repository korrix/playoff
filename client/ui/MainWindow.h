#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace networking {
class Chat;
}

namespace client::ui {
class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    MainWindow();

  public slots:
    void chatConnected(std::shared_ptr<networking::Chat> chat);
    void joinChannel();
    void inviteUser();
    void channelChanged(int index);

  private:
    std::unique_ptr<Ui::MainWindow> ui_;
    std::shared_ptr<networking::Chat> chat_;

    void openChannelTab(const QString& channelName);
    void displayError(const QString &reason);
};
}  // namespace ui