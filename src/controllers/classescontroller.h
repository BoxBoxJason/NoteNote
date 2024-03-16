#ifndef CONTROLLERS_CLASSESCONTROLLER_H
#define CONTROLLERS_CLASSESCONTROLLER_H

#include <QHash>
#include <QString>
#include <QStringList>

namespace ClassesController {

    QStringList getClasses();
    QStringList getSubjects(const QString& class_id);
    QString getDivision(const QString& class_id);

}

#endif // CONTROLLERS_CLASSESCONTROLLER_H
