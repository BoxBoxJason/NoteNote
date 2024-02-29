#ifndef GUI_AUTH_AUTHWIDGET_H
#define GUI_AUTH_AUTHWIDGET_H

#include <QWidget>
#include <QStackedLayout>
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
    void showError(const QString& message);

private:
    QStackedLayout* stacked_layout;
    LoginWidget* login_widget;
    RegisterWidget* register_widget;
    QLabel* error_display_label;

signals:
    void authentified(int user_id);

};

#endif // GUI_AUTH_AUTHWIDGET_H
