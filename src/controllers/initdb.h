#ifndef CONTROLLERS_INITDB_H
#define CONTROLLERS_INITDB_H

#include <QSqlDatabase>

namespace InitDBController {
    // ====== Database initialization functions ====== //
    void initDB();
    QSqlDatabase openDB();

    // ====== Table creation functions ====== //
    bool createTables(QSqlDatabase& db);
    bool createUsersTable(QSqlDatabase& db);
    bool createClassesTable(QSqlDatabase& db);
    bool createSubjectsTable(QSqlDatabase& db);
    bool createStudentsTable(QSqlDatabase& db);
    bool createSanctionsTable(QSqlDatabase& db);
    bool createGradesTable(QSqlDatabase& db);
    bool createAssiduityTable(QSqlDatabase& db);
    bool createReportsTable(QSqlDatabase& db);
    bool createGradedActivitiesTable(QSqlDatabase& db);
    bool createUngradedActivitiesTable(QSqlDatabase& db);
    bool createSchedulesTable(QSqlDatabase& db);
    bool createThemesTable(QSqlDatabase& db);

}

#endif // CONTROLLERS_INITDB_H
