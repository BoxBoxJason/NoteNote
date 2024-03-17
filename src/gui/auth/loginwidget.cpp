#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include "loginwidget.h"
#include "../../utils/authutils.h"
#include "../../controllers/userscontroller.h"

LoginWidget::LoginWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    // Email section
    QLabel* email_label = new QLabel(tr("Email"));
    email_label->setAlignment(Qt::AlignCenter);
    email_label->setObjectName("auth_input_label");
    layout->addWidget(email_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    email_line_edit = new QLineEdit(this);
    email_line_edit->setObjectName("auth_input");
    layout->addWidget(email_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Password section
    QLabel* password_label = new QLabel(tr("Password"));
    password_label->setAlignment(Qt::AlignCenter);
    password_label->setObjectName("auth_input_label");
    layout->addWidget(password_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    password_line_edit = new QLineEdit(this);
    password_line_edit->setObjectName("auth_input");
    password_line_edit->setEchoMode(QLineEdit::Password);
    layout->addWidget(password_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Add login button
    QPushButton* login_button = new QPushButton(tr("Login"));
    login_button->setObjectName("auth_submit_button");
    connect(login_button, &QPushButton::clicked, this, &LoginWidget::loginClicked);
    layout->addWidget(login_button, 0, Qt::AlignHCenter);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
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
