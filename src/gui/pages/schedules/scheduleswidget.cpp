#include <QVBoxLayout>
#include <QLabel>
#include "scheduleswidget.h"

SchedulesWidget::SchedulesWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
}
