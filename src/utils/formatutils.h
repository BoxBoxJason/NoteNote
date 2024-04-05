#ifndef UTILS_FORMATUTILS_H
#define UTILS_FORMATUTILS_H

#include <QString>
#include <QStringList>

namespace FormatUtils {
    QString capitalize(const QString& str);
    QStringList formatStringList(const QString& str);
    QString formatGrade(const QString& grade);
}
#endif // UTILS_FORMATUTILS_H
