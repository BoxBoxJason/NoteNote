#ifndef CONTROLLERS_UTILS_AUTHUTILS_H
#define CONTROLLERS_UTILS_AUTHUTILS_H

#include <QString>

namespace AuthUtils {
    QString generateRandomSalt();
    QString hashPassword(const QString& password, const QString& salt);
    bool checkEmailFormat(const QString& email);
    bool checkPasswordFormat(const QString& password);
    bool checkNameFormat(const QString& name);
    bool checkPasswordMatchesHash(const QString& password, const QString& hashed_password, const QString& salt);

}

#endif // CONTROLLERS_UTILS_AUTHUTILS_H
