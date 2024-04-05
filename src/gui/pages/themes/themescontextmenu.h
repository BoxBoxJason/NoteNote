#ifndef GUI_PAGES_THEMES_THEMESCONTEXTMENU
#define GUI_PAGES_THEMES_THEMESCONTEXTMENU

#include <QMenu>
#include <QTreeWidgetItem>

class ThemesContextMenu : public QMenu {
    /**
     * @class ThemesContextMenu
     * @brief A custom context menu for the themes widget.
     * @details The context menu provides options to create, rename and delete themes.
    */
    Q_OBJECT

public:
    ThemesContextMenu(QWidget* parent=nullptr);

public slots:
    /**
     * @brief Prepares the context menu based on the selected item.
     * @details Prepares the context menu based on the selected item.
     * @param selected_item The selected item.
    */
    void prepareMenu(QTreeWidgetItem* selected_item);

private:
    QAction* create_new_item;
    QAction* rename_item;
    QAction* delete_item;
    
};

#endif // GUI_PAGES_THEMES_THEMESCONTEXTMENU
