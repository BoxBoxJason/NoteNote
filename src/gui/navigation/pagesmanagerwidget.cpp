#include "pagesmanagerwidget.h"
#include "../../utils/sessionmanager.hpp"


PagesManagerWidget::PagesManagerWidget(QWidget* parent) : QWidget(parent) {
    stacked_layout = new QStackedLayout(this);
    auth_widget = new AuthWidget(this);
    stacked_layout->addWidget(auth_widget);

    connect(auth_widget, &AuthWidget::authentified, this, &PagesManagerWidget::login);
}


PagesManagerWidget::~PagesManagerWidget() {
}


void PagesManagerWidget::login(int user_id) {
    SessionManager::instance().setUserId(user_id);
    changePage("schedules");
    auth_widget = nullptr;
}


void PagesManagerWidget::changePage(const QString& page_name) {
    if (page_name != current_page) {
        bool page_valid = true;
        if (page_name == "auth") {
            SessionManager::instance().setUserId(-1);
            auth_widget = new AuthWidget(this);
            stacked_layout->addWidget(auth_widget);
        } else if (WIDGET_MAP.contains(page_name)) {
            stacked_layout->addWidget(WIDGET_MAP[page_name]());
        } else {
            qCritical() << "Page not found: " << page_name;
            page_valid = false;
        }
        if (page_valid) {
            current_page = page_name;
            QWidget* current_widget = stacked_layout->currentWidget();
            stacked_layout->removeWidget(current_widget);
            delete current_widget;
        }
    }
}
