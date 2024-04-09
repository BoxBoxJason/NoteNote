#ifndef MODELS_USERSMODEL_H
#define MODELS_USERSMODEL_H

#include <QString>
#include <QStringList>
#include <QHash>
#include <QVariant>

namespace UsersModel {
    // ===== POST FUNCTIONS ===== //
    int createUser(const QString& first_name, const QString& last_name, const QString& email, const QString& hashed_password, const QString& salt);
    int createUser(const QHash<QString,QVariant>& fields);

    // ===== PUT FUNCTIONS ===== //
    bool setUserFields(int user_id, const QHash<QString,QVariant>& fields);

    // ===== GET FUNCTIONS ===== //
    QHash<QString,QVariant> getUser(int user_id, const QStringList& fields = QStringList());
    QHash<QString,QVariant> getUser(const QHash<QString,QVariant>& filters = QHash<QString,QVariant>(), const QStringList& fields = QStringList());
    int getUserID(const QString& email);
    QHash<int,QHash<QString,QVariant>> getUsers(const QHash<QString,QVariant>& filters, const QStringList& fields = QStringList());
    
    // ===== DELETE FUNCTIONS ===== //
    bool deleteUser(int user_id);
    bool deleteUsers(const QHash<QString,QVariant>& filters);

}

#endif // MODELS_USERSMODEL_H
