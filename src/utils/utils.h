#ifndef UTILS_UTILS_H
#define UTILS_UTILS_H

#include <QString>

namespace AuthUtils {
    QString generateSalt();
    QString hashPassword(const QString& password, const QString& salt);
    bool checkEmailFormat(const QString& email);
    bool checkPasswordFormat(const QString& password);
    bool checkNameFormat(const QString& name);
}

#endif // UTILS_UTILS_H
