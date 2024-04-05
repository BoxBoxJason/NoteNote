#ifndef GUI_PAGES_THEMES_THEMESTREEWIDGET
#define GUI_PAGES_THEMES_THEMESTREEWIDGET

#include <QTreeWidget>
#include <QJsonArray>
#include "themescontextmenu.h"

class ThemesTreeWidget : public QTreeWidget {
    /**
     * @class ThemesTreeWidget
     * @brief An UI based widget to display themes.
     * @details The tree widget displays the themes in a tree structure.
    */
    Q_OBJECT

public:
    ThemesTreeWidget(QWidget* parent = nullptr);

public slots:
    /**
     * @brief displayThemes Displays the themes in the tree widget
     * @details Unpacks the Themes JSON object and displays the themes in the tree widget
     * @param themes_json The JSON object containing the themes  
    */
    void displayThemes(QTreeWidgetItem& parent_item, const QJsonArray& themes_json);

private slots:
    /**
     * @brief onItemChanged Slot to handle item changes
     * @details Slot to handle item changes
     * @param item The item that was changed
     * @param column The column that was changed
    */
    void onItemChanged(QTreeWidgetItem* item, int column);
    /**
     * @brief showContextMenu Slot to show the context menu
     * @details Prepares the context menu and shows it at the requested position
     * @param pos The position of the context menu
    */
    void showContextMenu(const QPoint& pos);

private:
    ThemesContextMenu* context_menu;

};

#endif // GUI_PAGES_THEMES_THEMESTREEWIDGET
