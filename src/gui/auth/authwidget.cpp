#include <QStackedLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "authwidget.h"
#include "../utils/pageswitcher.h"

AuthWidget::AuthWidget(QWidget* parent) : QWidget(parent) {
    // Header label
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(tr("Welcome to NoteNote !"));
    label->setObjectName("welcome_label");
    layout->addWidget(label,0,Qt::AlignTop | Qt::AlignHCenter);

    stacked_layout = new QStackedLayout();

    // Add page switcher (and connect it to stacked layout)
    PageSwitcher* page_switcher = new PageSwitcher(this, QStringList{tr("Login"), tr("Register")});
    layout->addWidget(page_switcher,0,Qt::AlignBottom | Qt::AlignHCenter);

    // Add error display label
    error_display_label = new QLabel(this);
    error_display_label->setObjectName("error_display_label");
    error_display_label->setWordWrap(true);
    error_display_label->setVisible(false);
    layout->addWidget(error_display_label,0,Qt::AlignTop | Qt::AlignHCenter);

    // Create register and login widgets
    login_widget = new LoginWidget(this);
    stacked_layout->addWidget(login_widget);
    connect(login_widget, &LoginWidget::signIn, this, &AuthWidget::authSuccess);
    connect(login_widget, &LoginWidget::error, this, &AuthWidget::showError);

    register_widget = new RegisterWidget(this);
    stacked_layout->addWidget(register_widget);
    connect(register_widget, &RegisterWidget::signUp, this, &AuthWidget::authSuccess);
    connect(register_widget, &RegisterWidget::error, this, &AuthWidget::showError);

    connect(page_switcher, &PageSwitcher::changePage, this, &AuthWidget::clean);
    connect(page_switcher, &PageSwitcher::changePage, stacked_layout, &QStackedLayout::setCurrentIndex);

    // Add Login and Register stacked layout
    layout->addLayout(stacked_layout);
    setLayout(layout);
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
