#include <QApplication>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include "initdb.h"
#include "../utils/exceptions.hpp"
#include "../utils/logger.h"

namespace InitDBController {

    QString DB_ABSOLUTE_PATH;
    QString DB_FILE_NAME = "notenote.db";

    void initDB() {
        try {
            DB_ABSOLUTE_PATH = QDir::cleanPath(QDir(QApplication::applicationDirPath()).filePath(DB_FILE_NAME));
            qDebug() << "Database path: " << DB_ABSOLUTE_PATH;
            QSqlDatabase db = openDB();
            createTables(db);
            db.close();
        } catch (DatabaseException& e) {
            qCritical() << e.message();
            Logger::showFatalMessage(e.message());
        }
    }


    QSqlDatabase openDB() {
        QSqlDatabase db;
        if (QSqlDatabase::contains("qt_sql_default_connection")) {
            db = QSqlDatabase::database("qt_sql_default_connection");
        } else {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(DB_ABSOLUTE_PATH);
        }
        if (db.open()) {
            qDebug() << "Database: connection ok";
        } else {
            throw DatabaseException("Database: connection failed: " + db.lastError().text());
        }
        return db;
    }


    bool createTables(QSqlDatabase& db) {
        bool success = true;
        success &= createUsersTable(db);
        success &= createClassesTable(db);
        success &= createStudentsTable(db);
        success &= createSubjectsTable(db);
        success &= createSanctionsTable(db);
        success &= createGradesTable(db);
        success &= createAssiduityTable(db);
        success &= createReportsTable(db);
        success &= createGradedActivitiesTable(db);
        success &= createUngradedActivitiesTable(db);
        success &= createSchedulesTable(db);
        success &= createThemesTable(db);
        if (success) {
            qDebug() << "Database: tables created";
        } else {
            db.rollback();
            throw DatabaseException("Database: tables creation failed: " + db.lastError().text());
        }
        return success;
    }


    bool createUsersTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        return query.exec("CREATE TABLE IF NOT EXISTS Users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "first_name TEXT NOT NULL,"
            "last_name TEXT NOT NULL,"
            "email TEXT NOT NULL UNIQUE,"
            "hashed_password TEXT NOT NULL,"
            "salt TEXT NOT NULL"
        ")");
        qDebug() << "Database: Users table created";
    }


    bool createClassesTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Classes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"                           // Class name
            "year_id TEXT NOT NULL,"                        // Class year id
            "subjects_ids TEXT NOT NULL"                   // Class subjects ids
        ")");
        if (success) {
            qDebug() << "Database: Classes table created";
        } else {
            qCritical() << "Database: Classes table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createStudentsTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "first_name TEXT NOT NULL,"                     // Student first name
            "last_name TEXT NOT NULL,"                      // Student last name
            "year_id TEXT NOT NULL,"                        // Student year id
            "class_id TEXT NOT NULL,"                       // Student class id
            "subjects_ids TEXT NOT NULL,"                   // Student subjects ids
            "FOREIGN KEY (class_id) REFERENCES Classes(id) ON DELETE CASCADE"
        ")");
        if (success) {
            qDebug() << "Database: Students table created";
        } else {
            qCritical() << "Database: Students table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createSanctionsTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Sanctions ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "student_id TEXT NOT NULL,"                     // Involved student id
            "start_date DATETIME NOT NULL,"                 // Sanction start date
            "end_date DATETIME NOT NULL,"                   // Sanction end date
            "type TEXT NOT NULL,"                           // Sanction type
            "reason TEXT NOT NULL,"                         // Sanction reason
            "FOREIGN KEY (student_id) REFERENCES Students(id) ON DELETE CASCADE"
        ")");
        if (success) {
            qDebug() << "Database: Sanctions table created";
        } else {
            qCritical() << "Database: Sanctions table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createUngradedActivitiesTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS UngradedActivities ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"                           // Activity name
            "start_date DATETIME NOT NULL,"                 // Activity start date
            "end_date DATETIME NOT NULL,"                   // Activity end date
            "duration INTEGER NOT NULL,"                    // Activity duration (minutes)
            "type TEXT NOT NULL,"                           // Activity type
            "description TEXT NOT NULL,"                    // Activity description
            "subject_id TEXT NOT NULL,"                     // Activity subject id
            "theme_id TEXT NOT NULL,"                        // Activity theme id
            "FOREIGN KEY (subject_id) REFERENCES Subjects(id),"
            "FOREIGN KEY (theme_id) REFERENCES Themes(id)"
        ")");
        if (success) {
            qDebug() << "Database: UngradedActivities table created";
        } else {
            qCritical() << "Database: UngradedActivities table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createGradedActivitiesTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS GradedActivities ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"                           // Activity name
            "start_date DATETIME NOT NULL,"                 // Activity start date
            "end_date DATETIME NOT NULL,"                   // Activity end date
            "duration INTEGER NOT NULL,"                    // Activity duration (minutes)
            "type TEXT NOT NULL,"                           // Activity type
            "description TEXT NOT NULL,"                    // Activity description
            "bonus BOOLEAN NOT NULL,"                       // Activity bonus
            "coefficient REAL NOT NULL,"                    // Activity coefficient
            "barem REAL NOT NULL,"                          // Activity barem
            "subject_id TEXT NOT NULL,"                     // Activity subject id
            "theme_id TEXT NOT NULL,"                        // Activity theme id
            "FOREIGN KEY (subject_id) REFERENCES Subjects(id),"
            "FOREIGN KEY (theme_id) REFERENCES Themes(id)"
        ")");
        if (success) {
            qDebug() << "Database: GradedActivities table created";
        } else {
            qCritical() << "Database: GradedActivities table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createSubjectsTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Subjects ("
            "name TEXT PRIMARY KEY,"                         // Subject name
            "short_name TEXT NOT NULL"                     // Subject short name
        ")");
        if (success) {
            qDebug() << "Database: Subjects table created";
        } else {
            qCritical() << "Database: Subjects table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createReportsTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Reports ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "student_id TEXT NOT NULL,"                     // Student id
            "type TEXT NOT NULL,"                           // Report type
            "description TEXT NOT NULL"                    // Report description
        ")");
        if (success) {
            qDebug() << "Database: Reports table created";
        } else {
            qCritical() << "Database: Reports table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createGradesTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Grades ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "student_id TEXT NOT NULL,"                     // Student id
            "activity_id TEXT NOT NULL,"                    // Activity id
            "grade REAL NOT NULL,"                          // Student grade
            "FOREIGN KEY (student_id) REFERENCES Students(id) ON DELETE CASCADE,"
            "FOREIGN KEY (activity_id) REFERENCES GradedActivities(id) ON DELETE CASCADE"
        ")");
        if (success) {
            qDebug() << "Database: Grades table created";
        } else {
            qCritical() << "Database: Grades table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createAssiduityTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Assiduity ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "date DATETIME NOT NULL,"                       // Assiduity date
            "duration INTEGER NOT NULL,"                    // Event duration (minutes)
            "subject_id TEXT NOT NULL,"                     // Assiduity subject id
            "student_id TEXT NOT NULL,"                     // Student id
            "FOREIGN KEY (subject_id) REFERENCES Subjects(id) ON DELETE CASCADE,"
            "FOREIGN KEY (student_id) REFERENCES Students(id) ON DELETE CASCADE"
        ")");
        if (success) {
            qDebug() << "Database: Assiduity table created";
        } else {
            qCritical() << "Database: Assiduity table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createSchedulesTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Schedules ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER NOT NULL,"                     // User id
            "events TEXT NOT NULL,"                          // User events (JSON)
            "FOREIGN KEY (user_id) REFERENCES Users(id) ON DELETE CASCADE"
        ")");
        if (success) {
            qDebug() << "Database: Schedules table created";
        } else {
            qCritical() << "Database: Schedules table creation failed: " << query.lastError().text();
        }
        return success;
    }


    bool createThemesTable(QSqlDatabase& db) {
        QSqlQuery query(db);
        bool success = query.exec("CREATE TABLE IF NOT EXISTS Themes ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL,"                           // Theme name
            "subject_id TEXT NOT NULL,"                     // Theme subject id
            "year_id TEXT NOT NULL,"                        // Theme year id
            "FOREIGN KEY (subject_id) REFERENCES Subjects(id) ON DELETE CASCADE"
        ")");
        if (success) {
            qDebug() << "Database: Themes table created";
        } else {
            qCritical() << "Database: Themes table creation failed: " << query.lastError().text();
        }
        return success;
    }
}
