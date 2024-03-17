#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "reportswidget.h"


ReportsWidget::ReportsWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Save / export buttons
    QHBoxLayout* buttons_layout = new QHBoxLayout;
    QPushButton* save_button = new QPushButton(QIcon(":icons/save.png"),"",this);
    save_button->setToolTip(tr("Save changes"));
    connect(save_button, &QPushButton::clicked, this, &ReportsWidget::saveChanges);
    buttons_layout->addWidget(save_button,0,Qt::AlignRight);

    QPushButton* export_button = new QPushButton(QIcon(":icons/export.png"),"",this);
    export_button->setToolTip(tr("Export to CSV"));
    connect(export_button, &QPushButton::clicked, this, &ReportsWidget::exportToCSV);
    buttons_layout->addWidget(export_button,0,Qt::AlignLeft);

    layout->addLayout(buttons_layout);

    setLayout(layout);
}


void ReportsWidget::showStudentReport(int student_id, int year_id, int trimester_id) {
    // TODO
}


void ReportsWidget::exportToCSV() {
    // TODO
}


void ReportsWidget::saveChanges() {
    // TODO
}
