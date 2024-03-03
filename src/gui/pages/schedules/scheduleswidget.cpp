#include "scheduleswidget.h"

#include <QVBoxLayout>
#include <QLabel>

SchedulesWidget::SchedulesWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
}


SchedulesWidget::~SchedulesWidget() {
}
