#ifndef GUI_NAVIGATION_NAVIGATIONBAR_H
#define GUI_NAVIGATION_NAVIGATIONBAR_H

#include <QToolBar>

class NavigationBar : public QToolBar
{
    Q_OBJECT

public:
    NavigationBar(QWidget* parent = nullptr);

public slots:
    void loggedIn(bool logged_in);

private:
    QAction* login_out_action;

signals:
    void changePage(const QString& page_name);    

};

#endif // GUI_NAVIGATION_NAVIGATIONBAR_H
