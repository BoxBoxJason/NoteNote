#ifndef GUI_UTILS_TREEWIDGETUTILS_H
#define GUI_UTILS_TREEWIDGETUTILS_H

#include <QTreeWidgetItem>
#include <QJsonArray>
#include <QJsonObject>

namespace TreeWidgetUtils {

    QJsonArray serializeTree(QTreeWidgetItem* root_item);
} 

#endif // GUI_UTILS_TREEWIDGETUTILS_H
