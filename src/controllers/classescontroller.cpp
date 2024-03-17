#include "classescontroller.h"
#include "../models/classesmodel.h"
#include "../utils/formatutils.h"

namespace ClassesController {

    QStringList getClasses(){
        QStringList classes;
        QHash<int,QHash<QString,QVariant>> classes_data = ClassesModel::getClasses(QHash<QString,QVariant>(), QStringList{"id","name"});
        for(auto it = classes_data.begin(); it != classes_data.end(); it++){
            QString class_name = it.value()["name"].toString().trimmed();
            if (! class_name.isEmpty())
                classes.append(class_name);
        }
        return classes;
    }


    QStringList getSubjects(int class_id){
        QStringList subjects_raw;
        QHash<QString,QVariant> class_data = ClassesModel::getClass(class_id, QStringList{"subjects"});
        return FormatUtils::formatStringList(class_data["subjects"].toString());
    }


    QStringList getSubjects(const QString& class_name){
        QStringList subjects_raw;
        QHash<QString,QVariant> class_data = ClassesModel::getClass(QHash<QString,QVariant>{{"name",class_name}}, QStringList{"subjects"});
        return FormatUtils::formatStringList(class_data["subjects"].toString());
    }


    QString getDivision(int class_id){
        QHash<QString,QVariant> class_data = ClassesModel::getClass(class_id, QStringList{"division"});
        return class_data["division"].toString();
    }


    QString getDivision(const QString& class_name){
        QHash<QString,QVariant> class_data = ClassesModel::getClass(QHash<QString,QVariant>{{"name",class_name}}, QStringList{"division"});
        return class_data["division"].toString();
    }


    QHash<QString,QVariant> getClassSubjectsAndDivision(const QString& class_name){
        return ClassesModel::getClass(QHash<QString,QVariant>{{"name",class_name}}, QStringList{"subjects","division"});
    }

}
