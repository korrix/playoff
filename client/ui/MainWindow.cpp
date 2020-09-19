#include "MainWindow.h"

#include "networking/Chat.h"
#include "ui_MainWindow.h"
#include "ui_ChannelTab.h"

#include <QErrorMessage>

namespace client::ui {
MainWindow::MainWindow() {
    ui_ = std::make_unique<Ui::MainWindow>();
    ui_->setupUi(this);
}

void MainWindow::chatConnected(std::shared_ptr<networking::Chat> chat) {
    chat_ = chat;
    ui_->centralWidget->setEnabled(true);
}

void MainWindow::joinChannel() {
    try {
        if(chat_) {
            auto channelName = ui_->joinRoomName->text();
            chat_->joinRoom(channelName.toStdString());
            openChannelTab(channelName);
            ui_->joinRoomName->setText("");
        }
    } catch(const std::exception &ex) {
        displayError(ex.what());
    }
}

void MainWindow::inviteUser() {
    try {
        if(chat_) {
            auto currentRoomName = roomNames[ui_->tabWidget->currentIndex()].toStdString();
            auto invitedUser = ui_->inviteUserName->text().toStdString();
            chat_->inviteUser(currentRoomName, invitedUser);
            ui_->inviteUserName->setText("");
        }
    } catch(const std::exception &ex) {
        displayError(ex.what());
    }
}

void MainWindow::channelChanged(int index) {
}

void MainWindow::displayError(const QString &reason) {
    auto *msg = new QErrorMessage(this);
    msg->showMessage("Error: " + reason);
}

void MainWindow::openChannelTab(const QString &channelName) {
    auto *widget = new QWidget;
    Ui::ChannelTab tabUi;
    tabUi.setupUi(widget);
    auto idx = ui_->tabWidget->addTab(widget, channelName);
    ui_->tabWidget->setCurrentIndex(idx);

    connect(tabUi.sendButton, &QPushButton::clicked, [this, channelName, input = tabUi.msgEdit]() {
        chat_->message(channelName.toStdString(), input->text().toStdString());
        input->setText("");
    });

    roomNames[idx] = channelName;
}

}  // namespace client::ui
