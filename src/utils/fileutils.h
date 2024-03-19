#ifndef UTILS_FILEUTILS_H
#define UTILS_FILEUTILS_H

#include <QString>

namespace FileUtils {
    bool checkFileNameValid(const QString& file_name);
    bool checkPathValid(const QString& path);
}

#endif // UTILS_FILEUTILS_H
