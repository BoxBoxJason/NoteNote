#include "utils.h"

#include <QRegularExpression>

namespace AuthUtils {

    bool checkEmailFormat(const QString& email) {
        QRegularExpression email_regex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return email_regex.match(email).hasMatch();
    }


    bool checkPasswordFormat(const QString& password) {
        QRegularExpression password_regex(R"([a-zA-Z0-9!@#$%^&*()_+]{8,})");
        return password_regex.match(password).hasMatch();
    }


    bool checkNameFormat(const QString& name) {
        QRegularExpression name_regex(R"(^[\p{L}-]+$)");
        return name_regex.match(name).hasMatch();
    }
}