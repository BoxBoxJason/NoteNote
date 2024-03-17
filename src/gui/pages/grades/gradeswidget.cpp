#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "gradeswidget.h"
#include "classtrimestersubjectpicker.h"

GradesWidget::GradesWidget(QWidget* parent)  : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    ClassTrimesterSubjectPicker* picker = new ClassTrimesterSubjectPicker(this);
    layout->addWidget(picker,0,Qt::AlignBottom | Qt::AlignHCenter);

    GradesDisplay* grades_display = new GradesDisplay(this);
    layout->addWidget(grades_display,1,Qt::AlignTop | Qt::AlignHCenter);

    // Action buttons
    QHBoxLayout* buttons_layout = new QHBoxLayout;
    QPushButton* save_button = new QPushButton(tr("Save"), this);
    connect(save_button, &QPushButton::clicked, this, &GradesWidget::saveChanges);
    buttons_layout->addWidget(save_button);

    QPushButton* export_button = new QPushButton(tr("Export"), this);
    connect(export_button, &QPushButton::clicked, this, &GradesWidget::exportToCSV);
    buttons_layout->addWidget(export_button);

    layout->addLayout(buttons_layout);
    setLayout(layout);
}


void GradesWidget::saveChanges() {
    // TODO
}


void GradesWidget::exportToCSV() {
    // TODO
}
