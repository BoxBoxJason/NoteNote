#include "formatutils.h"

namespace FormatUtils {
    QString capitalize(const QString& str) {
        QString capitalized;
        if (! str.isEmpty()){
            capitalized = str[0].toUpper() + str.mid(1).toLower();
        }
        return capitalized;
    }
}
