#ifndef GUI_NAVIGATION_NAVIGATIONBAR_H
#define GUI_NAVIGATION_NAVIGATIONBAR_H

#include <QToolBar>

class NavigationBar : public QToolBar
{
    Q_OBJECT

public:
    NavigationBar(QWidget* parent = nullptr);
    ~NavigationBar();
};

#endif // GUI_NAVIGATION_NAVIGATIONBAR_H
