#ifndef UTILS_SESSIONMANAGER_HPP
#define UTILS_SESSIONMANAGER_HPP

#include <QMutex>
#include <QMutexLocker>
#include <QSqlDatabase>

class SessionManager {

public:
    static SessionManager& instance() {
        static SessionManager _instance;
        return _instance;
    }

    void setUserId(int user_id) {
        QMutexLocker locker(&mutex);
        this->user_id = user_id;
    }

    int getUserId() {
        QMutexLocker locker(&mutex);
        return user_id;
    }

private:
    int user_id;
    QMutex mutex;

    // Private constructor and =delete on copy constructor and assignment operator for Singleton pattern
    SessionManager() {}
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

};


class DatabaseManager {

public:
    static DatabaseManager& instance() {
        static DatabaseManager _instance;
        return _instance;
    }

    void setDatabase(const QSqlDatabase& path) {
        QMutexLocker locker(&mutex);
        this->database_path = path;
    }

    QSqlDatabase getDatabase() {
        QMutexLocker locker(&mutex);
        return database_path;
    }

private:
    QSqlDatabase database_path;
    QMutex mutex;

    // Private constructor and =delete on copy constructor and assignment operator for Singleton pattern
    DatabaseManager() {}
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

};

#endif // UTILS_SESSIONMANAGER_HPP
