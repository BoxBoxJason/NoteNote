#ifndef CONTROLLERS_USERS_H
#define CONTROLLERS_USERS_H

#include <QString>

namespace UsersController {
    int checkPasswordMatch(const QString& email, const QString& password);
    int checkPasswordMatch(int user_id, const QString& password, const QString& salt);
    int getUserIdFromEmail(const QString& email);

    int checkEmailExists(const QString& email);
    int createUser(const QString& first_name, const QString& last_name, const QString& email, const QString& password);
}

#endif // CONTROLLERS_USERS_H
