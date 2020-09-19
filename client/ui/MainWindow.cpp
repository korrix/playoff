#include "MainWindow.h"

#include "networking/Chat.h"
#include "ui_ChannelTab.h"
#include "ui_MainWindow.h"

#include <QErrorMessage>
#include <QTimer>
#include <spdlog/spdlog.h>

namespace client::ui {
MainWindow::MainWindow() {
    ui_ = std::make_unique<Ui::MainWindow>();
    ui_->setupUi(this);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::pullChat);
}

void MainWindow::chatConnected(std::shared_ptr<networking::Chat> chat) {
    chat_ = chat;
    ui_->centralWidget->setEnabled(true);
    updateTimer->start(500);
}

void MainWindow::pullChat() {
    try {
        auto update = chat_->requestUpdate();
        for(auto &invitation : update.invitations()) {
            auto roomName = QString::fromStdString(invitation.room().name());
            auto message = QString::fromStdString(invitation.text());
            openChannelTab(roomName, message);
        }

        for(auto &message : update.messages()) {
            auto roomName = QString::fromStdString(message.room().name());
            auto msg = QString::fromStdString(message.sender().name() + ": " + message.text());
            roomMessages[roomName]->addItem(msg);
        }

    } catch(std::exception &ex) {
        spdlog::error("Error while updating: {}", ex.what());
    }
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
            auto invitedUser     = ui_->inviteUserName->text().toStdString();
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

void MainWindow::openChannelTab(const QString &channelName, QString invitation) {
    auto *widget = new QWidget;
    Ui::ChannelTab tabUi;
    tabUi.setupUi(widget);
    auto idx = ui_->tabWidget->addTab(widget, channelName);
    ui_->tabWidget->setCurrentIndex(idx);

    if(!invitation.isEmpty()) {
        tabUi.messageView->addItem("INVITATION: " + invitation);
    }

    connect(tabUi.sendButton, &QPushButton::clicked, [this, channelName, input = tabUi.msgEdit]() {
        chat_->message(channelName.toStdString(), input->text().toStdString());
        input->setText("");
    });

    roomNames[idx] = channelName;
    roomMessages[channelName] = tabUi.messageView;
}

}  // namespace client::ui
