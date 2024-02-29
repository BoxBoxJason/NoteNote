#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include "loginwidget.h"
#include "../utils/utils.h"
#include "../controllers/users.h"

LoginWidget::LoginWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout layout(this);
    // Email section
    QLabel email_label(tr("Email"));
    layout.addWidget(&email_label,0,Qt::AlignTop | Qt::AlignHCenter);
    QLineEdit email_line_edit_instance(this);
    email_line_edit = &email_line_edit_instance;
    layout.addWidget(email_line_edit,0,Qt::AlignTop | Qt::AlignHCenter);

    // Password section
    QLabel password_label(tr("Password"));
    layout.addWidget(&password_label,0,Qt::AlignTop | Qt::AlignHCenter);
    QLineEdit password_line_edit_instance(this);
    password_line_edit = &password_line_edit_instance;
    password_line_edit->setEchoMode(QLineEdit::Password);
    layout.addWidget(password_line_edit,0,Qt::AlignTop | Qt::AlignHCenter);

    resetInputStyle();
    // Add login button
    QPushButton login_button(tr("Login"));
    connect(&login_button, &QPushButton::clicked, this, &LoginWidget::loginClicked);
    layout.addWidget(&login_button,0,Qt::AlignTop | Qt::AlignHCenter);

    setLayout(&layout);
}


LoginWidget::~LoginWidget() {
    setParent(nullptr);
    delete email_line_edit;
    delete password_line_edit;
}


void LoginWidget::clean() {
    email_line_edit->clear();
    password_line_edit->clear();
}


void LoginWidget::loginClicked() {
    QString email = email_line_edit->text().trimmed();
    QString password = password_line_edit->text().trimmed();
    if (AuthUtils::checkEmailFormat(email) && AuthUtils::checkPasswordFormat(password)) {
        int user_id = UsersController::checkPasswordMatch(email, password);
        if (user_id >= 0) {
            emit signIn(user_id);
        } else {
            email_line_edit->setObjectName("auth_input_incorrect");
            password_line_edit->setObjectName("auth_input_incorrect");
            emit error(tr("Invalid email/password combination"));
        }
    } else {
        email_line_edit->setObjectName("auth_input_incorrect");
        password_line_edit->setObjectName("auth_input_incorrect");
        emit error(tr("Invalid email/password combination"));
    }
}


void LoginWidget::resetInputStyle() {
    email_line_edit->setObjectName("auth_input");
    password_line_edit->setObjectName("auth_input");
}
