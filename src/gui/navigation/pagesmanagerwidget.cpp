#include "pagesmanagerwidget.h"


PagesManagerWidget::PagesManagerWidget(QWidget* parent) : QWidget(parent) {
    stacked_layout = new QStackedLayout(this);
    auth_widget = new AuthWidget(this);
    stacked_layout->addWidget(auth_widget);

    connect(auth_widget, &AuthWidget::authentified, this, &PagesManagerWidget::login);
}


PagesManagerWidget::~PagesManagerWidget() {
}


void PagesManagerWidget::login(int user_id) {
    if (user_id >= 0) {
        int user_id = user_id;
        schedules_widget = new SchedulesWidget(this);
        stacked_layout->addWidget(schedules_widget);
        stacked_layout->setCurrentWidget(schedules_widget);
    }
}


void PagesManagerWidget::logout() {
    // Remove the previous widget and reset the user_id
    user_id = -1;
    stacked_layout->removeWidget(stacked_layout->currentWidget());

    // Create a new AuthWidget instance and set it as the current widget
    auth_widget = new AuthWidget(this);
    stacked_layout->addWidget(auth_widget);
    stacked_layout->setCurrentWidget(auth_widget);
}
