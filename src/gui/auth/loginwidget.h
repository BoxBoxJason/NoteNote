#ifndef GUI_AUTH_LOGINWIDGET_H
#define GUI_AUTH_LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget* parent = nullptr);
    ~LoginWidget();

public slots:
    void clean();

private:
    QLineEdit* email_line_edit;
    QLineEdit* password_line_edit;

private slots:
    void loginClicked();
    void resetInputStyle();

signals:
    void signIn(int user_id);
    void error(const QString& message);

};

#endif // GUI_AUTH_LOGINWIDGET_H
