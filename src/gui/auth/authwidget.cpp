#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "authwidget.h"
#include "../utils/pageswitcher.h"

AuthWidget::AuthWidget(QWidget* parent) : QWidget(parent) {
    // Header label
    QVBoxLayout layout(this);
    QLabel label(tr("Welcome to NoteNote !"));
    label.setObjectName("welcome_label");
    layout.addWidget(&label,0,Qt::AlignTop | Qt::AlignHCenter);

    QStackedLayout stacked_layout_instance(this);
    stacked_layout = &stacked_layout_instance;

    // Add page switcher (and connect it to stacked layout)
    PageSwitcher page_switcher(this, QStringList{tr("Login"), tr("Register")});
    layout.addWidget(&page_switcher);

    // Add error display label
    QLabel error_display_label_instance(this);
    error_display_label = &error_display_label_instance;
    error_display_label->setObjectName("error_display_label");
    error_display_label->setWordWrap(true);
    error_display_label->setVisible(false);
    layout.addWidget(error_display_label,0,Qt::AlignTop | Qt::AlignHCenter);

    // Create register and login widgets
    LoginWidget login_widget_instance(this);
    login_widget = &login_widget_instance;
    stacked_layout->addWidget(login_widget);
    connect(login_widget, &LoginWidget::signIn, this, &AuthWidget::authSuccess);

    RegisterWidget register_widget_instance(this);
    register_widget = &register_widget_instance;
    stacked_layout->addWidget(register_widget);
    connect(register_widget, &RegisterWidget::signUp, this, &AuthWidget::authSuccess);

    connect(&page_switcher, &PageSwitcher::changePage, stacked_layout, &QStackedLayout::setCurrentIndex);

    // Add Login and Register stacked layout
    layout.addLayout(stacked_layout);
    setLayout(&layout);
}


AuthWidget::~AuthWidget() {
    setParent(nullptr);
    delete login_widget;
    delete register_widget;
}


void AuthWidget::clean() {
    login_widget->clean();
    register_widget->clean();
    error_display_label->setVisible(false);
    error_display_label->clear();
}


void AuthWidget::authSuccess(int user_id) {
    if (user_id >= 0) {
        emit authentified(user_id);
    }
}


void AuthWidget::showError(const QString& message) {
    error_display_label->setText(message);
    error_display_label->setVisible(true);
}
