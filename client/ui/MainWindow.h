#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace networking {
class Chat;
}

class QTimer;
class QListWidget;

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
    QTimer *updateTimer;
    void pullChat();

    std::unique_ptr<Ui::MainWindow> ui_;
    std::shared_ptr<networking::Chat> chat_;

    void openChannelTab(const QString& channelName, QString invitation = {});
    void displayError(const QString &reason);

    std::unordered_map<int, QString> roomNames;
    std::unordered_map<QString, QListWidget*> roomMessages;
};
}  // namespace ui