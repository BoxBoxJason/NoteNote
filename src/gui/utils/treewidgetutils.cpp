#include <QStringList>
#include "treewidgetutils.h"

namespace TreeWidgetUtils {

    QJsonArray serializeTree(QTreeWidgetItem* root_item, const QStringList& headers) {
        QJsonArray json_array;
        for (int i = 0; i < root_item->childCount(); i++) {
            QJsonObject json_object;
            QTreeWidgetItem* item = root_item->child(i);
            for (int j = 0; j < headers.size(); j++) {
                json_object[headers[j]] = item->text(j);
            }
            if (item->childCount() > 0) {
                json_object["children"] = serializeTree(item);
            }
            json_array.append(json_object);
        }
        return json_array;
    }

}