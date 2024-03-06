#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QStringList>
#include <QSqlDatabase>
#include <QVariantList>
#include "general.h"
#include "../controllers/initdb.h"

namespace GeneralModel {

    int createTableRow(const QString& table_name, const QHash<QString,QVariant>& fields) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        for (auto it = fields.begin(); it != fields.end(); ++it) {
            field_names << it.key();
        }
        query.prepare("INSERT INTO " + table_name + " (" + field_names.join(", ") + ") VALUES (:" + field_names.join(", :") + ")");
        for (auto it = fields.begin(); it != fields.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }

        int row_id = -1;
        if (query.exec()) {
            row_id = query.lastInsertId().toInt();
        }

        db.close();
        return row_id;
    }


    bool setTableRowFields(const QString& table_name, int row_id, const QHash<QString,QVariant>& fields) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        for (auto it = fields.begin(); it != fields.end(); ++it) {
            field_names << it.key() + " = :" + it.key();
        }
        query.prepare("UPDATE " + table_name + " SET " + field_names.join(", ") + " WHERE id = :id");
        for (auto it = fields.begin(); it != fields.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }
        query.bindValue(":id", row_id);
        bool success = query.exec();
        db.close();
        return success;
    }


    QHash<QString,QVariant> getTableRow(const QString& table_name, int row_id, const QStringList& fields) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        if (fields.isEmpty()) {
            field_names << "*";
        } else {
            field_names = fields;
        }

        query.prepare("SELECT " + field_names.join(", ") + " FROM " + table_name + " WHERE id = :id");
        query.bindValue(":id", row_id);
        QHash<QString,QVariant> row;

        if(query.exec()){
            if (query.first()) {
                if (!fields.isEmpty()){
                    for (auto it = field_names.begin(); it != field_names.end(); ++it) {
                        row[*it] = query.value(*it);
                    }
                } else {
                    for (int i = 0; i < query.record().count(); ++i) {
                        row[query.record().fieldName(i)] = query.value(i);
                    }
                }
            }
        } else {
            row["error"] = query.lastError().text();
        }
        db.close();
        return row;
    }


    QHash<QString,QVariant> getTableRow(const QString& table_name, const QHash<QString,QVariant>& filters, const QStringList& fields) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        if (fields.isEmpty()) {
            field_names << "*";
        } else {
            field_names = fields;
        }

        QStringList filter_names;
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            filter_names << it.key() + " = :" + it.key();
        }

        query.prepare("SELECT " + field_names.join(", ") + " FROM " + table_name + " WHERE " + filter_names.join(" AND "));
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }

        QHash<QString,QVariant> row;
        if(query.exec()){
            if (query.first()) {
                if (!fields.isEmpty()){
                    for (auto it = field_names.begin(); it != field_names.end(); ++it) {
                        row[*it] = query.value(*it);
                    }
                } else {
                    for (int i = 0; i < query.record().count(); ++i) {
                        row[query.record().fieldName(i)] = query.value(i);
                    }
                }
            }
        } else {
            row["error"] = query.lastError().text();
        }
        db.close();
        return row;
    }


    int getTableRowID(const QString& table_name, const QHash<QString,QVariant>& filters) {
        int row_id = -1;
        QHash<QString,QVariant> row = getTableRow(table_name, filters, QStringList{"id"});
        if (row.contains("id")) {
            row_id = row.value("id").toInt();
        } else if (row.contains("error")) {
            qDebug() << row.value("error").toString();
        }
        return row_id;
    }


    QHash<int,QHash<QString,QVariant>> getTableRows(const QString& table_name, const QVector<int>& row_ids, const QStringList& fields){
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;

        QStringList field_names;
        if (fields.isEmpty()) {
            field_names << "*";
        } else {
            field_names = fields;
        }
        QVariantList ids;
        for (int id : row_ids) {
            ids << id;
        }

        query.prepare("SELECT " + field_names.join(", ") + " FROM " + table_name + " WHERE id IN (:ids)");
        query.bindValue(":ids",ids);

        QHash<int,QHash<QString,QVariant>> rows;
        if(query.exec()){
            while (query.next()) {
                QHash<QString,QVariant> row;
                if (!fields.isEmpty()){
                    for (auto it = field_names.begin(); it != field_names.end(); ++it) {
                        row[*it] = query.value(*it);
                    }
                } else {
                    for (int i = 0; i < query.record().count(); ++i) {
                        row[query.record().fieldName(i)] = query.value(i);
                    }
                }
                rows[query.value("id").toInt()] = row;
            }
        } else {
            QHash<QString,QVariant> row;
            row["error"] = query.lastError().text();
            rows[-1] = row;
        }

        db.close();
        return rows;
    }


    QHash<int,QHash<QString,QVariant>> getTableRows(const QString& table_name,const QHash<QString,QVariant>& filters, const QStringList& fields) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        if (fields.isEmpty()) {
            field_names << "*";
        } else {
            field_names = fields;
        }

        QStringList filter_names;
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            filter_names << it.key() + " = :" + it.key();
        }

        query.prepare("SELECT " + field_names.join(", ") + " FROM " + table_name + " WHERE " + filter_names.join(" AND "));
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }

        QHash<int,QHash<QString,QVariant>> rows;
        if(query.exec()){
            while (query.next()) {
                QHash<QString,QVariant> row;
                if (!fields.isEmpty()){
                    for (auto it = field_names.begin(); it != field_names.end(); ++it) {
                        row[*it] = query.value(*it);
                    }
                } else {
                    for (int i = 0; i < query.record().count(); ++i) {
                        row[query.record().fieldName(i)] = query.value(i);
                    }
                }
                rows[query.value("id").toInt()] = row;
            }
        } else {
            QHash<QString,QVariant> row;
            row["error"] = query.lastError().text();
            rows[-1] = row;
        }

        db.close();
        return rows;
    }


    QVector<QHash<QString,QVariant>> getTableOrderedRows(const QString& table_name, const QString& order_by, const QHash<QString,QVariant>& filters, const QStringList& fields,const QString& order){
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        if (fields.isEmpty()) {
            field_names << "*";
        } else {
            field_names = fields;
        }

        QStringList filter_names;
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            filter_names << it.key() + " = :" + it.key();
        }

        query.prepare("SELECT " + field_names.join(", ") + " FROM " + table_name + " WHERE " + filter_names.join(" AND ") + " ORDER BY " + order_by + " " + order);
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }

        QVector<QHash<QString,QVariant>> rows;
        if(query.exec()){
            while (query.next()) {
                QHash<QString,QVariant> row;
                if (!fields.isEmpty()){
                    for (auto it = field_names.begin(); it != field_names.end(); ++it) {
                        row[*it] = query.value(*it);
                    }
                } else {
                    for (int i = 0; i < query.record().count(); ++i) {
                        row[query.record().fieldName(i)] = query.value(i);
                    }
                }
                rows.append(row);
            }
        } else {
            QHash<QString,QVariant> row;
            row["error"] = query.lastError().text();
            rows.append(row);
        }
        db.close();
        return rows;
    }


    QHash<int,QHash<QString,QVariant>> getTableRowsPartialFilter(const QString& table_name, const QString& filter_name, const QString& value, const QStringList& fields) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList field_names;
        if (fields.isEmpty()) {
            field_names << "*";
        } else {
            field_names = fields;
        }

        query.prepare("SELECT " + field_names.join(", ") + " FROM " + table_name + " WHERE " + filter_name + " LIKE :value");
        query.bindValue(":value", "%" + value + "%");

        QHash<int,QHash<QString,QVariant>> rows;
        if(query.exec()){
            while (query.next()) {
                QHash<QString,QVariant> row;
                if (!fields.isEmpty()){
                    for (auto it = field_names.begin(); it != field_names.end(); ++it) {
                        row[*it] = query.value(*it);
                    }
                } else {
                    for (int i = 0; i < query.record().count(); ++i) {
                        row[query.record().fieldName(i)] = query.value(i);
                    }
                }
                rows[query.value("id").toInt()] = row;
            }
        } else {
            QHash<QString,QVariant> row;
            row["error"] = query.lastError().text();
            rows[-1] = row;
        }
        db.close();
        return rows;
    }


    bool deleteTableRow(const QString& table_name, int row_id) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        query.prepare("DELETE FROM " + table_name + " WHERE id = :id");
        query.bindValue(":id", row_id);
        bool success = query.exec();
        db.close();
        return success;
    }


    bool deleteTableRows(const QString& table_name, const QHash<QString,QVariant>& filters) {
        QSqlDatabase db = InitDBController::openDB();
        QSqlQuery query;
        QStringList filter_names;
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            filter_names << it.key() + " = :" + it.key();
        }
        query.prepare("DELETE FROM " + table_name + " WHERE " + filter_names.join(" AND "));
        for (auto it = filters.begin(); it != filters.end(); ++it) {
            query.bindValue(":" + it.key(), it.value());
        }
        bool success = query.exec();
        db.close();
        return success;
    }

}
