#ifndef GUI_PAGES_LESSONS_FILECREATORWIDGET_H
#define GUI_PAGES_LESSONS_FILECREATORWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QStackedLayout>
#include <QTreeWidgetItem>
#include "extensionpickerwidget.h"

class FileCreatorWidget : public QDialog {
    /**
     * @class FileCreatorWidget
     * @brief An UI based widget to create a new file or directory.
     * @details The widget provides a way to create a new file or directory with a specific extension.
    */
    Q_OBJECT

public:
    FileCreatorWidget(QTreeWidgetItem* parent_item, QWidget* parent = nullptr);

private:
    // Base path to create the new file or directory.
    QTreeWidgetItem* parent_item;
    // Extension picker widget
    ExtensionPickerWidget* extension_picker;
    // Widget stacked layout
    QStackedLayout* layout;

private slots:
    /**
     * @brief Slot to handle extension selected event.
     * @details Removes the extension picker widget and shows the name picker widget.
     * @param is_directory Flag to check if the selected extension is a directory.
     * @param extension The selected extension.
    */
    void extensionSelected(bool is_directory, const QString& extension);
    bool checkFileName(const QString& file_name);
    void createPath(bool is_directory, const QString& file_name);

signals:
    void invalidPath(const QString& error_message);
    void validPath();
};

#endif // GUI_PAGES_LESSONS_FILECREATORWIDGET_H
