#include "formatutils.h"

namespace FormatUtils {

    QString capitalize(const QString& str) {
        QString capitalized;
        if (! str.isEmpty()){
            capitalized = str[0].toUpper() + str.mid(1).toLower();
        }
        return capitalized;
    }


    QStringList formatStringList(const QString& str) {
        QStringList formatted;
        if (! str.isEmpty()){
            QStringList split_list = str.split(",");
            for(auto it = split_list.begin(); it != split_list.end(); it++){
                QString sanitized_str = it->trimmed();
                if (!sanitized_str.isEmpty()){
                    formatted.append(sanitized_str);
                }
            }
        }
        return formatted;
    }
}
