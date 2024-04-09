#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include "utils/logger.h"

namespace Logger {

    static QString LOG_FILE_PATH;

    void setupCustomLogger() {
        // Select log file path and create if needed
        LOG_FILE_PATH = QDir::cleanPath(QDir(QApplication::applicationDirPath()).filePath("notenote.log"));
        static QFile log_file(LOG_FILE_PATH);
        log_file.open(QFile::Append | QFile::Text);

        qInstallMessageHandler([](QtMsgType type, const QMessageLogContext &context, const QString &msg) {
            // Select log level
            QString log_level;
            switch (type) {
                case QtDebugMsg:
                    log_level = "DEBUG";
                    break;
                case QtInfoMsg:
                    log_level = "INFO";
                    break;
                case QtWarningMsg:
                    log_level = "WARNING";
                    break;
                case QtCriticalMsg:
                    log_level = "CRITICAL";
                    break;
                case QtFatalMsg:
                    log_level = "FATAL";
                    break;
            }

            // Format message
            QByteArray localMsg = msg.toLocal8Bit();
            QString formattedMessage = QString("%1 (%2): %3 %4\n").arg(
                QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"),
                log_level, localMsg.constData(),context.file ? QString("(%1:%2, %3)").arg(context.file).arg(context.line).arg(context.function) : QString());

            // Output to standard error
            fprintf(stderr, "%s", formattedMessage.toLocal8Bit().constData());
            fflush(stderr);

            // Output to file
            QTextStream out(&log_file);
            out << formattedMessage;
        });

        qDebug() << "Custom logger setup done. Log file path: " + LOG_FILE_PATH;
    }


    void showInfoMessage(const QString& message) {
        QMessageBox info_message;
        info_message.setIcon(QMessageBox::Information);
        info_message.setText(message);
        info_message.exec();
    }


    void showErrorMessage(const QString& message) {
        QMessageBox error_message;
        error_message.setIcon(QMessageBox::Warning);
        error_message.setText(message);
        error_message.exec();
    }


    void showFatalMessage(const QString& message) {
        QMessageBox error_message;
        error_message.setIcon(QMessageBox::Critical);
        error_message.setText(message);
        error_message.exec();
        QApplication::quit();
    }
}
