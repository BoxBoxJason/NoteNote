#ifndef GUI_PAGES_ASSIDUITY_ABSENCES_ABSENCESWIDGET_H
#define GUI_PAGES_ASSIDUITY_ABSENCES_ABSENCESWIDGET_H

#include "../assiduitywidget.h"

class AbsencesWidget : public AssiduityWidget
{
    Q_OBJECT

public:
    AbsencesWidget(QWidget* parent = nullptr);
    ~AbsencesWidget();
};

#endif // GUI_PAGES_ASSIDUITY_ABSENCES_ABSENCESWIDGET_H
