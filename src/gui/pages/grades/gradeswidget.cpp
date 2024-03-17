#include <QVBoxLayout>
#include <QLabel>
#include "gradeswidget.h"
#include "classtrimestersubjectpicker.h"

GradesWidget::GradesWidget(QWidget* parent)  : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    ClassTrimesterSubjectPicker* picker = new ClassTrimesterSubjectPicker(this);
    layout->addWidget(picker,0,Qt::AlignBottom | Qt::AlignHCenter);
    setLayout(layout);
}
