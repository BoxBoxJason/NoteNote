#ifndef GUI_PAGES_THEMES_THEMESWIDGET_H
#define GUI_PAGES_THEMES_THEMESWIDGET_H

#include <QWidget>

class ThemesWidget : public QWidget {
    Q_OBJECT

public:
    ThemesWidget(QWidget* parent = nullptr);

private slots:
    void saveChanges();
    void exportToCSV();

private:
    QString getCSV();
};

#endif // GUI_PAGES_THEMES_THEMESWIDGET_H
