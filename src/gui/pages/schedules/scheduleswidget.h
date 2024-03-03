#ifndef GUI_PAGES_SCHEDULES_SCHEDULESWIDGET_H
#define GUI_PAGES_SCHEDULES_SCHEDULESWIDGET_H

#include <QWidget>
#include <QStackedLayout>
#include "weekview.h"
#include "monthview.h"
#include "dayview.h"

class SchedulesWidget : public QWidget
{
    Q_OBJECT

public:
    SchedulesWidget(QWidget* parent = nullptr);
    ~SchedulesWidget();

public slots:

private:
    QStackedLayout* stacked_layout;
    WeekView* week_view;
    DayView* day_view;
    MonthView* month_view;
};

#endif // GUI_PAGES_SCHEDULES_SCHEDULESWIDGET_H
