#include <QDir>
#include <QFile>
#include <QString>
#include <QDesktopServices>
#include <QApplication>
#include "utils/fileutils.h"
#include "gui/pages/lessons/namepickerwidget.h"
#include "gui/pages/lessons/filecreatorwidget.h"

FileCreatorWidget::FileCreatorWidget(QTreeWidgetItem* parent_item, QWidget* parent) : QDialog(parent) , parent_item(parent_item) {
    layout = new QStackedLayout(this);
    extension_picker = new ExtensionPickerWidget(this);
    layout->addWidget(extension_picker);

    NamePickerWidget* name_picker = new NamePickerWidget(this);
    connect(extension_picker, &ExtensionPickerWidget::extensionSelected, name_picker, &NamePickerWidget::setSuffix);
    connect(extension_picker, &ExtensionPickerWidget::extensionSelected, this, &FileCreatorWidget::extensionSelected);
    connect(name_picker, &NamePickerWidget::namePicked, this, &FileCreatorWidget::createPath);
    connect(name_picker, &NamePickerWidget::nameChanged, this, &FileCreatorWidget::checkFileName);
    connect(this, &FileCreatorWidget::invalidPath, name_picker, &NamePickerWidget::setIncorrectInput);
    connect(this, &FileCreatorWidget::validPath, name_picker, &NamePickerWidget::setCorrectInput);
    layout->addWidget(name_picker);

    setLayout(layout);
}


void FileCreatorWidget::extensionSelected(bool is_directory, const QString& extension) {
    layout->removeWidget(extension_picker);
    delete extension_picker;
    extension_picker = nullptr;
}


void FileCreatorWidget::createPath(bool is_directory, const QString& file_name) {
    if (FileUtils::checkFileNameValid(file_name)) {
        const QString absolute_path = QDir(parent_item->text(1).isEmpty() ? FileUtils::CUSTOM_FS_ROOT_DIR() : parent_item->text(1)).filePath(file_name);
        if (FileUtils::checkPathValid(absolute_path)) {
            if (FileUtils::createPath(is_directory, absolute_path)) {
                QTreeWidgetItem* new_item = new QTreeWidgetItem(parent_item);
                new_item->setFlags(new_item->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
                new_item->setText(0, file_name);
                new_item->setText(1, absolute_path);
                new_item->setText(2, is_directory ? "directory" : "file");
                new_item->setIcon(0, QIcon(is_directory ? ":icons/extensions/folder.png" : ":icons/extensions/" + QFileInfo(absolute_path).suffix()+ ".png"));
                if (is_directory) {
                    new_item->setFlags(new_item->flags() | Qt::ItemIsDropEnabled);
                }
            }
        }
    }
}


bool FileCreatorWidget::checkFileName(const QString& file_name) {
    bool name_valid = true;
    QString trimmed_name = file_name.trimmed();
    QString attempted_path = QDir::cleanPath(QDir((parent_item->text(1)).isEmpty() ? FileUtils::CUSTOM_FS_ROOT_DIR() : parent_item->text(1)).filePath(trimmed_name));
    if (FileUtils::checkFileNameValid(trimmed_name) && FileUtils::checkPathValid(attempted_path) && \
        attempted_path.startsWith(FileUtils::CUSTOM_FS_ROOT_DIR()) && !QDir(attempted_path).exists()) {
        emit validPath();
    } else {
        name_valid = false;
        emit invalidPath(tr("Invalid item name. Please choose a different name."));
    }
    return name_valid;
}
