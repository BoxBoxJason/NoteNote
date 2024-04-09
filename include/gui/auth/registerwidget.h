#ifndef GUI_AUTH_REGISTERWIDGET_H
#define GUI_AUTH_REGISTERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    RegisterWidget(QWidget* parent = nullptr);

public slots:
    void clean();

private slots:
    void registerClicked();
    void checkFirstName(const QString& first_name);
    void checkLastName(const QString& last_name);
    void checkEmail(const QString& email);
    void checkPassword(const QString& password);
    void checkConfirmPassword(const QString& confirm_password);

private:
    QLineEdit* first_name_line_edit;
    QLineEdit* last_name_line_edit;
    QLineEdit* email_line_edit;
    QLineEdit* password_line_edit;
    QLineEdit* confirm_password_line_edit;
    QPushButton* register_button;
    bool first_name_valid = false;
    bool last_name_valid = false;
    bool email_valid = false;
    bool password_valid = false;
    bool confirm_password_valid = false;

signals:
    void signUp(int user_id);
    void error(const QString& message);
};

#endif // GUI_AUTH_REGISTERWIDGET_H
