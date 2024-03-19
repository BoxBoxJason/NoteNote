#include "fileutils.h"

#include <QRegularExpression>


static const QStringList RESERVED_NAMES = {"CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};
static const QRegularExpression RESERVED_CHARS = QRegularExpression("[\\\\/:*?\"<>|]");

namespace FileUtils {

    bool checkFileNameValid(const QString& file_name) {
        return ! (file_name.isEmpty() || file_name.contains(RESERVED_CHARS) || RESERVED_NAMES.contains(file_name));
    }

    bool checkPathValid(const QString& path) {
        return ! (path.isEmpty() || path.contains(RESERVED_CHARS) || RESERVED_NAMES.contains(path));
    }
}
