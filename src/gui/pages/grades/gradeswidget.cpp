#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include "gui/pages/grades/gradeswidget.h"
#include "gui/pages/grades/classtrimestersubjectpicker.h"

GradesWidget::GradesWidget(QWidget* parent)  : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    ClassTrimesterSubjectPicker* picker = new ClassTrimesterSubjectPicker(this);
    layout->addWidget(picker,0,Qt::AlignBottom | Qt::AlignHCenter);

    GradesDisplay* grades_display = new GradesDisplay(this);
    layout->addWidget(grades_display,1,Qt::AlignTop | Qt::AlignHCenter);

    // Save / export buttons
    QHBoxLayout* buttons_layout = new QHBoxLayout;
    QPushButton* save_button = new QPushButton(QIcon(":icons/actions/save.png"),"",this);
    save_button->setToolTip(tr("Save changes"));
    connect(save_button, &QPushButton::clicked, this, &GradesWidget::saveChanges);
    buttons_layout->addWidget(save_button,0,Qt::AlignRight);

    QPushButton* export_button = new QPushButton(QIcon(":icons/actions/export.png"),"",this);
    export_button->setToolTip(tr("Export to CSV"));
    connect(export_button, &QPushButton::clicked, this, &GradesWidget::exportToCSV);
    buttons_layout->addWidget(export_button,0,Qt::AlignLeft);

    layout->addLayout(buttons_layout);
    setLayout(layout);
}


void GradesWidget::saveChanges() {
    // TODO
}


void GradesWidget::exportToCSV() {
    // TODO
}
