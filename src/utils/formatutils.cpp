#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include "formatutils.h"

namespace FormatUtils {

    QString capitalize(const QString& str) {
        QString capitalized;
        if (! str.isEmpty()){
            capitalized = str[0].toUpper() + str.mid(1).toLower();
        }
        return capitalized;
    }


    QStringList formatStringList(const QString& str) {
        QStringList formatted;
        if (! str.isEmpty()){
            QStringList split_list = str.split(",");
            for(auto it = split_list.begin(); it != split_list.end(); it++){
                QString sanitized_str = it->trimmed();
                if (!sanitized_str.isEmpty()){
                    formatted.append(sanitized_str);
                }
            }
        }
        return formatted;
    }


    QString formatGrade(const QString& grade) {
        QStringList non_taken_grades;
        QFile variables_json_file(":enums/nontakengrades.json");
        if (variables_json_file.open(QFile::ReadOnly)) {
            QJsonObject non_taken_grades_dict = QJsonDocument::fromJson(variables_json_file.readAll()).object();
            variables_json_file.close();
            for (QJsonValue non_taken_value : non_taken_grades_dict) {
                non_taken_grades.append(non_taken_value.toString());
            }
        }
        QString floatable = "N/A";
        if (! non_taken_grades.contains(grade)){
            floatable = grade;
        } else if (! grade.isEmpty()) {
            bool conversion_ok;
            double grade_float = QString(grade).replace(",",".").toDouble(&conversion_ok);
            if (conversion_ok) {
                floatable = QString::number(grade_float,'f',2);
            }
        }
        return floatable;
    }
}
