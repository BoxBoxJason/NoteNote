#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include "gui/pages/lessons/filecreatorwidget.h"
#include "gui/pages/lessons/lessonscontextmenu.h"
#include "utils/fileutils.h"

LessonsContextMenu::LessonsContextMenu(QWidget* parent) : QMenu(parent) {
    create_new_item = new QAction("Create", this);
    connect(create_new_item, &QAction::triggered, this, &LessonsContextMenu::createAction);
    addAction(create_new_item);

    import_new_item = new QAction("Import", this);
    connect(import_new_item, &QAction::triggered, this, &LessonsContextMenu::importAction);
    addAction(import_new_item);

    open_file = new QAction("Open", this);
    connect(open_file, &QAction::triggered, this, &LessonsContextMenu::openAction);
    addAction(open_file);

    rename_item = new QAction("Rename", this);
    connect(rename_item, &QAction::triggered, this, &LessonsContextMenu::renameAction);
    addAction(rename_item);

    delete_item = new QAction("Delete", this);
    connect(delete_item, &QAction::triggered, this, &LessonsContextMenu::deleteAction);
    addAction(delete_item);
}


void LessonsContextMenu::prepareMenu(QTreeWidgetItem* item) {
    if (item != nullptr) {
        create_new_item->setEnabled(item->text(2) == "directory" || item->text(2).isEmpty());
        create_new_item->setVisible(item->text(2) == "directory" || item->text(2).isEmpty());

        import_new_item->setEnabled(item->text(2) == "directory" || item->text(2).isEmpty());
        import_new_item->setVisible(item->text(2) == "directory" || item->text(2).isEmpty());

        open_file->setEnabled(item->text(2) == "file");
        open_file->setVisible(item->text(2) == "file");

        rename_item->setEnabled(!item->text(2).isEmpty());
        rename_item->setVisible(!item->text(2).isEmpty());

        delete_item->setEnabled(!item->text(2).isEmpty());
        delete_item->setVisible(!item->text(2).isEmpty());
        selected_item = item;
    }
}


void LessonsContextMenu::deleteAction() {
    if (selected_item != nullptr) {
        FileUtils::deletePath(selected_item->text(1));
        delete selected_item;
        selected_item = nullptr;
    }
}


void LessonsContextMenu::renameAction() {
    if (selected_item != nullptr) {
        selected_item->setSelected(true);
    }
}


void LessonsContextMenu::openAction() {
    if (selected_item != nullptr) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(selected_item->text(1)));
    }
}


void LessonsContextMenu::importAction() {
    if (selected_item != nullptr) {
        QFileDialog import_dialog;
        import_dialog.setFileMode(QFileDialog::ExistingFiles);
        import_dialog.setDirectory(QDir::homePath());
        import_dialog.setNameFilter("All Files (*)");
        if (import_dialog.exec()) {
            QStringList files = import_dialog.selectedFiles();
            if (files.size() > 0) {
                QFile extensions_json_file(":enums/extensions.json");
                if (extensions_json_file.open(QFile::ReadOnly)) {
                    QJsonObject extensions_dict = QJsonDocument::fromJson(extensions_json_file.readAll()).object().value("extensions").toObject();
                    extensions_json_file.close();
                    for (const QString& file : files) {
                        QString new_path = QFileInfo(selected_item->text(1)).dir().filePath(QFileInfo(file).fileName());
                        QFile::copy(file, new_path);
                        QTreeWidgetItem* new_item = new QTreeWidgetItem(selected_item);
                        new_item->setFlags(new_item->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
                        new_item->setText(0, QFileInfo(file).fileName());
                        new_item->setText(1, new_path);
                        new_item->setText(2, "file");
                        QString extension = QFileInfo(file).suffix();
                        if (extensions_dict.contains(extension)) {
                            new_item->setIcon(0, QIcon(extensions_dict.value(extension).toString()));
                        } else {
                            new_item->setIcon(0, QIcon(":icons/extensions/none.png"));
                        }
                    }
                }
            }
        }
    }
}


void LessonsContextMenu::createAction() {
    if (selected_item != nullptr) {
        FileCreatorWidget* file_creator = new FileCreatorWidget(selected_item);
        file_creator->exec();
    }
}
