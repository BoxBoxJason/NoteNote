#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "navigationbar.h"


NavigationBar::NavigationBar(QWidget* parent) : QToolBar(parent) {
    setMovable(false);
    setFloatable(false);
    setOrientation(Qt::Vertical);
    QFile variables_json_file(":enums/toolbar.json");
    if (variables_json_file.open(QFile::ReadOnly)) {
        QJsonArray toolbar_array = QJsonDocument::fromJson(variables_json_file.readAll()).array();
        variables_json_file.close();
        for (QJsonValue array_val : toolbar_array) {
            QJsonObject action_dict = array_val.toObject();
            QAction* action = new QAction(this);
            action->setIcon(QIcon(action_dict.value("icon").toString()));
            action->setToolTip(tr(action_dict.value("tooltip").toString().toUtf8()));
            QString action_slug = action_dict.value("slug").toString();
            connect(action, &QAction::triggered, this, [this, action_slug]() { emit changePage(action_slug); });
            addAction(action);
        }

        QWidget *spacer = new QWidget();
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        spacer->setVisible(true);
        addWidget(spacer);

        QAction* settings_action = new QAction(this);
        settings_action->setIcon(QIcon(":icons/settings.png"));
        settings_action->setToolTip(tr("Settings"));
        connect(settings_action, &QAction::triggered, this, [this]() { emit changePage("settings"); });
        addAction(settings_action);

        login_out_action = new QAction(this);
        login_out_action->setIcon(QIcon(":icons/login.png"));
        login_out_action->setToolTip(tr("Log in"));
        connect(login_out_action, &QAction::triggered, this, [this]() { emit changePage("auth"); });
        addAction(login_out_action);

    } else {
        qCritical() << "Could not load toolbar settings, navigation will be disabled, please check toolbar.json";
    }
    
}


void NavigationBar::loggedIn(bool logged_in) {
    if (logged_in) {
        login_out_action->setIcon(QIcon(":icons/logout.png"));
        login_out_action->setToolTip(tr("Log out"));
    } else {
        login_out_action->setIcon(QIcon(":icons/login.png"));
        login_out_action->setToolTip(tr("Log in"));
    }
}
