#ifndef GUI_PAGES_ACTIVITIES_GRADED_GRADEDACTIVITIESWIDGET_H
#define GUI_PAGES_ACTIVITIES_GRADED_GRADEDACTIVITIESWIDGET_H

#include "../activitieswidget.h"

class GradedActivitiesWidget : public ActivitiesWidget
{
    Q_OBJECT

public:
    GradedActivitiesWidget(QWidget* parent = nullptr);
    ~GradedActivitiesWidget();
};

#endif // GUI_PAGES_ACTIVITIES_GRADED_GRADEDACTIVITIESWIDGET_H
