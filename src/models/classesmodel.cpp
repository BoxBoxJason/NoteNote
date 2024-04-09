#include "models/classesmodel.h"
#include "models/general.h"

namespace ClassesModel {

    int createClass(const QHash<QString,QVariant>& fields){
        return GeneralModel::createTableRow("Classes", fields);
    }


    int createClass(const QString& name, const QString& time_division, const QString& year_id, const QStringList& subjects){
        return createClass(QHash<QString,QVariant>{
            {"name", name},
            {"time_division", time_division},
            {"year_id", year_id},
            {"subjects", subjects}
        });
    }


    bool setClassFields(int class_id, const QHash<QString,QVariant>& fields){
        return GeneralModel::setTableRowFields("Classes", class_id, fields);
    }


    QHash<QString,QVariant> getClass(int class_id, const QStringList& fields){
        return GeneralModel::getTableRow("Classes", class_id, fields);
    }


    QHash<QString,QVariant> getClass(const QHash<QString,QVariant>& filters, const QStringList& fields){
        return GeneralModel::getTableRow("Classes", filters, fields);
    }


    QHash<int,QHash<QString,QVariant>> getClasses(const QHash<QString,QVariant>& filters, const QStringList& fields){
        return GeneralModel::getTableRows("Classes", filters, fields);
    }


    bool deleteClasse(int class_id){
        return GeneralModel::deleteTableRow("Classes", class_id);
    }

    bool deleteClasses(const QHash<QString,QVariant>& filters){
        return GeneralModel::deleteTableRows("Classes", filters);
    }
}
