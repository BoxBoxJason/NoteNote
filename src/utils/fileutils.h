#ifndef UTILS_FILEUTILS_H
#define UTILS_FILEUTILS_H

#include <QString>
#include <QJsonObject>
#include <QApplication>

namespace FileUtils {

    QString CUSTOM_FS_ROOT_DIR();

    bool checkFileNameValid(const QString& file_name);
    bool checkPathValid(const QString& path);

    QJsonArray constructFileSystemJson(const QString& dir_path);
    bool createPath(bool is_directory, const QString& path);
    bool deletePath(const QString& path);

}

#endif // UTILS_FILEUTILS_H
