#ifndef GUI_AUTH_AUTHWIDGET_H
#define GUI_AUTH_AUTHWIDGET_H

#include <QWidget>
#include "loginwidget.h"
#include "registerwidget.h"

class AuthWidget : public QWidget
{
    Q_OBJECT

public:
    AuthWidget(QWidget* parent = nullptr);
    ~AuthWidget();

public slots:
    void clean();

private slots: 
    void authSuccess(int user_id);

private:
    LoginWidget* login_widget;
    RegisterWidget* register_widget;

signals:
    void authentified(int user_id);

};

#endif // GUI_AUTH_AUTHWIDGET_H
