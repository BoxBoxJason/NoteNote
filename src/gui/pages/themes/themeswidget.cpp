#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include "themeswidget.h"

ThemesWidget::ThemesWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Save / export buttons
    QHBoxLayout* buttons_layout = new QHBoxLayout;
    QPushButton* save_button = new QPushButton(QIcon(":icons/actions/save.png"),"",this);
    save_button->setToolTip(tr("Save changes"));
    connect(save_button, &QPushButton::clicked, this, &ThemesWidget::saveChanges);
    buttons_layout->addWidget(save_button,0,Qt::AlignRight);

    QPushButton* export_button = new QPushButton(QIcon(":icons/actions/export.png"),"",this);
    export_button->setToolTip(tr("Export to CSV"));
    connect(export_button, &QPushButton::clicked, this, &ThemesWidget::exportToCSV);
    buttons_layout->addWidget(export_button,0,Qt::AlignLeft);

    layout->addLayout(buttons_layout);

    setLayout(layout);
}


void ThemesWidget::saveChanges() {
    // TODO
}


void ThemesWidget::exportToCSV() {
    // TODO
}
