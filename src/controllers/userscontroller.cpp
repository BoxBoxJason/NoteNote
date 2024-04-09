#include "controllers/userscontroller.h"
#include "models/usersmodel.h"
#include "controllers/utils/authutils.h"

namespace UsersController {

    int checkPasswordMatch(const QString& email, const QString& password) {
        QHash<QString, QVariant> user = UsersModel::getUser(QHash<QString, QVariant>{{"email", email}}, QStringList{"id", "hashed_password","salt"});
        int user_id = -1;
        if (!user.contains("error")) {
            QString hashed_password = user["hashed_password"].toString();
            QString salt = user["salt"].toString();
            if (AuthUtils::hashPassword(password, salt) == hashed_password) {
                user_id = user["id"].toInt();
            }
        }
    }


    int getUserIdFromEmail(const QString& email) {
        return UsersModel::getUserID(email);
    }


    int createUser(const QString& first_name, const QString& last_name, const QString& email, const QString& password) {
        QString salt = AuthUtils::generateRandomSalt();
        QString hashed_password = AuthUtils::hashPassword(password, salt);
        UsersModel::createUser(first_name, last_name, email, hashed_password, salt);
    }

}
