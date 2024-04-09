#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "gui/notenote.h"
#include "controllers/initdb.h"
#include "utils/logger.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Logger::setupCustomLogger();
    InitDBController::initDB();

    QFile variables_json_file(":styles/variables.json");
    if (variables_json_file.open(QFile::ReadOnly)) {
        QJsonObject styles_map = QJsonDocument::fromJson(variables_json_file.readAll()).object();
        variables_json_file.close();

        // Load the stylesheet
        QFile file(":styles/notenote.qss");
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            QString stylesheet = stream.readAll();
            // Replace variables placeholders with their values from the JSON file
            for (QString key : styles_map.keys()) {
                QString placeholder = "@" + key + "@";
                stylesheet.replace(placeholder, styles_map.value(key).toString());
            }
            app.setStyleSheet(stylesheet);
            file.close();
        }
    }

    NoteNote notenote;
    notenote.setWindowTitle("NoteNote");
    notenote.resize(800, 600);
    notenote.show();

    return app.exec();
}
