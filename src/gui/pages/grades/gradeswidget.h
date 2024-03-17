#ifndef GUI_PAGES_GRADES_GRADESWIDGET_H
#define GUI_PAGES_GRADES_GRADESWIDGET_H

#include <QWidget>
#include "gradesdisplay.h"

class GradesWidget : public QWidget
{
    Q_OBJECT

public:
    GradesWidget(QWidget* parent = nullptr);

private:
    GradesDisplay* grades_display;

private slots:
    void saveChanges();
    void exportToCSV();
};

#endif // GUI_PAGES_GRADES_GRADESWIDGET_H
