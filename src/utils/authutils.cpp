#include "authutils.h"

#include <QRegularExpression>
#include <QCryptographicHash>
#include <QUuid>

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


    QString generateRandomSalt() {
        QUuid uuid = QUuid::createUuid();
        QString uuidString = uuid.toString(QUuid::WithoutBraces);
        QByteArray hash = QCryptographicHash::hash(uuidString.toUtf8(), QCryptographicHash::Sha256);
        return QString(hash.toHex());
    }


    QString hashPassword(const QString& password, const QString& salt) {
        QByteArray salted_password = (password + salt).toUtf8();
        QByteArray hash = QCryptographicHash::hash(salted_password, QCryptographicHash::Sha256);
        return QString(hash.toHex());
    }


    bool checkPasswordMatchesHash(const QString& password, const QString& hashed_password, const QString& salt) {
        return hashed_password == hashPassword(password, salt);
    }

}