#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include "registerwidget.h"
#include "../utils/pageswitcher.h"
#include "../utils/utils.h"
#include "../controllers/users.h"

RegisterWidget::RegisterWidget(QWidget* parent) : QWidget(parent) {
    QGridLayout layout(this);

    // First name section
    QVBoxLayout first_name_layout;
    QLabel first_name_label(tr("First name"));
    first_name_label.setObjectName("auth_input_label");
    first_name_layout.addWidget(&first_name_label,0,Qt::AlignBottom | Qt::AlignHCenter);

    QLineEdit first_name_line_edit_instance(this);
    first_name_line_edit = &first_name_line_edit_instance;
    first_name_line_edit->setObjectName("auth_input");
    first_name_line_edit->setToolTip(tr("Only letters and hyphens are allowed"));
    connect(first_name_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkFirstName);
    first_name_layout.addWidget(first_name_line_edit,0,Qt::AlignTop | Qt::AlignHCenter);
    layout.addLayout(&first_name_layout,0,0,1,1,Qt::AlignCenter);

    // Last name section
    QVBoxLayout last_name_layout;
    QLabel last_name_label(tr("Last name"));
    last_name_label.setObjectName("auth_input_label");
    last_name_layout.addWidget(&last_name_label,0,Qt::AlignBottom | Qt::AlignHCenter);

    QLineEdit last_name_line_edit_instance(this);
    last_name_line_edit = &last_name_line_edit_instance;
    last_name_line_edit->setObjectName("auth_input");
    last_name_line_edit->setToolTip(tr("Only letters and hyphens are allowed"));
    connect(last_name_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkLastName);
    last_name_layout.addWidget(last_name_line_edit,0,Qt::AlignTop | Qt::AlignHCenter);
    layout.addLayout(&last_name_layout,0,1,1,1,Qt::AlignCenter);


    // Email section
    QHBoxLayout email_layout;
    QLabel email_label(tr("Email"));
    email_label.setObjectName("auth_input_label");
    email_layout.addWidget(&email_label,0, Qt::AlignVCenter | Qt::AlignLeft);

    QLineEdit email_line_edit_instance(this);
    email_line_edit = &email_line_edit_instance;
    email_line_edit->setObjectName("auth_input");
    email_line_edit->setToolTip(tr("Valid email format"));
    connect(email_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkEmail);
    email_layout.addWidget(email_line_edit,0,Qt::AlignVCenter | Qt::AlignLeft);
    layout.addLayout(&email_layout,1,0,1,2,Qt::AlignCenter);

    // Password section
    QHBoxLayout password_layout;
    QLabel password_label(tr("Password"));
    password_label.setObjectName("auth_input_label");
    password_layout.addWidget(&password_label,0,Qt::AlignVCenter | Qt::AlignLeft);

    QLineEdit password_line_edit_instance(this);
    password_line_edit = &password_line_edit_instance;
    password_line_edit->setEchoMode(QLineEdit::Password);
    password_line_edit->setObjectName("auth_input");
    password_line_edit->setToolTip(tr("At least 8 characters letters, numbers and special characters"));
    connect(password_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkPassword);
    password_layout.addWidget(password_line_edit,0,Qt::AlignVCenter | Qt::AlignLeft);
    layout.addLayout(&password_layout,2,0,1,2,Qt::AlignCenter);

    // Confirm password section
    QHBoxLayout confirm_password_layout;
    QLabel confirm_password_label(tr("Confirm password"));
    confirm_password_label.setObjectName("auth_input_label");
    confirm_password_layout.addWidget(&confirm_password_label,0,Qt::AlignVCenter | Qt::AlignLeft);

    QLineEdit confirm_password_line_edit_instance(this);
    confirm_password_line_edit = &confirm_password_line_edit_instance;
    confirm_password_line_edit->setEchoMode(QLineEdit::Password);
    confirm_password_line_edit->setObjectName("auth_input");
    confirm_password_line_edit->setToolTip(tr("Must match the password"));
    connect(confirm_password_line_edit, &QLineEdit::textChanged, this, &RegisterWidget::checkConfirmPassword);
    confirm_password_layout.addWidget(confirm_password_line_edit,0,Qt::AlignVCenter | Qt::AlignLeft);
    layout.addLayout(&confirm_password_layout,3,0,1,2,Qt::AlignCenter);

    // Add register button
    QPushButton register_button_instance(tr("Register"));
    register_button = &register_button_instance;
    connect(register_button, &QPushButton::clicked, this, &RegisterWidget::registerClicked);
    layout.addWidget(register_button,4,0,1,2,Qt::AlignHCenter | Qt::AlignTop);

    setLayout(&layout);
}


RegisterWidget::~RegisterWidget() {
    setParent(nullptr);
    delete first_name_line_edit;
    delete last_name_line_edit;
    delete email_line_edit;
    delete password_line_edit;
    delete confirm_password_line_edit;
    delete register_button;
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
    QString confirm_password = confirm_password_line_edit->text().trimmed();

    if(first_name_valid && last_name_valid && email_valid && password_valid && confirm_password_valid) {
        int user_id = UsersController::checkEmailExists(email);
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
