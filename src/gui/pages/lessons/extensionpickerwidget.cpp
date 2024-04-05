#include <QFile>
#include <QLabel>
#include <QGridLayout>
#include <QToolButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "../../../utils/logger.h"
#include "extensionpickerwidget.h"

ExtensionPickerWidget::ExtensionPickerWidget(QWidget* parent) : QWidget(parent) {
    QGridLayout* layout = new QGridLayout(this);
    QLabel* label = new QLabel(tr("Select the file type"),this);
    label->setObjectName("picker_label");
    layout->addWidget(label,0,0,1,3,Qt::AlignHCenter | Qt::AlignTop);

    QFile extensions_json_file(":enums/extensions.json");
    if (extensions_json_file.open(QFile::ReadOnly)) {
        QJsonArray extensions_array = QJsonDocument::fromJson(extensions_json_file.readAll()).object().value("details").toArray();
        extensions_json_file.close();
        for (int i = 0; i < extensions_array.size(); i++) {
            QJsonObject extension_dict = extensions_array.at(i).toObject();
            QToolButton* extension_button = new QToolButton(this);
            extension_button->setIcon(QIcon(extension_dict.value("icon").toString()));
            extension_button->setText(tr(extension_dict.value("extension").toString().toUtf8().constData()));
            extension_button->setToolTip(tr(extension_dict.value("name").toString().toUtf8().constData()));
            extension_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            extension_button->setObjectName("extension_button");
            connect(extension_button, &QToolButton::clicked, [this,extension_dict](){
                bool is_directory = extension_dict.value("name").toString() == "Directory";
                emit extensionSelected(is_directory,extension_dict.value("extension").toString());
            });
            layout->addWidget(extension_button,1 + i/3,i%3,1,1,Qt::AlignCenter);
        }
    } else {
        qWarning("Could not open extensions.json file, extension picking will not be available.");
        Logger::showErrorMessage(tr("Could not open extensions.json file, extension picking will not be available."));
    }
    setLayout(layout);
}
