#ifndef UTILS_EXCEPTIONS_H
#define UTILS_EXCEPTIONS_H

#include <QString>
#include <QException>

class DatabaseException : public QException {
public:
    DatabaseException(const QString& message) : m_message(message) {}
    void raise() const override { throw *this; }
    DatabaseException* clone() const override { return new DatabaseException(*this); }
    QString message() const { return m_message; }
private:
    QString m_message;
};

#endif // UTILS_EXCEPTIONS_H
