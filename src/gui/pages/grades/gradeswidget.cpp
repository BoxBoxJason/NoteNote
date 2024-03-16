#include <QVBoxLayout>
#include <QLabel>
#include "gradeswidget.h"

GradesWidget::GradesWidget(QWidget* parent)  : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("Grades", this);
    layout->addWidget(label);
    setLayout(layout);
}


GradesWidget::~GradesWidget() {
}
