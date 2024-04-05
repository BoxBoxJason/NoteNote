#include <QContextMenuEvent>
#include <QFileInfo>
#include <QApplication>
#include <QDir>
#include "lessonswidget.h"
#include "../../../utils/fileutils.h"

LessonsWidget::LessonsWidget(QWidget* parent) : QTreeWidget(parent) {
    QDir root_fs = QDir(FileUtils::CUSTOM_FS_ROOT_DIR());
    if (!root_fs.exists()) {
        root_fs.mkdir(root_fs.path());
    }

    // Add the custom file explorer context menu
    context_menu = new LessonsContextMenu(this);

    // Set the column count and header labels
    setColumnCount(3);
    setHeaderLabels(QStringList{"File System","Path","Type"});
    for (int i=1;i<3;i++) {
        hideColumn(i);
    }

    // Set the options
    setContextMenuPolicy(Qt::CustomContextMenu);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setDropIndicatorShown(true);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed | QAbstractItemView::SelectedClicked);

    // Connect custom widget slots and signals
    connect(this, &LessonsWidget::itemChanged, this, &LessonsWidget::onItemChanged);
    connect(this, &LessonsWidget::itemCollapsed, this, &LessonsWidget::folderClosed);
    connect(this, &LessonsWidget::itemExpanded, this, &LessonsWidget::folderOpened);
    connect(this, &QWidget::customContextMenuRequested, this, &LessonsWidget::showContextMenu);
    // Load the file system
    loadFileSystem(*invisibleRootItem(), FileUtils::constructFileSystemJson(FileUtils::CUSTOM_FS_ROOT_DIR()));
}


void LessonsWidget::showContextMenu(const QPoint& pos) {
    context_menu->prepareMenu(selectedItems().size() > 0 ? selectedItems().at(0) : invisibleRootItem());
    context_menu->exec(mapToGlobal(pos));
}


void LessonsWidget::loadFileSystem(QTreeWidgetItem& parent_item, const QJsonArray& json_file_system) {
    if (!json_file_system.isEmpty()) {
        for (const QJsonValue& file_value : json_file_system) {
            QJsonObject file_system_object = file_value.toObject();
            QTreeWidgetItem* new_item = new QTreeWidgetItem(parent_item);
            new_item->setFlags(new_item->flags() | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
            new_item->setText(0, file_system_object["name"].toString());
            new_item->setText(1, file_system_object["path"].toString());
            new_item->setText(2, file_system_object["type"].toString());
            new_item->setIcon(0, QIcon(file_system_object["type"].toString() == "directory" ? ":icons/extensions/folder.png" : ":icons/extensions/" + file_system_object["extension"].toString() + ".png"));
            parent_item.addChild(new_item);
            if (file_system_object.contains("children")) {
                new_item->setFlags(new_item->flags() | Qt::ItemIsDropEnabled);
                loadFileSystem(*new_item, file_system_object["children"].toArray());
            }
        }
    }
}


void LessonsWidget::folderClosed(QTreeWidgetItem* item) {
    if (item->text(2) == "directory") {
        item->setIcon(0, QIcon(":icons/extensions/folder.png"));
    }
}


void LessonsWidget::folderOpened(QTreeWidgetItem* item) {
    if (item->text(2) == "directory") {
        item->setIcon(0, QIcon(":icons/extensions/folderopen.png"));
    }
}


void LessonsWidget::onItemChanged(QTreeWidgetItem* item, int column) {
    if (column == 0) {
        QString new_file_name = item->text(0);
        QString new_path = QFileInfo(item->text(1)).dir().filePath(new_file_name);
        // Validate new file name and path
        if (FileUtils::checkFileNameValid(new_file_name) && FileUtils::checkPathValid(new_path) && new_path.contains(QApplication::applicationDirPath())) {
            // Rename the file / directory
            QFile file(item->text(1));
            file.rename(new_path);
            item->setText(1, new_path);
            if (item->text(2) == "directory") {
                // Remove all children and reload the file system
                while (item->childCount() > 0) {
                    delete item->child(0);
                }
                loadFileSystem(*item, FileUtils::constructFileSystemJson(new_path));
            } else {
                item->setIcon(0, QIcon(":icons/extensions/" + QFileInfo(new_path).suffix() + ".png"));
            }
        } else {
            item->setText(0, QFileInfo(item->text(1)).fileName());
        }
    }
}


void LessonsWidget::dropEvent(QDropEvent* event) {
    QTreeWidgetItem* moved_item = currentItem();
    QTreeWidgetItem* destination_item = itemFromIndex(indexAt(event->position().toPoint()));
    QString destination_path = destination_item->text(1).isEmpty() ? FileUtils::CUSTOM_FS_ROOT_DIR() : destination_item->text(1);
    QFileInfo destination_dir = QFileInfo(destination_path);
    if (destination_item == nullptr) {
        destination_item = invisibleRootItem();
    }
    if (moved_item != nullptr && destination_dir.isDir()) {
        QString new_path = QDir(destination_path).filePath(moved_item->text(0));
        QFile file(moved_item->text(1));
        if (file.rename(new_path)) {
            moved_item->setText(1, new_path);
            destination_item->addChild(moved_item);
            event->accept();
        } else {
            event->ignore();
        }
    }
}
