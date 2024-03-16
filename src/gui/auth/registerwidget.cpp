#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include "registerwidget.h"
#include "../../utils/authutils.h"
#include "../../controllers/userscontroller.h"

RegisterWidget::RegisterWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // First name section
    QLabel* first_name_label = new QLabel(tr("First name"));
    first_name_label->setObjectName("auth_input_label");
    first_name_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(first_name_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    first_name_line_edit = new QLineEdit(this);
    first_name_line_edit->setObjectName("auth_input");
    first_name_line_edit->setToolTip(tr("Only letters and hyphens are allowed"));
    connect(first_name_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkFirstName);
    layout->addWidget(first_name_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Last name section
    QLabel* last_name_label = new QLabel(tr("Last name"));
    last_name_label->setObjectName("auth_input_label");
    last_name_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(last_name_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    last_name_line_edit = new QLineEdit(this);
    last_name_line_edit->setObjectName("auth_input");
    last_name_line_edit->setToolTip(tr("Only letters and hyphens are allowed"));
    connect(last_name_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkLastName);
    layout->addWidget(last_name_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Email section
    QLabel* email_label = new QLabel(tr("Email"));
    email_label->setObjectName("auth_input_label");
    email_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(email_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    email_line_edit = new QLineEdit(this);
    email_line_edit->setObjectName("auth_input");
    email_line_edit->setToolTip(tr("Valid email format required"));
    connect(email_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkEmail);
    layout->addWidget(email_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Password section
    QLabel* password_label = new QLabel(tr("Password"));
    password_label->setObjectName("auth_input_label");
    password_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(password_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    password_line_edit = new QLineEdit(this);
    password_line_edit->setEchoMode(QLineEdit::Password);
    password_line_edit->setObjectName("auth_input");
    password_line_edit->setToolTip(tr("At least 8 characters letters, numbers and special characters"));
    connect(password_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkPassword);
    layout->addWidget(password_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Confirm password section
    QLabel* confirm_password_label = new QLabel(tr("Confirm password"));
    confirm_password_label->setObjectName("auth_input_label");
    confirm_password_label->setAlignment(Qt::AlignCenter);
    layout->addWidget(confirm_password_label, 0, Qt::AlignHCenter | Qt::AlignBottom);

    confirm_password_line_edit = new QLineEdit(this);
    confirm_password_line_edit->setEchoMode(QLineEdit::Password);
    confirm_password_line_edit->setObjectName("auth_input");
    confirm_password_line_edit->setToolTip(tr("Must match the password"));
    connect(confirm_password_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkConfirmPassword);
    layout->addWidget(confirm_password_line_edit, 0, Qt::AlignHCenter | Qt::AlignTop);

    // Register button
    register_button = new QPushButton(tr("Register"));
    register_button->setObjectName("auth_submit_button");
    connect(register_button, &QPushButton::clicked, this, &RegisterWidget::registerClicked);
    register_button->setEnabled(false);
    layout->addWidget(register_button, 0, Qt::AlignHCenter);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}


RegisterWidget::~RegisterWidget() {
}


void RegisterWidget::clean() {
    first_name_line_edit->clear();
    first_name_line_edit->setObjectName("auth_input");

    last_name_line_edit->clear();
    last_name_line_edit->setObjectName("auth_input");

    email_line_edit->clear();
    email_line_edit->setObjectName("auth_input");

    password_line_edit->clear();
    password_line_edit->setObjectName("auth_input");

    confirm_password_line_edit->clear();
    confirm_password_line_edit->setObjectName("auth_input");
}


void RegisterWidget::registerClicked() {
    // Retrieve fields
    QString first_name = first_name_line_edit->text().trimmed();
    QString last_name = last_name_line_edit->text().trimmed();
    QString email = email_line_edit->text().trimmed();
    QString password = password_line_edit->text().trimmed();

    if(first_name_valid && last_name_valid && email_valid && password_valid && confirm_password_valid) {
        int user_id = UsersController::getUserIdFromEmail(email);
        if (user_id < 0) {
            user_id = UsersController::createUser(first_name, last_name, email, password);
            if (user_id >= 0) {
                emit signUp(user_id);
            } else {
                emit error(tr("An error occurred while creating the user"));
            }
        } else {
            emit error(tr("The email is already in use"));
        }
    } else {
        emit error(tr("Invalid input fields"));
    }
}


void RegisterWidget::checkFirstName(const QString& first_name) {
    first_name_valid = AuthUtils::checkNameFormat(first_name.trimmed());
    if (first_name_valid) {
        first_name_line_edit->setObjectName("auth_input");
        if (last_name_valid && email_valid && password_valid && confirm_password_valid) {
            register_button->setEnabled(true);
        }
    } else {
        first_name_line_edit->setObjectName("auth_input_incorrect");
        register_button->setEnabled(false);
    }
}


void RegisterWidget::checkLastName(const QString& last_name) {
    last_name_valid = AuthUtils::checkNameFormat(last_name.trimmed());
    if (last_name_valid) {
        last_name_line_edit->setObjectName("auth_input");
        if (first_name_valid && email_valid && password_valid && confirm_password_valid) {
            register_button->setEnabled(true);
        }
    } else {
        last_name_line_edit->setObjectName("auth_input_incorrect");
        register_button->setEnabled(false);
    }
}


void RegisterWidget::checkEmail(const QString& email) {
    email_valid = AuthUtils::checkEmailFormat(email.trimmed());
    if (email_valid) {
        email_line_edit->setObjectName("auth_input");
        if (first_name_valid && last_name_valid && password_valid && confirm_password_valid) {
            register_button->setEnabled(true);
        }
    } else {
        email_line_edit->setObjectName("auth_input_incorrect");
        register_button->setEnabled(false);
    }
}


void RegisterWidget::checkPassword(const QString& password) {
    password_valid = AuthUtils::checkPasswordFormat(password.trimmed());
    if (password_valid) {
        password_line_edit->setObjectName("auth_input");
        if (first_name_valid && last_name_valid && email_valid && confirm_password_valid) {
            register_button->setEnabled(true);
        }
    } else {
        password_line_edit->setObjectName("auth_input_incorrect");
        register_button->setEnabled(false);
    }
}


void RegisterWidget::checkConfirmPassword(const QString& confirm_password) {
    confirm_password_valid = confirm_password.trimmed() == password_line_edit->text().trimmed();
    if (confirm_password_valid) {
        confirm_password_line_edit->setObjectName("auth_input");
        if (first_name_valid && last_name_valid && email_valid && password_valid) {
            register_button->setEnabled(true);
        }
    } else {
        confirm_password_line_edit->setObjectName("auth_input_incorrect");
        register_button->setEnabled(false);
    }
}
