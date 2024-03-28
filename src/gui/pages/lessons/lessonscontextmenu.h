#ifndef GUI_PAGES_LESSONS_LESSONSCONTEXTMENU_H
#define GUI_PAGES_LESSONS_LESSONSCONTEXTMENU_H

#include <QMenu>
#include <QAction>
#include <QTreeWidgetItem>

class LessonsContextMenu : public QMenu {
    /**
     * @class LessonsContextMenu
     * @brief An UI based context menu to allow user to interact with the lessons widget.
     * @details The context menu provides options to create, import, open, rename and delete items.
    */
    Q_OBJECT

public:
    LessonsContextMenu(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Prepare the context menu based on the selected item.
     * @param item The selected item in the lessons widget.
    */
    void prepareMenu(QTreeWidgetItem* item);

private slots:
    /**
     * @brief Starts the file creator dialog widget.
    */
    void createAction();
    /**
     * @brief Starts the file importer dialog widget.
    */
    void importAction();
    /**
     * @brief Opens the selected file with the default system application.
    */
    void openAction();
    /**
     * @brief Renames the selected item in the lessons widget (and in file system).
    */
    void renameAction();
    /**
     * @brief Deletes the selected item in the lessons widget (and from file system).
    */
    void deleteAction();

private:
    // Selected item in the lessons widget.
    QTreeWidgetItem* selected_item;
    // Context menu actions.
    QAction* create_new_item;
    QAction* import_new_item;
    QAction* open_file;
    QAction* rename_item;
    QAction* delete_item;

};

#endif // GUI_PAGES_LESSONS_LESSONSCONTEXTMENU_H
