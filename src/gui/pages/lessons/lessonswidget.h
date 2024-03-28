#ifndef GUI_PAGES_LESSONS_LESSONSWIDGET_H
#define GUI_PAGES_LESSONS_LESSONSWIDGET_H

#include <QTreeWidget>
#include <QJsonArray>
#include "lessonscontextmenu.h"

class LessonsWidget : public QTreeWidget {
    /**
     * @class LessonsWidget
     * @brief An UI based widget to display the lessons file system.
     * @details The widget provides a tree view of the file system and allows user to interact with the file system.
    */
    Q_OBJECT

public:
    LessonsWidget(QWidget* parent = nullptr);

protected:
    /**
     * @brief Moves the item to its new destination.
     * @param event The drop event.
    */
    void dropEvent(QDropEvent* event) override;

private:
    // Context menu for the lessons widget.
    LessonsContextMenu* context_menu;

private slots:
    /**
     * @brief Slot to handle item changed event.
     * @details Checks if the new item name is valid and updates the file system.
     * @param item The item that was changed.
     * @param column The column that was changed.
    */
    void onItemChanged(QTreeWidgetItem* item, int column);
    /**
     * @brief Slot to handle file system loading.
     * @details Loads the file system into the lessons widget.
     * @param parent_item The parent item to load the file system.
     * @param file_system The file system to load.
    */
    void loadFileSystem(QTreeWidgetItem& parent_item, const QJsonArray& json_file_system);
    /**
     * @brief Slot to handle folder closed event.
     * @details Updates the folder icon when the folder is closed.
     * @param item The folder item that was closed.
    */
    void folderClosed(QTreeWidgetItem* item);
    /**
     * @brief Slot to handle folder opened event.
     * @details Updates the folder icon when the folder is opened.
     * @param item The folder item that was opened.
    */
    void folderOpened(QTreeWidgetItem* item);
    void showContextMenu(const QPoint& pos);

};

#endif // GUI_PAGES_LESSONS_LESSONSWIDGET_H
