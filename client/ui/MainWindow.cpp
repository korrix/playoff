#include "MainWindow.h"
#include "ui_MainWindow.h"

namespace client::ui {
MainWindow::MainWindow() {
    ui_ = std::make_unique<Ui::MainWindow>();
    ui_->setupUi(this);
}

void MainWindow::chatConnected(std::shared_ptr<networking::Chat> chat) {
    chat_ = chat;
    ui_->centralWidget->setEnabled(true);
}
}

