#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include <QFile>
#include <QApplication>
#include "utils/fileutils.h"
#include "gui/pages/lessons/namepickerwidget.h"

NamePickerWidget::NamePickerWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(tr("Choose a name"),this);
    label->setObjectName("picker_label");
    layout->addWidget(label,0,Qt::AlignBottom | Qt::AlignHCenter);

    file_name_input = new QLineEdit(this);
    file_name_input->setObjectName("picker_input");
    connect(file_name_input, &QLineEdit::textChanged, this, [this](const QString &text) { emit nameChanged(text.trimmed());} );
    layout->addWidget(file_name_input,1,Qt::AlignTop | Qt::AlignHCenter);

    create_button = new QPushButton(tr("Create"),this);
    create_button->setObjectName("confirm_button");
    connect(create_button, &QPushButton::clicked, this, &NamePickerWidget::submitCreation);
    layout->addWidget(create_button,0,Qt::AlignCenter);
}


void NamePickerWidget::submitCreation() {
    emit namePicked(is_directory, file_name_input->text().trimmed());
}


void NamePickerWidget::setIncorrectInput(const QString& error_message) {
    file_name_input->setObjectName("picker_input_incorrect");
    file_name_input->setToolTip(tr(error_message.toUtf8()));
    create_button->setEnabled(false);
}


void NamePickerWidget::setCorrectInput() {
    file_name_input->setObjectName("picker_input");
    file_name_input->setToolTip(tr("Pick a name for the new item"));
    create_button->setEnabled(true);
}


void NamePickerWidget::setSuffix(bool is_dir, const QString& suffix) {
    is_directory = is_dir;
    file_name_input->setText(suffix);
    file_name_input->setCursorPosition(0);
}