#ifndef CONTROLLERS_CLASSESCONTROLLER_H
#define CONTROLLERS_CLASSESCONTROLLER_H

#include <QHash>
#include <QString>
#include <QStringList>

namespace ClassesController {

    QStringList getClasses();
    QStringList getSubjects(int class_id);
    QStringList getSubjects(const QString& class_name);
    QString getDivision(int class_id);
    QString getDivision(const QString& class_name);
    QHash<QString,QVariant> getClassSubjectsAndDivision(const QString& class_name);

}

#endif // CONTROLLERS_CLASSESCONTROLLER_H
