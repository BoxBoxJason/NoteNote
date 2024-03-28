#ifndef GUI_PAGES_LESSONS_EXTENSIONPICKERWIDGET_H
#define GUI_PAGES_LESSONS_EXTENSIONPICKERWIDGET_H

#include <QWidget>
#include <QString>

class ExtensionPickerWidget : public QWidget {
    /**
     * @class ExtensionPickerWidget
     * @brief An UI based widget to allow user to pick an extension for file creation.
    */
    Q_OBJECT

public:
    ExtensionPickerWidget(QWidget* parent = nullptr);

signals:
    /**
     * @brief Signal emitted when an extension is selected.
     * @param is_directory A boolean value to indicate if the selected extension is a directory.
     * @param extension The selected extension (default is empty).
    */
    void extensionSelected(bool is_directory, const QString& extension="");

};

#endif // GUI_PAGES_LESSONS_EXTENSIONPICKERWIDGET_H
