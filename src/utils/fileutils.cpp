#include <QRegularExpression>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QJsonArray>
#include "fileutils.h"


static const QStringList RESERVED_NAMES = {"CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};
static const QRegularExpression RESERVED_CHARS = QRegularExpression("[\\\\:*?\"<>|]");

namespace FileUtils {

    QString CUSTOM_FS_ROOT_DIR() {
        return QDir(QApplication::applicationDirPath()).filePath("lessons");
    }


    bool checkFileNameValid(const QString& file_name) {
        return ! (file_name.isEmpty() || file_name.contains(RESERVED_CHARS) || RESERVED_NAMES.contains(file_name));
    }


    bool checkPathValid(const QString& path) {
        return ! (path.isEmpty() || path.contains(RESERVED_CHARS) || RESERVED_NAMES.contains(path));
    }


    QJsonArray constructFileSystemJson(const QString& dir_path) {
        QJsonArray json_fs;
        QFileInfo file_info(dir_path);
        if (file_info.exists() && file_info.isDir()) {
            QDir directory(dir_path);
            for (const QFileInfo& child : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden)) {
                QJsonObject child_json;
                child_json["path"] = child.absoluteFilePath();
                child_json["name"] = child.fileName();
                child_json["type"] = child.isDir() ? "directory" : "file";
                child_json["extension"] = child.suffix();
                if (child.isDir()) {
                    child_json["children"] = constructFileSystemJson(child.absoluteFilePath());
                }
                json_fs.append(child_json);
            }
        }
        return json_fs;
    }


    bool createPath(bool is_dir, const QString& path) {
        bool success = false;
        if (is_dir) {
            success = QDir().mkpath(path);
        } else {
            QFile file(path);
            if (file.open(QIODevice::WriteOnly)) {
                file.close();
                QDesktopServices::openUrl(QUrl::fromLocalFile(path));
                success = true;
            }
        }
        return success;
    }


    bool deletePath(const QString& path) {
        bool success = false;
        if (QFileInfo(path).isDir()) {
            success = QDir(path).removeRecursively();
        } else {
            success = QFile(path).remove();
        }
        return success;
    }

}
