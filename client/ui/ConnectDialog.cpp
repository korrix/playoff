#include "ConnectDialog.h"

#include "model/User.h"
#include "ui_ConnectDialog.h"

#include <QErrorMessage>

namespace client::ui {
ConnectDialog::ConnectDialog(){
    ui_ = std::make_unique<Ui::ConnectDialog>();
    ui_->setupUi(this);
}

ConnectDialog::~ConnectDialog() = default;

void ConnectDialog::connect() {
    try {
      // TODO
    } catch(const std::exception &ex) {
        displayError(ex.what());
    }
}

void ConnectDialog::cancel() {
    reject();
}

void ConnectDialog::displayError(const QString &reason) {
}
}  // namespace client::ui