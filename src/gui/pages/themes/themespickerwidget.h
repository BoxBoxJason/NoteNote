#ifndef GUI_PAGES_THEMES_THEMESPICKERWIDGET
#define GUI_PAGES_THEMES_THEMESPICKERWIDGET

#include <QLineEdit>

class ThemesPickerWidget : public QLineEdit {
    Q_OBJECT

public:
    ThemesPickerWidget(QWidget* parent = nullptr);

public slots:
    void onThemeUpdated(const QString& theme_input);

signals:
    void themePicked(const QString& theme_id);
};

#endif // GUI_PAGES_THEMES_THEMESPICKERWIDGET
