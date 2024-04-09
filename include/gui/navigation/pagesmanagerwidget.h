#ifndef GUI_NAVIGATION_PAGESMANAGERWIDGET_H
#define GUI_NAVIGATION_PAGESMANAGERWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include <QMap>
#include "gui/pages/schedules/scheduleswidget.h"
#include "gui/pages/students/studentswidget.h"
#include "gui/pages/grades/gradeswidget.h"
#include "gui/pages/reports/reportswidget.h"
#include "gui/pages/lessons/lessonswidget.h"
#include "gui/pages/themes/themeswidget.h"
#include "gui/pages/activities/graded/gradedactivitieswidget.h"
#include "gui/pages/activities/ungraded/ungradedactivitieswidget.h"
#include "gui/pages/assiduity/absences/absenceswidget.h"
#include "gui/pages/assiduity/lates/lateswidget.h"
#include "gui/pages/sanctions/sanctionswidget.h"
#include "gui/pages/settings/settingswidget.h"
#include "gui/auth/authwidget.h"

class PagesManagerWidget : public QWidget {
    Q_OBJECT

public:
    PagesManagerWidget(QWidget* parent = nullptr);

public slots:
    void changePage(const QString& page_name);

private slots:
    void login(int user_id);

private:
    QString current_page="auth";
    QStackedLayout* stacked_layout;
    AuthWidget* auth_widget;
    const QMap<QString, std::function<QWidget*()>> WIDGET_MAP = {
        {"schedules", [this](){ return new SchedulesWidget(this); }},
        {"students", [this](){ return new StudentsWidget(this); }},
        {"grades", [this](){ return new GradesWidget(this); }},
        {"reports", [this](){ return new ReportsWidget(this); }},
        {"lessons", [this](){ return new LessonsWidget(this); }},
        {"themes", [this](){ return new ThemesWidget(this); }},
        {"gradedactivities", [this](){ return new GradedActivitiesWidget(this); }},
        {"ungradedactivities", [this](){ return new UngradedActivitiesWidget(this); }},
        {"absences", [this](){ return new AbsencesWidget(this); }},
        {"lates", [this](){ return new LatesWidget(this); }},
        {"sanctions", [this](){ return new SanctionsWidget(this); }},
        {"settings", [this](){ return new SettingsWidget(this); }}
    };
};

#endif // GUI_NAVIGATION_PAGESMANAGERWIDGET_H
