#ifndef GUI_PAGES_REPORTS_REPORTSWIDGET_H
#define GUI_PAGES_REPORTS_REPORTSWIDGET_H

#include <QWidget>
#include <QString>

class ReportsWidget : public QWidget
{
    Q_OBJECT

public:
    ReportsWidget(QWidget* parent = nullptr);
    ~ReportsWidget();

public slots:
    void setTeacherId(int teacher_id);

private:
    void showStudentReport(int student_id, int year_id, int trimester_id);
};

#endif // GUI_PAGES_REPORTS_REPORTSWIDGET_H
