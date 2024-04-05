#ifndef MODELS_GENERAL_H
#define MODELS_GENERAL_H

#include <QString>
#include <QStringList>
#include <QHash>
#include <QVariant>
#include <QVector>

namespace GeneralModel {
    // ===== POST FUNCTIONS ===== //
    int createTableRow(const QString& table_name, const QHash<QString,QVariant>& fields);

    // ===== PUT FUNCTIONS ===== //
    bool setTableRowFields(const QString& table_name, int row_id, const QHash<QString,QVariant>& fields);

    // ===== GET FUNCTIONS ===== //
    QHash<QString,QVariant> getTableRow(const QString& table_name, int row_id, const QStringList& fields = QStringList());
    QHash<QString,QVariant> getTableRow(const QString& table_name, const QHash<QString,QVariant>& filters, const QStringList& fields = QStringList());
    int getTableRowID(const QString& table_name, const QHash<QString,QVariant>& filters);
    QHash<int,QHash<QString,QVariant>> getTableRows(const QString& table_name, const QVector<int>& row_ids, const QStringList& fields = QStringList());
    QHash<int,QHash<QString,QVariant>> getTableRows(const QString& table_name,const QHash<QString,QVariant>& filters = QHash<QString,QVariant>(), const QStringList& fields = QStringList());
    QVector<QHash<QString,QVariant>> getTableOrderedRows(const QString& table_name, const QString& order_by, const QHash<QString,QVariant>& filters = QHash<QString,QVariant>(), const QStringList& fields = QStringList(),const QString& order = "ASC");
    QHash<int,QHash<QString,QVariant>> getTableRowsPartialFilter(const QString& table_name, const QString& filter_name, const QString& value, const QStringList& fields = QStringList());

    // ===== DELETE FUNCTIONS ===== //
    bool deleteTableRow(const QString& table_name, int row_id);
    bool deleteTableRows(const QString& table_name, const QHash<QString,QVariant>& filters);

}

#endif // MODELS_GENERAL_H
