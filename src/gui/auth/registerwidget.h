#ifndef GUI_AUTH_REGISTERWIDGET_H
#define GUI_AUTH_REGISTERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    RegisterWidget(QWidget* parent = nullptr);
    ~RegisterWidget();

public slots:
    void clean();

private slots:
    void registerClicked();
    void checkName(const QString& name);
    void checkEmail(const QString& email);
    void checkPassword(const QString& password);
    void checkConfirmPassword(const QString& confirm_password);

private:
    QLineEdit* first_name_line_edit;
    QLineEdit* last_name_line_edit;
    QLineEdit* email_line_edit;
    QLineEdit* password_line_edit;
    QLineEdit* confirm_password_line_edit;

signals:
    void registered(int user_id);

};

#endif // GUI_AUTH_REGISTERWIDGET_H
