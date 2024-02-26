#include "authwidget.h"

AuthWidget::AuthWidget(QWidget* parent) : QWidget(parent)
{
    login_widget_instance = LoginWidget(this);
    login_widget = &login_widget_instance;
    register_widget_instance = RegisterWidget(this);
    register_widget = &register_widget_instance;

    connect(login_widget, &LoginWidget::authSuccess, this, &AuthWidget::authSuccess);
    connect(register_widget, &RegisterWidget::authSuccess, this, &AuthWidget::authSuccess);

    QVBoxLayout layout(this);
    layout->addWidget(login_widget);
    layout->addWidget(register_widget);
    setLayout(&layout);
}
