#ifndef CONTROLLERS_USERSCONTROLLER_H
#define CONTROLLERS_USERSCONTROLLER_H

#include <QString>

namespace UsersController {
    int checkPasswordMatch(const QString& email, const QString& password);
    int getUserIdFromEmail(const QString& email);

    int createUser(const QString& first_name, const QString& last_name, const QString& email, const QString& password);
}

#endif // CONTROLLERS_USERSCONTROLLER_H
