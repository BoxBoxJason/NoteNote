#ifndef MODELS_CLASSESMODEL_H
#define MODELS_CLASSESMODEL_H

#include <QString>
#include <QHash>
#include <QVariant>
#include <QStringList>

namespace ClassesModel {

    // ===== POST FUNCTIONS ===== //
    int createClass(const QString& name, const QString& time_division, const QString& year_id, const QStringList& subjects);
    int createClass(const QHash<QString,QVariant>& fields);

    // ===== PUT FUNCTIONS ===== //
    bool setClassFields(int class_id, const QHash<QString,QVariant>& fields);

    // ===== GET FUNCTIONS ===== //
    QHash<QString,QVariant> getClass(int class_id, const QStringList& fields = QStringList());
    QHash<QString,QVariant> getClass(const QHash<QString,QVariant>& filters = QHash<QString,QVariant>(), const QStringList& fields = QStringList());
    QHash<int,QHash<QString,QVariant>> getClasses(const QHash<QString,QVariant>& filters = QHash<QString,QVariant>(), const QStringList& fields = QStringList());

    // ===== DELETE FUNCTIONS ===== //
    bool deleteClasse(int class_id);
    bool deleteClasses(const QHash<QString,QVariant>& filters);
}
#endif // MODELS_CLASSESMODEL_H
