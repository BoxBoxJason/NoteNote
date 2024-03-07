#ifndef GUI_NAVIGATION_NAVIGATIONBAR_H
#define GUI_NAVIGATION_NAVIGATIONBAR_H

#include <QToolBar>

class NavigationBar : public QToolBar
{
    Q_OBJECT

public:
    NavigationBar(QWidget* parent = nullptr);
    ~NavigationBar();

private:
    QAction* login_out_action;

signals:
    void changePage(const QString& page_name);
    void logout();

};

#endif // GUI_NAVIGATION_NAVIGATIONBAR_H
