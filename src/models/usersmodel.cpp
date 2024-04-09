#include "models/usersmodel.h"
#include "models/general.h"

namespace UsersModel {

    int createUser(const QString& first_name, const QString& last_name, const QString& email, const QString& hashed_password, const QString& salt) {
        return createUser(QHash<QString,QVariant>{
            {"first_name", first_name},
            {"last_name", last_name},
            {"email", email},
            {"hashed_password", hashed_password},
            {"salt", salt}
        });
    }


    int createUser(const QHash<QString,QVariant>& fields) {
        return GeneralModel::createTableRow("Users", fields);
    }


    bool setUserFields(int user_id, const QHash<QString,QVariant>& fields) {
        return GeneralModel::setTableRowFields("Users", user_id, fields);
    }


    QHash<QString,QVariant> getUser(int user_id, const QStringList& fields) {
        return GeneralModel::getTableRow("Users", user_id, fields);
    }


    QHash<QString,QVariant> getUser(const QHash<QString,QVariant>& filters, const QStringList& fields) {
        return GeneralModel::getTableRow("Users", filters, fields);
    }


    int getUserID(const QString& email) {
        return GeneralModel::getTableRowID("Users", QHash<QString,QVariant>{{"email", email}});
    }


    QHash<int,QHash<QString,QVariant>> getUsers(const QHash<QString,QVariant>& filters, const QStringList& fields) {
        return GeneralModel::getTableRows("Users", filters, fields);
    }


    bool deleteUser(int user_id) {
        return GeneralModel::deleteTableRow("Users", user_id);
    }


    bool deleteUsers(const QHash<QString,QVariant>& filters) {
        return GeneralModel::deleteTableRows("Users", filters);
    }

}
