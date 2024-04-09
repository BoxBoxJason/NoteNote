#include <QVBoxLayout>
#include <QLabel>
#include "gui/pages/schedules/scheduleswidget.h"

SchedulesWidget::SchedulesWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
}
