#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "navigationbar.h"


NavigationBar::NavigationBar(QWidget* parent) : QToolBar(parent) {
    setMovable(false);
    setFloatable(false);
    setOrientation(Qt::Vertical);
    QFile variables_json_file(":styles/toolbar.json");
    if (variables_json_file.open(QFile::ReadOnly)) {
        QJsonArray toolbar_array = QJsonDocument::fromJson(variables_json_file.readAll()).array();
        variables_json_file.close();
        for (QJsonValue array_val : toolbar_array) {
            QJsonObject action_dict = array_val.toObject();
            QAction* action = new QAction(this);
            action->setIcon(QIcon(action_dict.value("icon").toString()));
            action->setToolTip(action_dict.value("tooltip").toString());
            QString action_slug = action_dict.value("action").toString();
            connect(action, &QAction::triggered, this, [this, action_slug]() { emit changePage(action_slug); });
            addAction(action);
        }
    } else {
        qCritical() << "Could not load toolbar settings, navigation will be disabled, please check toolbar.json";
    }
    
}


NavigationBar::~NavigationBar() {
}
