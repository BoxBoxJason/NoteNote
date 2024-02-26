#ifndef GUI_PAGES_ACTIVITIES_UNGRADED_UNGRADEDACTIVITIESWIDGET_H
#define GUI_PAGES_ACTIVITIES_UNGRADED_UNGRADEDACTIVITIESWIDGET_H

#include "../activitieswidget.h"

class UngradedActivitiesWidget : public ActivitiesWidget
{
    Q_OBJECT

public:
    UngradedActivitiesWidget(QWidget* parent = nullptr);
    ~UngradedActivitiesWidget();
};

#endif // GUI_PAGES_ACTIVITIES_UNGRADED_UNGRADEDACTIVITIESWIDGET_H
