#ifndef UTILS_LOGGER_H
#define UTILS_LOGGER_H

#include <QString>

namespace Logger {

    void setupCustomLogger();
    void showInfoMessage(const QString& message);
    void showErrorMessage(const QString& message);
    void showFatalMessage(const QString& message);
}

#endif // UTILS_LOGGER_H
