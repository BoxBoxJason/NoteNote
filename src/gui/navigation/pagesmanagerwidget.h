#ifndef GUI_NAVIGATION_PAGESMANAGERWIDGET_H
#define GUI_NAVIGATION_PAGESMANAGERWIDGET_H

#include <QWidget>
#include "../pages/schedules/scheduleswidget.h"
#include "../pages/students/studentswidget.h"
#include "../pages/grades/gradeswidget.h"
#include "../pages/reports/reportswidget.h"
#include "../pages/lessons/lessonswidget.h"
#include "../pages/themes/themeswidget.h"
#include "../pages/activities/graded/gradedactivitieswidget.h"
#include "../pages/activities/ungraded/ungradedactivitieswidget.h"
#include "../pages/assiduity/absences/absenceswidget.h"
#include "../pages/assiduity/lates/lateswidget.h"
#include "../auth/authwidget.h"

class PagesManagerWidget : public QWidget
{
    Q_OBJECT

public:
    PagesManagerWidget(QWidget* parent = nullptr);
    ~PagesManagerWidget();

private slots:
    void login(int user_id);
    void logout();

private:
    SchedulesWidget* schedules_widget;
    StudentsWidget* students_widget;
    GradesWidget* grades_widget;
    ReportsWidget* reports_widget;
    LessonsWidget* lessons_widget;
    ThemesWidget* themes_widget;
    GradedActivitiesWidget* graded_activities_widget;
    UngradedActivitiesWidget* ungraded_activities_widget;
    AbsencesWidget* absences_widget;
    LatesWidget* lates_widget;
    AuthWidget* auth_widget;

};

#endif // GUI_NAVIGATION_PAGESMANAGERWIDGET_H
